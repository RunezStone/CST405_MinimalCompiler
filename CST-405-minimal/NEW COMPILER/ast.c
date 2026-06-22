/* ============================================================================
 * OOMini  —  AST construction & debug printing
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;

static ASTNode* alloc(NodeType t) {
    ASTNode* n = (ASTNode*)calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "out of memory building AST\n"); exit(1); }
    n->type   = t;
    n->lineno = yylineno;
    return n;
}

static char* dup(const char* s) {
    if (!s) return NULL;
    char* p = (char*)malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

/* ---- Expressions ---- */
ASTNode* newNum(int v)            { ASTNode* n = alloc(NODE_NUM);  n->ival = v;        return n; }
ASTNode* newVar(char* name)       { ASTNode* n = alloc(NODE_VAR);  n->name = dup(name); return n; }
ASTNode* newSelf(void)            { return alloc(NODE_SELF); }

ASTNode* newBinOp(char op, ASTNode* l, ASTNode* r) {
    ASTNode* n = alloc(NODE_BINOP);
    n->op = op; n->left = l; n->right = r;
    return n;
}
ASTNode* newFieldAccess(ASTNode* base, char* field) {
    ASTNode* n = alloc(NODE_FIELD_ACCESS);
    n->base = base; n->name = dup(field);
    return n;
}
ASTNode* newMethodCall(ASTNode* base, char* method, ASTNode* args) {
    ASTNode* n = alloc(NODE_METHOD_CALL);
    n->base = base; n->name = dup(method); n->args = args;
    return n;
}
ASTNode* newFuncCall(char* name, ASTNode* args) {
    ASTNode* n = alloc(NODE_FUNC_CALL);
    n->name = dup(name); n->args = args;
    return n;
}
ASTNode* newNewObj(char* className, ASTNode* args) {
    ASTNode* n = alloc(NODE_NEW);
    n->typeName = dup(className); n->args = args;
    return n;
}

/* ---- Statements ---- */
ASTNode* newDecl(char* typeName, char* name) {
    ASTNode* n = alloc(NODE_DECL);
    n->typeName = dup(typeName); n->name = dup(name);
    return n;
}
ASTNode* newAssignVar(char* name, ASTNode* value) {
    ASTNode* n = alloc(NODE_ASSIGN);
    n->name = dup(name); n->value = value;
    return n;
}
ASTNode* newAssignField(ASTNode* fieldAccess, ASTNode* value) {
    ASTNode* n = alloc(NODE_ASSIGN);
    n->lhsField = fieldAccess; n->value = value;
    return n;
}
ASTNode* newPrint(ASTNode* e)  { ASTNode* n = alloc(NODE_PRINT);  n->value = e; return n; }
ASTNode* newReturn(ASTNode* e) { ASTNode* n = alloc(NODE_RETURN); n->value = e; return n; }
ASTNode* newExprStmt(ASTNode* e){ASTNode* n = alloc(NODE_EXPR_STMT);n->value = e; return n; }

ASTNode* newIf(ASTNode* cond, ASTNode* thenB, ASTNode* elseB) {
    ASTNode* n = alloc(NODE_IF);
    n->cond = cond; n->body = thenB; n->elseBody = elseB;
    return n;
}
ASTNode* newWhile(ASTNode* cond, ASTNode* body) {
    ASTNode* n = alloc(NODE_WHILE);
    n->cond = cond; n->body = body;
    return n;
}

/* ---- Definitions ---- */
ASTNode* newParam(char* typeName, char* name) {
    ASTNode* n = alloc(NODE_PARAM);
    n->typeName = dup(typeName); n->name = dup(name);
    return n;
}
ASTNode* newFuncDef(char* retType, char* name, ASTNode* params, ASTNode* body) {
    ASTNode* n = alloc(NODE_FUNC_DEF);
    n->typeName = dup(retType); n->name = dup(name);
    n->params = params; n->body = body;
    return n;
}
ASTNode* newMethodDef(char* retType, char* name, ASTNode* params, ASTNode* body) {
    ASTNode* n = alloc(NODE_METHOD_DEF);
    n->typeName = dup(retType); n->name = dup(name);
    n->params = params; n->body = body;
    return n;
}
ASTNode* newFieldDef(char* typeName, char* name) {
    ASTNode* n = alloc(NODE_FIELD_DEF);
    n->typeName = dup(typeName); n->name = dup(name);
    return n;
}
ASTNode* newClassDef(char* name, char* parent, ASTNode* members) {
    ASTNode* n = alloc(NODE_CLASS_DEF);
    n->name = dup(name); n->parentName = dup(parent); n->members = members;
    return n;
}

/* ---- List helper ---- */
ASTNode* listAppend(ASTNode* head, ASTNode* node) {
    if (!head) return node;
    if (!node) return head;
    ASTNode* p = head;
    while (p->next) p = p->next;
    p->next = node;
    return head;
}

/* ---- Debug printing ---- */
static void pad(int n) { for (int i = 0; i < n; i++) printf("  "); }

static const char* opName(char op) {
    switch (op) {
        case '+': return "+";  case '-': return "-";
        case '*': return "*";  case '/': return "/";
        case '<': return "<";  case '>': return ">";
        case 'l': return "<="; case 'g': return ">=";
        case 'e': return "=="; case 'n': return "!=";
        default:  return "?";
    }
}

void printAST(ASTNode* node, int indent) {
    if (!node) return;
    pad(indent);
    switch (node->type) {
        case NODE_NUM:    printf("Num %d\n", node->ival); break;
        case NODE_VAR:    printf("Var %s\n", node->name); break;
        case NODE_SELF:   printf("self\n"); break;
        case NODE_BINOP:
            printf("BinOp %s\n", opName(node->op));
            printAST(node->left, indent+1);
            printAST(node->right, indent+1);
            break;
        case NODE_FIELD_ACCESS:
            printf("FieldAccess .%s\n", node->name);
            printAST(node->base, indent+1);
            break;
        case NODE_METHOD_CALL:
            printf("MethodCall .%s()\n", node->name);
            printAST(node->base, indent+1);
            for (ASTNode* a = node->args; a; a = a->next) printAST(a, indent+1);
            break;
        case NODE_FUNC_CALL:
            printf("FuncCall %s()\n", node->name);
            for (ASTNode* a = node->args; a; a = a->next) printAST(a, indent+1);
            break;
        case NODE_NEW:
            printf("New %s\n", node->typeName);
            for (ASTNode* a = node->args; a; a = a->next) printAST(a, indent+1);
            break;
        case NODE_DECL:
            printf("Decl %s %s\n", node->typeName, node->name);
            break;
        case NODE_ASSIGN:
            if (node->lhsField) {
                printf("Assign (field)\n");
                printAST(node->lhsField, indent+1);
            } else {
                printf("Assign %s\n", node->name);
            }
            printAST(node->value, indent+1);
            break;
        case NODE_PRINT:
            printf("Print\n"); printAST(node->value, indent+1); break;
        case NODE_RETURN:
            printf("Return\n"); printAST(node->value, indent+1); break;
        case NODE_EXPR_STMT:
            printf("ExprStmt\n"); printAST(node->value, indent+1); break;
        case NODE_IF:
            printf("If\n");
            pad(indent+1); printf("cond:\n");  printAST(node->cond, indent+2);
            pad(indent+1); printf("then:\n");  printAST(node->body, indent+2);
            if (node->elseBody) { pad(indent+1); printf("else:\n"); printAST(node->elseBody, indent+2); }
            break;
        case NODE_WHILE:
            printf("While\n");
            pad(indent+1); printf("cond:\n"); printAST(node->cond, indent+2);
            pad(indent+1); printf("body:\n"); printAST(node->body, indent+2);
            break;
        case NODE_PARAM:
            printf("Param %s %s\n", node->typeName, node->name); break;
        case NODE_FIELD_DEF:
            printf("Field %s %s\n", node->typeName, node->name); break;
        case NODE_METHOD_DEF:
            printf("Method %s %s\n", node->typeName, node->name);
            for (ASTNode* p = node->params; p; p = p->next) printAST(p, indent+1);
            printAST(node->body, indent+1);
            break;
        case NODE_FUNC_DEF:
            printf("Func %s %s\n", node->typeName, node->name);
            for (ASTNode* p = node->params; p; p = p->next) printAST(p, indent+1);
            printAST(node->body, indent+1);
            break;
        case NODE_CLASS_DEF:
            printf("Class %s%s%s\n", node->name,
                   node->parentName ? " extends " : "",
                   node->parentName ? node->parentName : "");
            for (ASTNode* m = node->members; m; m = m->next) printAST(m, indent+1);
            break;
        case NODE_STMT_LIST:
            printf("StmtList\n"); break;
    }
    /* Print following statements in a list */
    if (node->type == NODE_DECL || node->type == NODE_ASSIGN ||
        node->type == NODE_PRINT || node->type == NODE_RETURN ||
        node->type == NODE_IF || node->type == NODE_WHILE ||
        node->type == NODE_EXPR_STMT) {
        printAST(node->next, indent);
    }
}
