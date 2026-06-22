/* ============================================================================
 * OOMini  —  Semantic Analyzer (implementation)
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symtab.h"

static int errors = 0;
const char* currentClassName = NULL;   /* enclosing class during a method */
static const char* currentRetType = NULL;

static void err(int line, const char* fmt, const char* a) {
    errors++;
    fprintf(stderr, "Semantic error (line %d): ", line);
    fprintf(stderr, fmt, a);
    fprintf(stderr, "\n");
}

static int argCount(ASTNode* args) {
    int n = 0;
    for (ASTNode* a = args; a; a = a->next) n++;
    return n;
}
static int paramCount(ASTNode* params) {
    int n = 0;
    for (ASTNode* p = params; p; p = p->next) n++;
    return n;
}

static int isClassType(const char* t) {
    return t && strcmp(t, "int") != 0 && strcmp(t, "void") != 0;
}

/* ----------------------------------------------------------------------------
 * Static-type resolver (shared with codegen). Reports errors as a side effect.
 * --------------------------------------------------------------------------*/
const char* exprType(ASTNode* e) {
    if (!e) return "int";
    switch (e->type) {
        case NODE_NUM:   return "int";
        case NODE_BINOP: return "int";   /* arithmetic & relational both int */
        case NODE_VAR: {
            char* t = getVarType(e->name);
            if (!t) { err(e->lineno, "use of undeclared variable '%s'", e->name); return "int"; }
            return t;
        }
        case NODE_SELF:
            if (!currentClassName) { err(e->lineno, "%s", "'self' used outside a method"); return "int"; }
            return currentClassName;
        case NODE_FIELD_ACCESS: {
            const char* bt = exprType(e->base);
            ClassInfo* c = findClass(bt);
            if (!c) { err(e->lineno, "field access on non-object of type '%s'", bt); return "int"; }
            FieldInfo* f = findField(c, e->name);
            if (!f) { err(e->lineno, "no such field '%s'", e->name); return "int"; }
            return f->type;
        }
        case NODE_METHOD_CALL: {
            const char* bt = exprType(e->base);
            ClassInfo* c = findClass(bt);
            if (!c) { err(e->lineno, "method call on non-object of type '%s'", bt); return "int"; }
            MethodInfo* m = findMethod(c, e->name);
            if (!m) { err(e->lineno, "no such method '%s'", e->name); return "int"; }
            if (argCount(e->args) != m->paramCount)
                err(e->lineno, "wrong argument count for method '%s'", e->name);
            for (ASTNode* a = e->args; a; a = a->next) exprType(a);
            return m->retType;
        }
        case NODE_FUNC_CALL: {
            FuncInfo* f = findFunc(e->name);
            if (!f) { err(e->lineno, "call to undefined function '%s'", e->name); return "int"; }
            if (argCount(e->args) != f->paramCount)
                err(e->lineno, "wrong argument count for function '%s'", e->name);
            for (ASTNode* a = e->args; a; a = a->next) exprType(a);
            return f->retType;
        }
        case NODE_NEW: {
            ClassInfo* c = findClass(e->typeName);
            if (!c) { err(e->lineno, "'new' of unknown class '%s'", e->typeName); return "int"; }
            MethodInfo* init = findMethod(c, "init");
            int n = argCount(e->args);
            if (init) {
                if (n != init->paramCount)
                    err(e->lineno, "wrong argument count for constructor of '%s'", e->typeName);
            } else if (n != 0) {
                err(e->lineno, "class '%s' has no constructor but args were given", e->typeName);
            }
            for (ASTNode* a = e->args; a; a = a->next) exprType(a);
            return e->typeName;
        }
        default:
            return "int";
    }
}

/* ----------------------------------------------------------------------------
 * Statement checking
 * --------------------------------------------------------------------------*/
static void checkStmt(ASTNode* s);

static void checkStmtList(ASTNode* head) {
    for (ASTNode* s = head; s; s = s->next) checkStmt(s);
}

static void checkStmt(ASTNode* s) {
    if (!s) return;
    switch (s->type) {
        case NODE_DECL:
            if (isClassType(s->typeName) && !findClass(s->typeName))
                err(s->lineno, "unknown type '%s' in declaration", s->typeName);
            if (getOffset(s->name) != -1)
                err(s->lineno, "redeclaration of '%s'", s->name);
            addLocal(s->name, s->typeName);
            break;

        case NODE_ASSIGN:
            if (s->lhsField) {
                exprType(s->lhsField);          /* validates object.field      */
            } else {
                if (getVarType(s->name) == NULL)
                    err(s->lineno, "assignment to undeclared variable '%s'", s->name);
            }
            exprType(s->value);
            break;

        case NODE_PRINT:
            exprType(s->value);
            break;

        case NODE_RETURN:
            if (s->value) exprType(s->value);
            if (s->value && currentRetType && strcmp(currentRetType, "void") == 0)
                err(s->lineno, "%s", "returning a value from a void function");
            break;

        case NODE_EXPR_STMT:
            exprType(s->value);
            break;

        case NODE_IF:
            exprType(s->cond);
            checkStmtList(s->body);
            checkStmtList(s->elseBody);
            break;

        case NODE_WHILE:
            exprType(s->cond);
            checkStmtList(s->body);
            break;

        default:
            break;
    }
}

/* ----------------------------------------------------------------------------
 * Pass 1 — register classes & functions
 * --------------------------------------------------------------------------*/
static void registerClassDef(ASTNode* cd) {
    if (cd->parentName && !findClass(cd->parentName)) {
        err(cd->lineno, "parent class '%s' must be defined before its subclass",
            cd->parentName);
        /* register without parent so later checks still find the class */
    }
    ClassInfo* c = registerClass(cd->name, findClass(cd->parentName ? cd->parentName : "")
                                           ? cd->parentName : NULL);
    if (!c) {
        if (findClass(cd->name)) err(cd->lineno, "duplicate class '%s'", cd->name);
        return;
    }
    for (ASTNode* m = cd->members; m; m = m->next) {
        if (m->type == NODE_FIELD_DEF) {
            if (!addField(c, m->name, m->typeName))
                err(m->lineno, "duplicate field '%s'", m->name);
        } else if (m->type == NODE_METHOD_DEF) {
            addMethod(c, c->name, m->name, m->typeName, paramCount(m->params));
        }
    }
}

/* ----------------------------------------------------------------------------
 * Pass 2 — check bodies
 * --------------------------------------------------------------------------*/
static void checkFuncBody(ASTNode* fn, const char* className) {
    currentClassName = className;
    currentRetType   = fn->typeName;
    initScope();
    if (className) addLocal("self", (char*)className);   /* implicit receiver */
    for (ASTNode* p = fn->params; p; p = p->next) {
        if (isClassType(p->typeName) && !findClass(p->typeName))
            err(p->lineno, "unknown parameter type '%s'", p->typeName);
        addLocal(p->name, p->typeName);
    }
    checkStmtList(fn->body);
    currentClassName = NULL;
    currentRetType   = NULL;
}

int analyze(ASTNode* program) {
    errors = 0;
    initClasses();
    initFuncs();

    /* Pass 1a: classes (source order so parents precede children) */
    for (ASTNode* it = program; it; it = it->next)
        if (it->type == NODE_CLASS_DEF) registerClassDef(it);

    /* Pass 1b: free functions */
    for (ASTNode* it = program; it; it = it->next)
        if (it->type == NODE_FUNC_DEF) {
            if (!registerFunc(it->name, it->typeName, paramCount(it->params)))
                err(it->lineno, "duplicate function '%s'", it->name);
        }

    /* main() must exist */
    FuncInfo* mainF = findFunc("main");
    if (!mainF)
        err(0, "%s", "program has no 'func void main()' entry point");
    else if (mainF->paramCount != 0)
        err(0, "%s", "'main' must take no parameters");

    /* Pass 2: bodies */
    for (ASTNode* it = program; it; it = it->next) {
        if (it->type == NODE_FUNC_DEF) {
            checkFuncBody(it, NULL);
        } else if (it->type == NODE_CLASS_DEF) {
            for (ASTNode* m = it->members; m; m = m->next)
                if (m->type == NODE_METHOD_DEF)
                    checkFuncBody(m, it->name);
        }
    }

    if (errors == 0)
        printf("Semantic analysis: OK (no errors)\n");
    else
        printf("Semantic analysis: %d error(s) found\n", errors);
    return errors;
}
