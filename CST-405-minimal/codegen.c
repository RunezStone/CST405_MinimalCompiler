#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

/* Output file handle */
static FILE* output;

/* Simple temp-register counter — wraps $t0–$t7 */
static int tempReg = 0;

/* Counter for generating unique loop labels (Lstart0/Lend0, Lstart1/Lend1, ...) */
static int loopLabelCount = 0;

/* Frame size of the current function — set by genFuncDef so that
 * early-return (end) statements inside if bodies can emit the epilogue. */
static int currentFrameSize = 128;

/* ─────────────────────────────────────────────────────────────────────────
 * GLOBAL VARIABLE TABLE
 * Pre-scanned before any function is generated.  $s7 is set to $sp
 * at the start of main so functions can reach globals via N($s7).
 * ───────────────────────────────────────────────────────────────────────── */
#define MAX_GLOBALS 100
static struct {
    char name[64];
    char structType[64]; /* struct type name, or "" for scalars/arrays */
    int  offset;
} globalVars[MAX_GLOBALS];
static int globalVarCount  = 0;
static int globalNextOffset = 0;

static void addGlobal(const char* name, const char* structTypeName, int bytes) {
    if (globalVarCount >= MAX_GLOBALS) return;
    strncpy(globalVars[globalVarCount].name, name, 63);
    globalVars[globalVarCount].name[63] = '\0';
    if (structTypeName) {
        strncpy(globalVars[globalVarCount].structType, structTypeName, 63);
        globalVars[globalVarCount].structType[63] = '\0';
    } else {
        globalVars[globalVarCount].structType[0] = '\0';
    }
    globalVars[globalVarCount].offset = globalNextOffset;
    globalNextOffset += bytes;
    globalVarCount++;
}

/* Look up a global variable's offset.  Returns -1 if not found. */
static int getGlobalVarOffset(const char* name) {
    for (int i = 0; i < globalVarCount; i++)
        if (strcmp(globalVars[i].name, name) == 0)
            return globalVars[i].offset;
    return -1;
}

/* Look up a global variable's struct type name. Returns NULL if scalar. */
static const char* getGlobalStructType(const char* name) {
    for (int i = 0; i < globalVarCount; i++)
        if (strcmp(globalVars[i].name, name) == 0)
            return globalVars[i].structType[0] ? globalVars[i].structType : NULL;
    return NULL;
}

/* Walk the globals AST and record every variable's offset so functions
 * can use $s7-relative addressing to reach them.                       */
static void scanGlobals(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_DECL: {
            StructTypeInfo* st = findStructType(node->data.decl.varType);
            if (st) {
                addGlobal(node->data.decl.name, node->data.decl.varType,
                          st->totalSize);
            } else {
                addGlobal(node->data.decl.name, NULL, 4);
            }
            break;
        }
        case NODE_ARRAY_DECL:
            addGlobal(node->data.array_decl.name, NULL,
                      node->data.array_decl.size * 4);
            break;
        case NODE_STMT_LIST:
            scanGlobals(node->data.stmtlist.stmt);
            scanGlobals(node->data.stmtlist.next);
            break;
        default:
            break; /* NODE_STRUCT_DEF, NODE_ASSIGN defaults, etc. — skip */
    }
}

static int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;
    return reg;
}

/* ─────────────────────────────────────────────────────────────────────────
 * ARGUMENT REGISTER TRACKING
 * Collect up to 4 arguments for a pending function call, then emit
 * move instructions into $a0–$a3 at call time.
 * ───────────────────────────────────────────────────────────────────────── */
#define MAX_CALL_ARGS 4
static int   pendingArgs[MAX_CALL_ARGS];  /* $t register holding each arg */
static int   pendingArgCount = 0;

/* ─────────────────────────────────────────────────────────────────────────
 * EXPRESSION CODE GENERATION
 * Leaves the result in $t{tempReg - 1} after returning.
 * ───────────────────────────────────────────────────────────────────────── */
static void genExpr(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_NUM: {
            int reg = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", reg, node->data.num);
            break;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            int reg    = getNextTemp();
            if (offset != -1) {
                fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
            } else {
                int goffset = getGlobalVarOffset(node->data.name);
                if (goffset != -1) {
                    fprintf(output, "    lw $t%d, %d($s7)   # global %s\n",
                            reg, goffset, node->data.name);
                } else {
                    fprintf(stderr,
                        "CODEGEN ERROR: Variable '%s' not declared\n",
                        node->data.name);
                    exit(1);
                }
            }
            break;
        }

        /* ── Struct field access (rvalue):  base is field  ──
         * Address = base's stack offset + field's byte offset within
         * the struct (both positive, relative to $sp).               */
        case NODE_STRUCT_ACCESS: {
            ASTNode* base    = node->data.struct_access.base;
            char*    field   = node->data.struct_access.field;
            char*    baseName = (base && base->type == NODE_VAR)
                                    ? base->data.name : NULL;
            if (!baseName) {
                fprintf(stderr,
                    "CODEGEN ERROR: Struct access base must be a simple variable\n");
                exit(1);
            }
            int         baseOffset     = getVarOffset(baseName);
            const char* structTypeName = getVarStructType(baseName);
            /* Fall back to global table if not in local frame */
            int isGlobal = 0;
            if (baseOffset == -1) {
                baseOffset     = getGlobalVarOffset(baseName);
                structTypeName = getGlobalStructType(baseName);
                isGlobal       = 1;
            }
            if (baseOffset == -1) {
                fprintf(stderr,
                    "CODEGEN ERROR: '%s' is not a declared struct variable\n", baseName);
                exit(1);
            }
            StructTypeInfo* st = structTypeName ? findStructType(structTypeName) : NULL;
            StructField*    f  = st ? findStructField(st, field) : NULL;
            if (!f) {
                fprintf(stderr,
                    "CODEGEN ERROR: Cannot resolve field '%s' on '%s'\n",
                    field, baseName);
                exit(1);
            }
            int totalOffset = baseOffset + f->offset;
            int reg = getNextTemp();
            if (isGlobal) {
                fprintf(output, "    lw $t%d, %d($s7)   # global %s is %s\n",
                        reg, totalOffset, baseName, field);
            } else {
                fprintf(output, "    lw $t%d, %d($sp)   # %s is %s\n",
                        reg, totalOffset, baseName, field);
            }
            break;
        }

        case NODE_BINOP: {
            genExpr(node->data.binop.left);
            int leftReg = tempReg - 1;
            genExpr(node->data.binop.right);
            int rightReg = tempReg - 1;

            switch (node->data.binop.op) {
                case '+':
                    fprintf(output, "    add $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case '-':
                    fprintf(output, "    sub $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case '*':
                    fprintf(output, "    mul $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case '/':
                    fprintf(output, "    div $t%d, $t%d\n",
                            leftReg, rightReg);
                    fprintf(output, "    mflo $t%d\n", leftReg);
                    break;

                /* ── Relational operators — yield 0/1 in $t<leftReg> ──
                 * op codes set by the scanner: '<' '>' for < and >,
                 * 'l' '=' (<=), 'g' (>=), 'e' (==), 'n' (!=)            */
                case '<':
                    fprintf(output, "    slt $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case '>':
                    fprintf(output, "    sgt $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case 'l':   /* <= */
                    fprintf(output, "    sle $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case 'g':   /* >= */
                    fprintf(output, "    sge $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case 'e':   /* == */
                    fprintf(output, "    seq $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;
                case 'n':   /* != */
                    fprintf(output, "    sne $t%d, $t%d, $t%d\n",
                            leftReg, leftReg, rightReg);
                    break;

                default:
                    break;
            }
            tempReg = leftReg + 1;
            break;
        }

       
        case NODE_FUNC_CALL:
            genFuncCall(node);
            /* Result is in $v0; move to next temp so the caller can use it */
            fprintf(output, "    move $t%d, $v0\n", getNextTemp());
            break;

        default:
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: FUNCTION CALL CODE GENERATION
 * Evaluates each argument, moves results into $a0–$a3, then jal.
 * ───────────────────────────────────────────────────────────────────────── */
void genFuncCall(ASTNode* node) {
    if (!node || node->type != NODE_FUNC_CALL) return;

    /* Collect argument register indices */
    pendingArgCount = 0;
    ASTNode* arg = node->data.func_call.args;
    while (arg && pendingArgCount < MAX_CALL_ARGS) {
        if (arg->type == NODE_ARG_LIST) {
            genExpr(arg->data.arg_list.expr);
            pendingArgs[pendingArgCount++] = tempReg - 1;
            arg = arg->data.arg_list.next;
        } else {
            genExpr(arg);
            pendingArgs[pendingArgCount++] = tempReg - 1;
            break;
        }
    }

    /* Move arguments into $a0–$a3 */
    for (int i = 0; i < pendingArgCount; i++) {
        fprintf(output, "    move $a%d, $t%d\n", i, pendingArgs[i]);
    }

    /* Call the function — use func_ prefix for user-defined functions */
    fprintf(output, "    jal func_%s\n", node->data.func_call.name);

    /* Reset temp counter after the call */
    tempReg = 0;
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: FUNCTION DEFINITION CODE GENERATION
 * Emits the function label, stack frame setup, body, and return.
 * ───────────────────────────────────────────────────────────────────────── */
static void genFuncDef(ASTNode* node) {
    if (!node || node->type != NODE_FUNC_DEF) return;

    /* Reset the symbol table for this function's frame */
    initSymTab();
    tempReg = 0;

    /* We need two passes:
     * 1. Register all params/locals to know the frame size.
     * 2. Emit the code.
     * For simplicity we use a fixed frame size of 128 bytes
     * (enough for up to 28 local ints + saved $ra).
     * The lecture notes use a similar fixed approach.        */
    int frameSize = 128;
    currentFrameSize = frameSize;   /* make visible to early-return stmts */

    /* ── Function label ── */
    fprintf(output, "\n# -- Function: %s --\n", node->data.func_def.name);
    fprintf(output, "func_%s:\n", node->data.func_def.name);

    /* ── Prologue: allocate frame, save $ra ── */
    fprintf(output, "    addi $sp, $sp, -%d\n", frameSize);
    fprintf(output, "    sw   $ra, %d($sp)\n", frameSize - 4);

    /* ── Store incoming parameters ($a0–$a3) onto the stack ── */
    int argIdx = 0;
    ASTNode* p = node->data.func_def.params;
    while (p && argIdx < MAX_CALL_ARGS) {
        char* paramName = NULL;
        ASTNode* param  = NULL;

        if (p->type == NODE_PARAM) {
            param = p;
            p = NULL;   /* single param, stop after this */
        } else if (p->type == NODE_PARAM_LIST) {
            param = p->data.param_list.param;
            p     = p->data.param_list.next;
        } else {
            break;
        }

        if (param && param->type == NODE_PARAM)
            paramName = param->data.param.name;
        else if (param && param->type == NODE_ARRAY_DECL)
            paramName = param->data.array_decl.name;

        if (paramName) {
            int offset = addVar(paramName, "int");
            fprintf(output, "    sw   $a%d, %d($sp)   # param %s\n",
                    argIdx, offset, paramName);
            argIdx++;
        }
    }

    /* ── Body ── */
    genStmt(node->data.func_def.body);

    /* ── Return value ── */
    ASTNode* ec = node->data.func_def.end_clause;
    if (ec && ec->data.name != NULL) {
        /* "end result;" — load the variable into $v0 */
        int offset = getVarOffset(ec->data.name);
        if (offset != -1) {
            fprintf(output, "    lw   $v0, %d($sp)   # return %s\n",
                    offset, ec->data.name);
        } else {
            fprintf(stderr,
                "CODEGEN ERROR: Return variable '%s' not found in '%s'\n",
                ec->data.name, node->data.func_def.name);
        }
    }
    /* "end null;" — void, $v0 left undefined (caller won't use it) */

    /* ── Epilogue: restore $ra, free frame, return ── */
    fprintf(output, "    lw   $ra, %d($sp)\n", frameSize - 4);
    fprintf(output, "    addi $sp, $sp, %d\n", frameSize);
    fprintf(output, "    jr   $ra\n");
}

/* ─────────────────────────────────────────────────────────────────────────
 * STATEMENT CODE GENERATION
 * ───────────────────────────────────────────────────────────────────────── */
void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_DECL: {
            char* declType   = node->data.decl.varType;
            int   isStructTy = (declType && findStructType(declType) != NULL);
            int   offset;

            if (isStructTy) {
                offset = addStructVar(node->data.decl.name, declType);
            } else {
                offset = addVar(node->data.decl.name, declType);
            }

            if (offset == -1) {
                fprintf(stderr,
                    "CODEGEN ERROR: Variable '%s' already declared\n",
                    node->data.decl.name);
                exit(1);
            }
            fprintf(output, "    # Declare %s %s at offset %d\n",
                    declType, node->data.decl.name, offset);

            /* ── Initialize fields that carry a default value, e.g.
             *    struct stats { int health; health = 10; ... }
             * emits   playerStats.health = 10   right after the DECL ── */
            if (isStructTy) {
                StructTypeInfo* st = findStructType(declType);
                if (st) {
                    for (int fi = 0; fi < st->fieldCount; fi++) {
                        StructField* f = &st->fields[fi];
                        if (!f->hasDefault) continue;

                        int totalOffset = offset + f->offset;
                        if (f->defaultIsFloat) {
                            fprintf(output,
                                "    # NOTE: float default for %s.%s = %g "
                                "skipped (float codegen unsupported)\n",
                                node->data.decl.name, f->name, f->defaultFloatVal);
                        } else {
                            int reg = getNextTemp();
                            fprintf(output, "    li $t%d, %d\n", reg, f->defaultIntVal);
                            fprintf(output,
                                "    sw $t%d, %d($sp)   # %s.%s = %d (default)\n",
                                reg, totalOffset, node->data.decl.name,
                                f->name, f->defaultIntVal);
                            tempReg = 0;
                        }
                    }
                }
            }
            break;
        }

        case NODE_ASSIGN: {
            /* ── Struct field assignment:  base is field = expr;  ── */
            if (node->data.assign.structLHS) {
                ASTNode* access  = node->data.assign.structLHS;
                ASTNode* base    = access->data.struct_access.base;
                char*    field   = access->data.struct_access.field;
                char*    baseName = (base && base->type == NODE_VAR)
                                        ? base->data.name : NULL;
                if (!baseName) {
                    fprintf(stderr,
                        "CODEGEN ERROR: Struct assignment base must be a simple variable\n");
                    exit(1);
                }
                int         baseOffset     = getVarOffset(baseName);
                const char* structTypeName = getVarStructType(baseName);
                int         isGlobal       = 0;
                if (baseOffset == -1) {
                    baseOffset     = getGlobalVarOffset(baseName);
                    structTypeName = getGlobalStructType(baseName);
                    isGlobal       = 1;
                }
                if (baseOffset == -1) {
                    fprintf(stderr,
                        "CODEGEN ERROR: '%s' is not a declared struct variable\n", baseName);
                    exit(1);
                }
                StructTypeInfo* st = structTypeName ? findStructType(structTypeName) : NULL;
                StructField*    f  = st ? findStructField(st, field) : NULL;
                if (!f) {
                    fprintf(stderr,
                        "CODEGEN ERROR: Cannot resolve field '%s' on '%s'\n",
                        field, baseName);
                    exit(1);
                }
                int totalOffset = baseOffset + f->offset;
                genExpr(node->data.assign.value);
                if (isGlobal)
                    fprintf(output, "    sw   $t%d, %d($s7)   # global %s is %s = ...\n",
                            tempReg - 1, totalOffset, baseName, field);
                else
                    fprintf(output, "    sw   $t%d, %d($sp)   # %s is %s = ...\n",
                            tempReg - 1, totalOffset, baseName, field);
                tempReg = 0;
                break;
            }

            /* ── helper macro: resolve scalar variable offset + base register ── */
            #define RESOLVE_VAR(varname, out_offset, out_reg_str)       \
                do {                                                     \
                    int _lo = getVarOffset(varname);                     \
                    if (_lo != -1) {                                     \
                        (out_offset)   = _lo;                           \
                        (out_reg_str)  = "$sp";                         \
                    } else {                                             \
                        int _go = getGlobalVarOffset(varname);          \
                        if (_go != -1) {                                 \
                            (out_offset)  = _go;                        \
                            (out_reg_str) = "$s7";                      \
                        } else {                                         \
                            fprintf(stderr,                              \
                                "CODEGEN ERROR: Variable '%s' not declared\n", \
                                varname);                                \
                            exit(1);                                     \
                        }                                                \
                    }                                                    \
                } while (0)

            /* ── handle func call on RHS ── */
            if (node->data.assign.value &&
                node->data.assign.value->type == NODE_FUNC_CALL) {
                genFuncCall(node->data.assign.value);
                int   off = 0;
                const char* breg = NULL;
                RESOLVE_VAR(node->data.assign.var, off, breg);
                fprintf(output, "    sw   $v0, %d(%s)   # %s = call result\n",
                        off, breg, node->data.assign.var);
                tempReg = 0;
            } else {
                int   off = 0;
                const char* breg = NULL;
                RESOLVE_VAR(node->data.assign.var, off, breg);
                genExpr(node->data.assign.value);
                fprintf(output, "    sw   $t%d, %d(%s)   # %s = ...\n",
                        tempReg - 1, off, breg, node->data.assign.var);
                tempReg = 0;
            }
            #undef RESOLVE_VAR
            break;
        }

        case NODE_PRINT:
            genExpr(node->data.expr);
            fprintf(output, "    # Print integer\n");
            fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
            fprintf(output, "    li   $v0, 1\n");
            fprintf(output, "    syscall\n");
            fprintf(output, "    # Print newline\n");
            fprintf(output, "    li   $v0, 11\n");
            fprintf(output, "    li   $a0, 10\n");
            fprintf(output, "    syscall\n");
            tempReg = 0;
            break;

        /* ── NEW: standalone function call statement ── */
        case NODE_FUNC_CALL:
            genFuncCall(node);
            break;

        /* ── early return: end x; / end 0; / end null; inside a block ──
         * Loads the return value into $v0 (if any), then runs the
         * standard function epilogue and jumps to $ra.               */
        case NODE_END_CLAUSE: {
            const char* retName = node->data.name;
            if (retName != NULL) {
                if (retName[0] >= '0' && retName[0] <= '9') {
                    /* Numeric literal — e.g. end 1; */
                    fprintf(output, "    li   $v0, %s   # early return value\n",
                            retName);
                } else {
                    /* Variable — e.g. end result; */
                    int offset = getVarOffset(retName);
                    if (offset != -1)
                        fprintf(output,
                                "    lw   $v0, %d($sp)   # early return %s\n",
                                offset, retName);
                    else
                        fprintf(stderr,
                                "CODEGEN ERROR: Return variable '%s' not found\n",
                                retName);
                }
            }
            /* Epilogue — mirror of genFuncDef's epilogue */
            fprintf(output, "    lw   $ra, %d($sp)\n", currentFrameSize - 4);
            fprintf(output, "    addi $sp, $sp, %d\n", currentFrameSize);
            fprintf(output, "    jr   $ra\n");
            break;
        }

        /* ── NEW: while loop ──
         * Lstart:
         *     <evaluate condition into $tN>
         *     beqz $tN, Lend
         *     <body>
         *     j Lstart
         * Lend:                                                        */
        /* ── if / if-else / else-if ──
         *     <evaluate condition into $tN>
         *     beqz $tN, Lelse<id>   (or Lend<id> if no else)
         *     <then body>
         *     j Lend<id>            (only if else exists)
         * Lelse<id>:
         *     <else body>
         * Lend<id>:                                                    */
        case NODE_IF: {
            int id = loopLabelCount++;
            genExpr(node->data.if_stmt.condition);
            int condReg = tempReg - 1;

            if (node->data.if_stmt.else_stmt) {
                fprintf(output, "    beqz $t%d, Lelse%d\n", condReg, id);
                tempReg = 0;
                if (node->data.if_stmt.then_stmt)
                    genStmt(node->data.if_stmt.then_stmt);
                tempReg = 0;
                fprintf(output, "    j Lend%d\n", id);
                fprintf(output, "Lelse%d:\n", id);
                genStmt(node->data.if_stmt.else_stmt);
                tempReg = 0;
            } else {
                fprintf(output, "    beqz $t%d, Lend%d\n", condReg, id);
                tempReg = 0;
                if (node->data.if_stmt.then_stmt)
                    genStmt(node->data.if_stmt.then_stmt);
                tempReg = 0;
            }
            fprintf(output, "Lend%d:\n", id);
            break;
        }

        case NODE_WHILE: {
            int id = loopLabelCount++;
            fprintf(output, "Lstart%d:\n", id);
            genExpr(node->data.while_stmt.condition);
            fprintf(output, "    beqz $t%d, Lend%d\n", tempReg - 1, id);
            tempReg = 0;
            genStmt(node->data.while_stmt.body);
            tempReg = 0;
            fprintf(output, "    j Lstart%d\n", id);
            fprintf(output, "Lend%d:\n", id);
            break;
        }

        /* ── NEW: C-style while loop ──
         *     <init>
         * Lstart:
         *     <evaluate condition into $tN>
         *     beqz $tN, Lend
         *     <body>
         *     <update>
         *     j Lstart
         * Lend:                                                        */
        case NODE_FOR_WHILE: {
            genStmt(node->data.for_while.init);
            tempReg = 0;
            int id = loopLabelCount++;
            fprintf(output, "Lstart%d:\n", id);
            genExpr(node->data.for_while.condition);
            fprintf(output, "    beqz $t%d, Lend%d\n", tempReg - 1, id);
            tempReg = 0;
            genStmt(node->data.for_while.body);
            tempReg = 0;
            genStmt(node->data.for_while.update);
            tempReg = 0;
            fprintf(output, "    j Lstart%d\n", id);
            fprintf(output, "Lend%d:\n", id);
            break;
        }

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        default:
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: WALK A STMT_LIST OF FUNCTION DEFINITIONS
 * ───────────────────────────────────────────────────────────────────────── */
static void genFuncList(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        genFuncList(node->data.stmtlist.stmt);
        genFuncList(node->data.stmtlist.next);
    } else if (node->type == NODE_FUNC_DEF) {
        genFuncDef(node);
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * TOP-LEVEL MIPS GENERATION
 * ───────────────────────────────────────────────────────────────────────── */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "CODEGEN ERROR: Cannot open output file '%s'\n",
                filename);
        exit(1);
    }

    /* ── MIPS file header ── */
    fprintf(output, "# Generated MIPS Assembly\n");
    fprintf(output, "# -------------------------------------\n\n");
    fprintf(output, ".data\n\n");
    fprintf(output, ".text\n");
    fprintf(output, ".globl main\n");

    /* ── UPDATED: handle NODE_PROGRAM root ── */
    if (root && root->type == NODE_PROGRAM) {

        /* 0. Pre-scan globals so functions can resolve them via $s7 */
        globalVarCount  = 0;
        globalNextOffset = 0;
        if (root->data.program.globals)
            scanGlobals(root->data.program.globals);

        /* 1. Emit all function definitions first (before main) */
        genFuncList(root->data.program.funcs);

        /* 2. Emit the Program_Start block as 'main' */
        fprintf(output, "\nmain:\n");
        fprintf(output, "    # Allocate global stack frame\n");
        fprintf(output, "    addi $sp, $sp, -400\n");
        fprintf(output, "    move $s7, $sp   # global frame pointer\n\n");

        /* Reset symbol table for Program_Start's local variables */
        initSymTab();
        tempReg = 0;

        /* Generate global declarations so they land in the symbol table */
        if (root->data.program.globals)
            genStmt(root->data.program.globals);

        /* Generate Program_Start body */
        ASTNode* ps = root->data.program.start;
        if (ps && ps->type == NODE_PROGRAM_START)
            genStmt(ps->data.block.stmt_list);

        /* Program exit */
        fprintf(output, "\n    # Exit program\n");
        fprintf(output, "    addi $sp, $sp, 400\n");
        fprintf(output, "    li   $v0, 10\n");
        fprintf(output, "    syscall\n");

    } else {
        /* Fallback: old flat stmt_list root (shouldn't happen with
         * the new parser but keeps backwards compatibility)        */
        fprintf(output, "\nmain:\n");
        fprintf(output, "    addi $sp, $sp, -400\n\n");
        initSymTab();
        tempReg = 0;
        genStmt(root);
        fprintf(output, "\n    addi $sp, $sp, 400\n");
        fprintf(output, "    li   $v0, 10\n");
        fprintf(output, "    syscall\n");
    }

    fclose(output);
    printf("  ✓ MIPS code written to '%s'\n", filename);
}
