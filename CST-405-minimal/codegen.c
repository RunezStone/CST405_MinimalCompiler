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
            if (offset == -1) {
                fprintf(stderr,
                    "CODEGEN ERROR: Variable '%s' not in symbol table\n",
                    node->data.name);
                exit(1);
            }
            int reg = getNextTemp();
            fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
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

    /* ── Function label ── */
    fprintf(output, "\n# ── Function: %s ──\n", node->data.func_def.name);
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

        case NODE_ASSIGN: {
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
                fprintf(output, "    sw   $t%d, %d($sp)   # %s = ...\n",
                        tempReg - 1, offset, node->data.assign.var);
                tempReg = 0;
            }
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
    fprintf(output, "# ─────────────────────────────────────\n\n");
    fprintf(output, ".data\n\n");
    fprintf(output, ".text\n");
    fprintf(output, ".globl main\n");

    /* ── UPDATED: handle NODE_PROGRAM root ── */
    if (root && root->type == NODE_PROGRAM) {

        /* 1. Emit all function definitions first (before main) */
        genFuncList(root->data.program.funcs);

        /* 2. Emit the Program_Start block as 'main' */
        fprintf(output, "\nmain:\n");
        fprintf(output, "    # Allocate global stack frame\n");
        fprintf(output, "    addi $sp, $sp, -400\n\n");

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