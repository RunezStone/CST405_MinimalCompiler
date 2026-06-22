/* ============================================================================
 * OOMini  —  MIPS Code Generator (implementation)
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"
#include "semantic.h"

#define FRAME 1024          /* per-call frame size in bytes */

static FILE* out;
static int   labelCtr = 0;
static char  endLabel[128];     /* epilogue label of the function being built */

static char* uniqueLabel(const char* base) {
    char* s = (char*)malloc(64);
    snprintf(s, 64, "%s%d", base, labelCtr++);
    return s;
}

/* runtime evaluation-stack helpers (operate on $sp, below the $fp frame) */
static void push_t0(void) {
    fprintf(out, "    addiu $sp, $sp, -4\n");
    fprintf(out, "    sw    $t0, 0($sp)\n");
}
static void pop_into(const char* reg) {
    fprintf(out, "    lw    %s, 0($sp)\n", reg);
    fprintf(out, "    addiu $sp, $sp, 4\n");
}

static int argCount(ASTNode* args) {
    int n = 0; for (ASTNode* a = args; a; a = a->next) n++; return n;
}

/* ----------------------------------------------------------------------------
 * Expression generation — every expression leaves its value in $t0.
 * --------------------------------------------------------------------------*/
static void genExpr(ASTNode* e);

/* Load arg registers $a(startReg..) from values already pushed on the stack.
 * Values are at offsets: arg1 at (count-1)*4($sp) ... argN at 0($sp).
 * `extraSlots` = number of words sitting *below* the args (e.g. a saved self
 * or object pointer), so the args begin at offset extraSlots? No — args are on
 * top, so arg_i is at (count-i)*4($sp) regardless. */
static void loadArgRegs(ASTNode* args, int startReg) {
    int n = argCount(args);
    int i = 0;
    for (ASTNode* a = args; a; a = a->next, i++) {
        int reg = startReg + i;
        if (reg > 3) {
            fprintf(out, "    # NOTE: arg %d exceeds $a3 (unsupported, ignored)\n", i+1);
            continue;
        }
        int off = (n - 1 - i) * 4;        /* arg_(i) sits this far up the stack */
        fprintf(out, "    lw    $a%d, %d($sp)\n", reg, off);
    }
}

static void genExpr(ASTNode* e) {
    if (!e) { fprintf(out, "    li    $t0, 0\n"); return; }

    switch (e->type) {
        case NODE_NUM:
            fprintf(out, "    li    $t0, %d\n", e->ival);
            return;

        case NODE_VAR: {
            int off = getOffset(e->name);
            fprintf(out, "    lw    $t0, %d($fp)    # %s\n", off, e->name);
            return;
        }
        case NODE_SELF: {
            int off = getOffset("self");
            fprintf(out, "    lw    $t0, %d($fp)    # self\n", off);
            return;
        }

        case NODE_BINOP: {
            genExpr(e->left);
            push_t0();
            genExpr(e->right);          /* right in $t0 */
            pop_into("$t1");            /* left in $t1  */
            switch (e->op) {
                case '+': fprintf(out, "    add   $t0, $t1, $t0\n"); break;
                case '-': fprintf(out, "    sub   $t0, $t1, $t0\n"); break;
                case '*': fprintf(out, "    mul   $t0, $t1, $t0\n"); break;
                case '/': fprintf(out, "    div   $t1, $t0\n    mflo  $t0\n"); break;
                case '<': fprintf(out, "    slt   $t0, $t1, $t0\n"); break;
                case '>': fprintf(out, "    sgt   $t0, $t1, $t0\n"); break;
                case 'l': fprintf(out, "    sle   $t0, $t1, $t0\n"); break;
                case 'g': fprintf(out, "    sge   $t0, $t1, $t0\n"); break;
                case 'e': fprintf(out, "    seq   $t0, $t1, $t0\n"); break;
                case 'n': fprintf(out, "    sne   $t0, $t1, $t0\n"); break;
            }
            return;
        }

        case NODE_FIELD_ACCESS: {
            const char* bt = exprType(e->base);
            ClassInfo* c = findClass(bt);
            FieldInfo* f = c ? findField(c, e->name) : NULL;
            int foff = f ? f->offset : 0;
            genExpr(e->base);                       /* $t0 = object pointer */
            fprintf(out, "    lw    $t0, %d($t0)    # .%s\n", foff, e->name);
            return;
        }

        case NODE_FUNC_CALL: {
            int n = argCount(e->args);
            for (ASTNode* a = e->args; a; a = a->next) { genExpr(a); push_t0(); }
            loadArgRegs(e->args, 0);                 /* $a0.. */
            fprintf(out, "    addiu $sp, $sp, %d\n", n * 4);
            if (strcmp(e->name, "main") == 0)
                fprintf(out, "    jal   main\n");
            else
                fprintf(out, "    jal   fn_%s\n", e->name);
            fprintf(out, "    move  $t0, $v0\n");
            return;
        }

        case NODE_METHOD_CALL: {
            const char* bt = exprType(e->base);
            ClassInfo* c = findClass(bt);
            MethodInfo* m = c ? findMethod(c, e->name) : NULL;
            int slot = m ? m->slot : 0;
            int n = argCount(e->args);

            genExpr(e->base);            /* $t0 = receiver pointer */
            push_t0();                   /* [self] at bottom */
            for (ASTNode* a = e->args; a; a = a->next) { genExpr(a); push_t0(); }
            /* stack now: argN(0) .. arg1((n-1)*4), self(n*4) */
            fprintf(out, "    lw    $a0, %d($sp)    # self\n", n * 4);
            loadArgRegs(e->args, 1);     /* $a1.. = args */
            fprintf(out, "    lw    $t9, 0($a0)     # vtable ptr\n");
            fprintf(out, "    lw    $t9, %d($t9)    # vtable[%d] = %s\n",
                    slot * 4, slot, e->name);
            fprintf(out, "    addiu $sp, $sp, %d\n", (n + 1) * 4);
            fprintf(out, "    jalr  $t9            # dynamic dispatch\n");
            fprintf(out, "    move  $t0, $v0\n");
            return;
        }

        case NODE_NEW: {
            ClassInfo* c = findClass(e->typeName);
            int size = c ? c->objectSize : 4;
            MethodInfo* init = c ? findMethod(c, "init") : NULL;
            int n = argCount(e->args);

            fprintf(out, "    li    $v0, 9          # sbrk: allocate object\n");
            fprintf(out, "    li    $a0, %d\n", size);
            fprintf(out, "    syscall\n");
            fprintf(out, "    move  $t0, $v0        # $t0 = new %s\n", e->typeName);
            push_t0();                               /* [obj] saved */
            fprintf(out, "    la    $t1, %s_vtable\n", e->typeName);
            fprintf(out, "    sw    $t1, 0($t0)     # install vtable\n");

            if (init) {
                for (ASTNode* a = e->args; a; a = a->next) { genExpr(a); push_t0(); }
                /* stack: argN(0)..arg1((n-1)*4), obj(n*4) */
                fprintf(out, "    lw    $a0, %d($sp)    # self (new obj)\n", n * 4);
                loadArgRegs(e->args, 1);
                fprintf(out, "    addiu $sp, $sp, %d   # pop args, keep obj\n", n * 4);
                fprintf(out, "    jal   %s            # constructor\n", init->label);
            }
            pop_into("$t0");                          /* result = object pointer */
            return;
        }

        default:
            fprintf(out, "    li    $t0, 0\n");
            return;
    }
}

/* ----------------------------------------------------------------------------
 * Statement generation
 * --------------------------------------------------------------------------*/
static void genStmt(ASTNode* s);
static void genStmtList(ASTNode* head) { for (ASTNode* s = head; s; s = s->next) genStmt(s); }

static void genStmt(ASTNode* s) {
    if (!s) return;
    switch (s->type) {
        case NODE_DECL:
            addLocal(s->name, s->typeName);
            fprintf(out, "    # decl %s %s\n", s->typeName, s->name);
            /* objects/ints default to 0/null */
            fprintf(out, "    li    $t0, 0\n");
            fprintf(out, "    sw    $t0, %d($fp)\n", getOffset(s->name));
            return;

        case NODE_ASSIGN:
            if (s->lhsField) {
                const char* bt = exprType(s->lhsField->base);
                ClassInfo* c = findClass(bt);
                FieldInfo* f = c ? findField(c, s->lhsField->name) : NULL;
                int foff = f ? f->offset : 0;
                genExpr(s->lhsField->base);     /* $t0 = obj ptr */
                push_t0();
                genExpr(s->value);              /* $t0 = value   */
                pop_into("$t1");                /* $t1 = obj ptr */
                fprintf(out, "    sw    $t0, %d($t1)    # .%s = ...\n",
                        foff, s->lhsField->name);
            } else {
                genExpr(s->value);
                fprintf(out, "    sw    $t0, %d($fp)    # %s = ...\n",
                        getOffset(s->name), s->name);
            }
            return;

        case NODE_PRINT:
            genExpr(s->value);
            fprintf(out, "    move  $a0, $t0\n");
            fprintf(out, "    li    $v0, 1          # print int\n");
            fprintf(out, "    syscall\n");
            fprintf(out, "    li    $v0, 11         # print newline\n");
            fprintf(out, "    li    $a0, 10\n");
            fprintf(out, "    syscall\n");
            return;

        case NODE_RETURN:
            if (s->value) {
                genExpr(s->value);
                fprintf(out, "    move  $v0, $t0\n");
            }
            fprintf(out, "    j     %s\n", endLabel);
            return;

        case NODE_EXPR_STMT:
            genExpr(s->value);
            return;

        case NODE_IF: {
            char* lElse = uniqueLabel("Lelse");
            char* lEnd  = uniqueLabel("Lendif");
            genExpr(s->cond);
            fprintf(out, "    beqz  $t0, %s\n", lElse);
            genStmtList(s->body);
            fprintf(out, "    j     %s\n", lEnd);
            fprintf(out, "%s:\n", lElse);
            genStmtList(s->elseBody);
            fprintf(out, "%s:\n", lEnd);
            return;
        }

        case NODE_WHILE: {
            char* lTop = uniqueLabel("Lwhile");
            char* lEnd = uniqueLabel("Lendw");
            fprintf(out, "%s:\n", lTop);
            genExpr(s->cond);
            fprintf(out, "    beqz  $t0, %s\n", lEnd);
            genStmtList(s->body);
            fprintf(out, "    j     %s\n", lTop);
            fprintf(out, "%s:\n", lEnd);
            return;
        }

        default:
            return;
    }
}

/* ----------------------------------------------------------------------------
 * Function / method prologue + body + epilogue
 * --------------------------------------------------------------------------*/
static void genFunction(ASTNode* fn, const char* className, int isMain) {
    char label[128];
    if (className)      snprintf(label, sizeof(label), "%s_%s", className, fn->name);
    else if (isMain)    snprintf(label, sizeof(label), "main");
    else                snprintf(label, sizeof(label), "fn_%s", fn->name);

    snprintf(endLabel, sizeof(endLabel), "L_end_%s", label);
    currentClassName = className;

    /* Build scope: self (methods) then params, recording offsets */
    initScope();
    int selfOff = -1;
    if (className) selfOff = addLocal("self", (char*)className);
    int pOff[8]; int pc = 0;
    for (ASTNode* p = fn->params; p; p = p->next)
        if (pc < 8) pOff[pc++] = addLocal(p->name, p->typeName);

    fprintf(out, "\n# ---- %s ----\n", label);
    fprintf(out, "%s:\n", label);
    fprintf(out, "    addiu $sp, $sp, -%d\n", FRAME);
    fprintf(out, "    sw    $ra, %d($sp)\n", FRAME - 4);
    fprintf(out, "    sw    $fp, %d($sp)\n", FRAME - 8);
    fprintf(out, "    move  $fp, $sp\n");

    /* spill incoming argument registers into the frame */
    if (className) {
        fprintf(out, "    sw    $a0, %d($fp)    # self\n", selfOff);
        for (int i = 0; i < pc; i++)
            if (i + 1 <= 3) fprintf(out, "    sw    $a%d, %d($fp)    # param\n", i + 1, pOff[i]);
    } else {
        for (int i = 0; i < pc; i++)
            if (i <= 3) fprintf(out, "    sw    $a%d, %d($fp)    # param\n", i, pOff[i]);
    }

    genStmtList(fn->body);

    /* epilogue */
    fprintf(out, "%s:\n", endLabel);
    if (isMain) {
        fprintf(out, "    li    $v0, 10         # exit\n");
        fprintf(out, "    syscall\n");
    } else {
        fprintf(out, "    move  $sp, $fp\n");
        fprintf(out, "    lw    $ra, %d($sp)\n", FRAME - 4);
        fprintf(out, "    lw    $fp, %d($sp)\n", FRAME - 8);
        fprintf(out, "    addiu $sp, $sp, %d\n", FRAME);
        fprintf(out, "    jr    $ra\n");
    }
    currentClassName = NULL;
}

/* ----------------------------------------------------------------------------
 * Top-level driver
 * --------------------------------------------------------------------------*/
void generateMIPS(ASTNode* program, const char* filename) {
    out = fopen(filename, "w");
    if (!out) { perror("codegen fopen"); return; }

    fprintf(out, "# ============================================\n");
    fprintf(out, "#  OOMini -> MIPS   (run with: spim -file %s)\n", filename);
    fprintf(out, "# ============================================\n\n");

    /* .data : one vtable per class */
    fprintf(out, ".data\n");
    for (int i = 0; i < classCount; i++) {
        ClassInfo* c = &classes[i];
        fprintf(out, "%s_vtable:", c->name);
        if (c->methodCount == 0) {
            fprintf(out, " .word 0");
        } else {
            fprintf(out, " .word ");
            for (int j = 0; j < c->methodCount; j++)
                fprintf(out, "%s%s", c->methods[j].label,
                        j + 1 < c->methodCount ? ", " : "");
        }
        fprintf(out, "\n");
    }

    fprintf(out, "\n.text\n.globl main\n");

    /* free functions (main emitted with exit epilogue) */
    for (ASTNode* it = program; it; it = it->next)
        if (it->type == NODE_FUNC_DEF)
            genFunction(it, NULL, strcmp(it->name, "main") == 0);

    /* methods */
    for (ASTNode* it = program; it; it = it->next)
        if (it->type == NODE_CLASS_DEF)
            for (ASTNode* m = it->members; m; m = m->next)
                if (m->type == NODE_METHOD_DEF)
                    genFunction(m, it->name, 0);

    fclose(out);
    printf("MIPS written to %s\n", filename);
}
