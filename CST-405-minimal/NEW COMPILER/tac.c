/* ============================================================================
 * OOMini  —  Three-Address Code generation (implementation)
 * Display-oriented IR: shows how OO lowers to primitive ops.
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"
#include "symtab.h"
#include "semantic.h"

static FILE* out;
static int   tempNo;
static int   labelNo;

static char* newTemp(void) {
    char* s = (char*)malloc(16);
    snprintf(s, 16, "t%d", tempNo++);
    return s;
}
static char* newLabel(void) {
    char* s = (char*)malloc(16);
    snprintf(s, 16, "L%d", labelNo++);
    return s;
}

static const char* opStr(char op) {
    switch (op) {
        case '+': return "+"; case '-': return "-";
        case '*': return "*"; case '/': return "/";
        case '<': return "<"; case '>': return ">";
        case 'l': return "<="; case 'g': return ">=";
        case 'e': return "=="; case 'n': return "!=";
        default:  return "?";
    }
}

/* Forward */
static char* genExpr(ASTNode* e);

static int genArgs(ASTNode* args) {
    /* emit param lines, return count */
    int n = 0;
    char* tmps[16];
    for (ASTNode* a = args; a && n < 16; a = a->next) tmps[n++] = genExpr(a);
    for (int i = 0; i < n; i++)
        fprintf(out, "    param %s\n", tmps[i]);
    return n;
}

static char* genExpr(ASTNode* e) {
    if (!e) return strdup("0");
    switch (e->type) {
        case NODE_NUM: {
            char* s = (char*)malloc(16);
            snprintf(s, 16, "%d", e->ival);
            return s;
        }
        case NODE_VAR:  return strdup(e->name);
        case NODE_SELF: return strdup("self");

        case NODE_BINOP: {
            char* l = genExpr(e->left);
            char* r = genExpr(e->right);
            char* t = newTemp();
            fprintf(out, "    %s = %s %s %s\n", t, l, opStr(e->op), r);
            return t;
        }
        case NODE_FIELD_ACCESS: {
            char* b = genExpr(e->base);
            char* t = newTemp();
            fprintf(out, "    %s = %s .%s          ; member load\n", t, b, e->name);
            return t;
        }
        case NODE_METHOD_CALL: {
            char* b = genExpr(e->base);
            const char* bt = exprType(e->base);
            ClassInfo* c = findClass(bt);
            MethodInfo* m = c ? findMethod(c, e->name) : NULL;
            int slot = m ? m->slot : -1;
            fprintf(out, "    param %s              ; self\n", b);
            int n = genArgs(e->args);
            char* t = newTemp();
            fprintf(out, "    %s = vcall %s.%s [slot %d], %d args  ; dynamic dispatch\n",
                    t, b, e->name, slot, n);
            return t;
        }
        case NODE_FUNC_CALL: {
            int n = genArgs(e->args);
            char* t = newTemp();
            fprintf(out, "    %s = call %s, %d args\n", t, e->name, n);
            return t;
        }
        case NODE_NEW: {
            ClassInfo* c = findClass(e->typeName);
            int sz = c ? c->objectSize : 0;
            char* t = newTemp();
            fprintf(out, "    %s = new %s(%d)        ; heap alloc + set vtable\n",
                    t, e->typeName, sz);
            MethodInfo* init = c ? findMethod(c, "init") : NULL;
            if (init) {
                fprintf(out, "    param %s              ; self\n", t);
                int n = genArgs(e->args);
                fprintf(out, "    call %s, %d args      ; constructor (resolved)\n",
                        init->label, n);
            }
            return t;
        }
        default: return strdup("0");
    }
}

static void genStmt(ASTNode* s);
static void genStmtList(ASTNode* head) { for (ASTNode* s = head; s; s = s->next) genStmt(s); }

static void genStmt(ASTNode* s) {
    if (!s) return;
    switch (s->type) {
        case NODE_DECL:
            addLocal(s->name, s->typeName);   /* keep scope in sync for exprType */
            fprintf(out, "    decl %s %s\n", s->typeName, s->name);
            break;
        case NODE_ASSIGN:
            if (s->lhsField) {
                char* b = genExpr(s->lhsField->base);
                char* v = genExpr(s->value);
                fprintf(out, "    %s .%s = %s          ; member store\n",
                        b, s->lhsField->name, v);
            } else {
                char* v = genExpr(s->value);
                fprintf(out, "    %s = %s\n", s->name, v);
            }
            break;
        case NODE_PRINT: {
            char* v = genExpr(s->value);
            fprintf(out, "    print %s\n", v);
            break;
        }
        case NODE_RETURN: {
            if (s->value) { char* v = genExpr(s->value); fprintf(out, "    return %s\n", v); }
            else fprintf(out, "    return\n");
            break;
        }
        case NODE_EXPR_STMT:
            genExpr(s->value);
            break;
        case NODE_IF: {
            char* c = genExpr(s->cond);
            char* lElse = newLabel();
            char* lEnd  = newLabel();
            fprintf(out, "    ifFalse %s goto %s\n", c, lElse);
            genStmtList(s->body);
            fprintf(out, "    goto %s\n", lEnd);
            fprintf(out, "%s:\n", lElse);
            genStmtList(s->elseBody);
            fprintf(out, "%s:\n", lEnd);
            break;
        }
        case NODE_WHILE: {
            char* lTop = newLabel();
            char* lEnd = newLabel();
            fprintf(out, "%s:\n", lTop);
            char* c = genExpr(s->cond);
            fprintf(out, "    ifFalse %s goto %s\n", c, lEnd);
            genStmtList(s->body);
            fprintf(out, "    goto %s\n", lTop);
            fprintf(out, "%s:\n", lEnd);
            break;
        }
        default: break;
    }
}

static void genFunc(ASTNode* fn, const char* className) {
    currentClassName = className;
    initScope();
    if (className) addLocal("self", (char*)className);
    for (ASTNode* p = fn->params; p; p = p->next) addLocal(p->name, p->typeName);

    if (className) fprintf(out, "func %s_%s:\n", className, fn->name);
    else           fprintf(out, "func %s:\n", fn->name);
    genStmtList(fn->body);
    fprintf(out, "endfunc\n\n");
    currentClassName = NULL;
}

void generateTAC(ASTNode* program, const char* filename) {
    out = fopen(filename, "w");
    if (!out) { perror("tac fopen"); return; }
    tempNo = 0; labelNo = 0;

    fprintf(out, "; OOMini Three-Address Code\n");
    fprintf(out, "; ----------------------------------------\n\n");

    for (ASTNode* it = program; it; it = it->next) {
        if (it->type == NODE_FUNC_DEF) {
            genFunc(it, NULL);
        } else if (it->type == NODE_CLASS_DEF) {
            for (ASTNode* m = it->members; m; m = m->next)
                if (m->type == NODE_METHOD_DEF)
                    genFunc(m, it->name);
        }
    }
    fclose(out);
    printf("TAC written to %s\n", filename);
}
