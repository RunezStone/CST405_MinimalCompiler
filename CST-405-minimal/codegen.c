#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

/* Output file handle */
static FILE* output;

/* Simple temp-register counter — wraps $t0–$t7 */
static int tempReg = 0;

static int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;
    return reg;
}

/* ── Float support ──────────────────────────────────────────────────────── */
/* Float temp register counter — uses even $f registers: $f0,$f2,$f4,... */
static int floatReg = 0;

static int getNextFloatReg() {
    int reg = floatReg;
    floatReg += 2;
    if (floatReg > 30) floatReg = 0;
    return reg;
}

/* Set by genExpr — 1 if the last expression produced a float result */
static int lastExprIsFloat = 0;

/* Float constant pool — literals are stored in .data and loaded at runtime */
#define MAX_FLOAT_CONSTS 64
static float floatConsts[MAX_FLOAT_CONSTS];
static int   floatConstCount = 0;

/* Add a float constant to the pool; returns its index */
static int addFloatConst(float val) {
    for (int i = 0; i < floatConstCount; i++)
        if (floatConsts[i] == val) return i;
    if (floatConstCount >= MAX_FLOAT_CONSTS) {
        fprintf(stderr, "CODEGEN ERROR: float constant pool full\n");
        return 0;
    }
    floatConsts[floatConstCount++] = val;
    return floatConstCount - 1;
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
            lastExprIsFloat = 0;
            break;
        }

        case NODE_FLOAT: {
            int idx = addFloatConst(node->data.fval);
            int addrReg = getNextTemp();
            int freg = getNextFloatReg();
            fprintf(output, "    la   $t%d, _fc%d\n", addrReg, idx);
            fprintf(output, "    lwc1 $f%d, 0($t%d)\n", freg, addrReg);
            lastExprIsFloat = 1;
            break;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr,
                    "CODEGEN ERROR: Variable '%s' not in symbol table\n",
                    node->data.name);
                exit(1);
            }
            char* type = getVarType(node->data.name);
            if (type && strcmp(type, "float") == 0) {
                int freg = getNextFloatReg();
                fprintf(output, "    lwc1 $f%d, %d($sp)   # float %s\n",
                        freg, offset, node->data.name);
                lastExprIsFloat = 1;
            } else {
                int reg = getNextTemp();
                fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
                lastExprIsFloat = 0;
            }
            break;
        }

        case NODE_BINOP: {
            /* Handle unary minus separately (right operand is NULL) */
            if (node->data.binop.op == 'u') {
                genExpr(node->data.binop.left);
                if (lastExprIsFloat) {
                    int freg = floatReg - 2; if (freg < 0) freg = 30;
                    fprintf(output, "    neg.s $f%d, $f%d\n", freg, freg);
                } else {
                    int reg = tempReg - 1;
                    fprintf(output, "    neg $t%d, $t%d\n", reg, reg);
                }
                break;
            }

            genExpr(node->data.binop.left);
            int leftIsFloat = lastExprIsFloat;
            int leftTReg = tempReg - 1;
            int leftFReg = floatReg - 2; if (leftFReg < 0) leftFReg = 30;

            genExpr(node->data.binop.right);
            int rightIsFloat = lastExprIsFloat;
            int rightTReg = tempReg - 1;
            int rightFReg = floatReg - 2; if (rightFReg < 0) rightFReg = 30;

            int useFloat = leftIsFloat || rightIsFloat;

            if (useFloat) {
                /* Promote integer operands to float if mixed */
                if (!leftIsFloat) {
                    int freg = getNextFloatReg();
                    fprintf(output, "    mtc1  $t%d, $f%d\n", leftTReg, freg);
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", freg, freg);
                    leftFReg = freg;
                }
                if (!rightIsFloat) {
                    int freg = getNextFloatReg();
                    fprintf(output, "    mtc1  $t%d, $f%d\n", rightTReg, freg);
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", freg, freg);
                    rightFReg = freg;
                }
                switch (node->data.binop.op) {
                    case '+': fprintf(output, "    add.s $f%d, $f%d, $f%d\n", leftFReg, leftFReg, rightFReg); break;
                    case '-': fprintf(output, "    sub.s $f%d, $f%d, $f%d\n", leftFReg, leftFReg, rightFReg); break;
                    case '*': fprintf(output, "    mul.s $f%d, $f%d, $f%d\n", leftFReg, leftFReg, rightFReg); break;
                    case '/': fprintf(output, "    div.s $f%d, $f%d, $f%d\n", leftFReg, leftFReg, rightFReg); break;
                    default: break;
                }
                floatReg = leftFReg + 2;
                lastExprIsFloat = 1;
            } else {
                switch (node->data.binop.op) {
                    case '+':
                        fprintf(output, "    add $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case '-':
                        fprintf(output, "    sub $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case '*':
                        fprintf(output, "    mul $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case '/':
                        fprintf(output, "    div $t%d, $t%d\n",
                                leftTReg, rightTReg);
                        fprintf(output, "    mflo $t%d\n", leftTReg);
                        break;
                    case '<':
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case '>':
                        fprintf(output, "    sgt $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case 'l': /* <= */
                        fprintf(output, "    sle $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case 'g': /* >= */
                        fprintf(output, "    sge $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case 'e': /* == */
                        fprintf(output, "    seq $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    case 'n': /* != */
                        fprintf(output, "    sne $t%d, $t%d, $t%d\n",
                                leftTReg, leftTReg, rightTReg);
                        break;
                    default:
                        break;
                }
                tempReg = leftTReg + 1;
                lastExprIsFloat = 0;
            }
            break;
        }

        /* ── NEW: function call as an expression ── */
        case NODE_FUNC_CALL:
            genFuncCall(node);
            /* Result is in $v0; move to next temp so the caller can use it */
            fprintf(output, "    move $t%d, $v0\n", getNextTemp());
            break;

        case NODE_ARRAY_INDEX: {
    /* Evaluate the index expression */
    genExpr(node->data.array_index.index);
    int indexReg = tempReg - 1;

    /* Compute byte offset: index * 4 */
    int addrReg = getNextTemp();
    fprintf(output, "    sll  $t%d, $t%d, 2\n", addrReg, indexReg);

    /* Load: use lwc1 for float arrays, lw for int arrays */
    char* atype = getVarType(node->data.array_index.name);
    if (atype && strcmp(atype, "float") == 0) {
        int freg = getNextFloatReg();
        fprintf(output, "    lwc1 $f%d, %s($t%d)   # float %s[i]\n",
                freg, node->data.array_index.name, addrReg,
                node->data.array_index.name);
        lastExprIsFloat = 1;
    } else {
        int destReg = getNextTemp();
        fprintf(output, "    lw   $t%d, %s($t%d)   # %s[i]\n",
                destReg,
                node->data.array_index.name,
                addrReg,
                node->data.array_index.name);
        lastExprIsFloat = 0;
    }
    break;
}

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
            int offset = addVar(node->data.decl.name, node->data.decl.varType);
            if (offset == -1) {
                fprintf(stderr,
                    "CODEGEN ERROR: Variable '%s' already declared\n",
                    node->data.decl.name);
                exit(1);
            }
            fprintf(output, "    # Declare %s %s at offset %d\n",
                    node->data.decl.varType,
                    node->data.decl.name, offset);
            break;
        }
        case NODE_ARRAY_DECL: {
    if (!node->data.array_decl.isParam) {
        int bytes  = node->data.array_decl.size * 4;
        char* atype = node->data.array_decl.varType
                      ? node->data.array_decl.varType : "int";
        int offset = addVar(node->data.array_decl.name, atype);
        fprintf(output, "    # Array %s %s[%d] at offset %d (%d bytes)\n",
                atype,
                node->data.array_decl.name,
                node->data.array_decl.size,
                offset, bytes);
    }
    break;
}

        case NODE_ASSIGN: {
            /* ── Array store: arr[i] = expr ── */        /* ← ADD THIS BLOCK */
    if (node->data.assign.arrayLHS) {
        char* arrName = node->data.assign.arrayLHS->data.array_index.name;

        /* Evaluate the index expression */
        genExpr(node->data.assign.arrayLHS->data.array_index.index);
        int indexReg = tempReg - 1;

        /* Evaluate the RHS value */
        genExpr(node->data.assign.value);
        int valTReg  = tempReg - 1;
        int valFReg  = floatReg - 2; if (valFReg < 0) valFReg = 30;
        int isFloat  = lastExprIsFloat;

        /* Compute byte offset: index * 4 */
        int addrReg = getNextTemp();
        fprintf(output, "    sll  $t%d, $t%d, 2\n", addrReg, indexReg);

        /* Store: use swc1 for floats, sw for ints */
        if (isFloat) {
            fprintf(output, "    swc1 $f%d, %s($t%d)   # float %s[i] = ...\n",
                    valFReg, arrName, addrReg, arrName);
        } else {
            fprintf(output, "    sw   $t%d, %s($t%d)   # %s[i] = ...\n",
                    valTReg, arrName, addrReg, arrName);
        }
        tempReg  = 0;
        floatReg = 0;
        break;
    }
            /* ── NEW: handle func call on RHS ── */
            if (node->data.assign.value &&
                node->data.assign.value->type == NODE_FUNC_CALL) {
                genFuncCall(node->data.assign.value);
                /* Result is in $v0 — store to destination variable */
                int offset = getVarOffset(node->data.assign.var);
                if (offset == -1) {
                    fprintf(stderr,
                        "CODEGEN ERROR: Variable '%s' not declared\n",
                        node->data.assign.var);
                    exit(1);
                }
                fprintf(output, "    sw   $v0, %d($sp)   # %s = call result\n",
                        offset, node->data.assign.var);
                tempReg = 0;
            } else {
                int offset = getVarOffset(node->data.assign.var);
                if (offset == -1) {
                    fprintf(stderr,
                        "CODEGEN ERROR: Variable '%s' not declared\n",
                        node->data.assign.var);
                    exit(1);
                }
                genExpr(node->data.assign.value);
                char* varType = getVarType(node->data.assign.var);
                if (varType && strcmp(varType, "float") == 0) {
                    int freg = floatReg - 2; if (freg < 0) freg = 30;
                    fprintf(output, "    swc1 $f%d, %d($sp)   # %s = ...\n",
                            freg, offset, node->data.assign.var);
                } else {
                    fprintf(output, "    sw   $t%d, %d($sp)   # %s = ...\n",
                            tempReg - 1, offset, node->data.assign.var);
                }
                tempReg = 0;
                floatReg = 0;
            }
            break;
        }

        case NODE_PRINT:
            genExpr(node->data.expr);
            if (lastExprIsFloat) {
                int freg = floatReg - 2; if (freg < 0) freg = 30;
                fprintf(output, "    # Print float\n");
                fprintf(output, "    mov.s $f12, $f%d\n", freg);
                fprintf(output, "    li    $v0, 2\n");
                fprintf(output, "    syscall\n");
            } else {
                fprintf(output, "    # Print integer\n");
                fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
                fprintf(output, "    li   $v0, 1\n");
                fprintf(output, "    syscall\n");
            }
            fprintf(output, "    # Print newline\n");
            fprintf(output, "    li   $v0, 11\n");
            fprintf(output, "    li   $a0, 10\n");
            fprintf(output, "    syscall\n");
            tempReg = 0;
            floatReg = 0;
            break;

        case NODE_FUNC_CALL:
            genFuncCall(node);
            break;

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        default:
            break;
    }
}

static void genFuncList(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        genFuncList(node->data.stmtlist.stmt);
        genFuncList(node->data.stmtlist.next);
    } else if (node->type == NODE_FUNC_DEF) {
        genFuncDef(node);
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    char tmpName[256];
    snprintf(tmpName, sizeof(tmpName), "%s.tmp", filename);

    FILE* finalOut = fopen(filename, "w");
    if (!finalOut) { fprintf(stderr, "CODEGEN ERROR: Cannot open %s\n", filename); exit(1); }
    output = fopen(tmpName, "w");
    if (!output) { fprintf(stderr, "CODEGEN ERROR: Cannot open temp %s\n", tmpName); exit(1); }

    floatConstCount = 0;
    floatReg = 0;

    fprintf(output, ".text\n");
    fprintf(output, ".globl main\n");

    if (root && root->type == NODE_PROGRAM) {
        genFuncList(root->data.program.funcs);
        fprintf(output, "\nmain:\n");
        fprintf(output, "    # Allocate global stack frame\n");
        fprintf(output, "    addi $sp, $sp, -400\n\n");
        initSymTab();
        tempReg = 0;
        if (root->data.program.globals)
            genStmt(root->data.program.globals);
        ASTNode* ps = root->data.program.start;
        if (ps && ps->type == NODE_PROGRAM_START)
            genStmt(ps->data.block.stmt_list);
        fprintf(output, "\n    # Exit program\n");
        fprintf(output, "    addi $sp, $sp, 400\n");
        fprintf(output, "    li   $v0, 10\n");
        fprintf(output, "    syscall\n");
    } else {
        fprintf(output, "\nmain:\n");
        fprintf(output, "    addi $sp, $sp, -400\n\n");
        initSymTab(); tempReg = 0;
        genStmt(root);
        fprintf(output, "\n    addi $sp, $sp, 400\n");
        fprintf(output, "    li   $v0, 10\n");
        fprintf(output, "    syscall\n");
    }
    fclose(output);

    fprintf(finalOut, "# Generated MIPS Assembly\n# ------------\n\n.data\n");
    if (root && root->type == NODE_PROGRAM) {
        ASTNode* g = root->data.program.globals;
        while (g) {
            ASTNode* decl = (g->type == NODE_STMT_LIST) ? g->data.stmtlist.stmt : g;
            if (decl && decl->type == NODE_ARRAY_DECL)
                fprintf(finalOut, "%s: .space %d\n", decl->data.array_decl.name, decl->data.array_decl.size * 4);
            g = (g->type == NODE_STMT_LIST) ? g->data.stmtlist.next : NULL;
        }
    }
    for (int i = 0; i < floatConstCount; i++) {
        char fbuf[32];
        snprintf(fbuf, sizeof(fbuf), "%g", floatConsts[i]);
        /* SPIM requires a decimal point in .float literals */
        if (!strchr(fbuf, '.') && !strchr(fbuf, 'e'))
            strncat(fbuf, ".0", sizeof(fbuf) - strlen(fbuf) - 1);
        fprintf(finalOut, "_fc%d: .float %s\n", i, fbuf);
    }
    fprintf(finalOut, "\n");
    FILE* tmp = fopen(tmpName, "r");
    if (tmp) {
        char buf[4096]; size_t n;
        while ((n = fread(buf, 1, sizeof(buf), tmp)) > 0) fwrite(buf, 1, n, finalOut);
        fclose(tmp); remove(tmpName);
    }
    fclose(finalOut);
    printf("  MIPS code written to '%s'\n", filename);
}
