#ifndef AST_H
#define AST_H

/* ============================================================================
 * OOMini  —  Abstract Syntax Tree
 * ----------------------------------------------------------------------------
 * OOMini is the object-oriented successor to the CST-405 minimal language.
 * It adds classes, single inheritance (extends), methods, constructors,
 * heap-allocated objects (new), the `self` receiver, and runtime
 * polymorphism via per-class vtables.
 *
 * Program structure:
 *     <class definitions>
 *     <free function definitions>
 *     func main() { ... }          // entry point
 *
 * To keep the tree small and robust, every construct is represented by ONE
 * generic node struct (no tagged union). Unused fields are simply NULL/0.
 * Lists (statements, params, args, class members, top-level items) are
 * singly linked through the `next` pointer.
 * ==========================================================================*/

typedef enum {
    /* ---- Expressions ---- */
    NODE_NUM,           /* integer literal              42                 */
    NODE_VAR,           /* variable reference           x                  */
    NODE_SELF,          /* the receiver inside a method self               */
    NODE_BINOP,         /* binary op (arith + relational) a + b, a < b     */
    NODE_FIELD_ACCESS,  /* field read                   obj.field          */
    NODE_METHOD_CALL,   /* dynamic dispatch             obj.m(args)        */
    NODE_FUNC_CALL,     /* free function call           f(args)            */
    NODE_NEW,           /* object allocation            new Class(args)    */

    /* ---- Statements ---- */
    NODE_DECL,          /* declaration       int x;   /  Animal a;         */
    NODE_ASSIGN,        /* assignment        x = e;   /  obj.field = e;     */
    NODE_PRINT,         /* print(e);                                       */
    NODE_IF,            /* if (c) {..} else {..}                           */
    NODE_WHILE,         /* while (c) {..}                                  */
    NODE_RETURN,        /* return e;  /  return;                           */
    NODE_EXPR_STMT,     /* expression used as a statement (e.g. obj.m();)  */
    NODE_STMT_LIST,     /* a statement followed by more (via ->next)       */

    /* ---- Declarations / definitions ---- */
    NODE_PARAM,         /* one formal parameter         int a / Animal a   */
    NODE_FUNC_DEF,      /* free function definition                        */
    NODE_METHOD_DEF,    /* method definition inside a class                */
    NODE_FIELD_DEF,     /* field declaration inside a class                */
    NODE_CLASS_DEF      /* class C extends P { fields; methods; }          */
} NodeType;

typedef struct ASTNode {
    NodeType type;
    int      lineno;

    /* literal / operator payloads */
    int   ival;        /* NODE_NUM value                                   */
    char  op;          /* NODE_BINOP: + - * / < > l(<=) g(>=) e(==) n(!=)  */

    /* identifiers / type names */
    char* name;        /* var / field / method / func / class / param name */
    char* typeName;    /* declared type or class name or method return type*/
    char* parentName;  /* NODE_CLASS_DEF: parent class, or NULL            */

    /* sub-trees (only the relevant ones are set per node type) */
    struct ASTNode* left;     /* binop left operand                        */
    struct ASTNode* right;    /* binop right operand                       */
    struct ASTNode* base;     /* receiver of field access / method call    */
    struct ASTNode* args;     /* argument list head (chained via next)     */
    struct ASTNode* params;   /* parameter list head                       */
    struct ASTNode* body;     /* function/method/if/while body (stmt list) */
    struct ASTNode* cond;     /* if/while condition                        */
    struct ASTNode* elseBody; /* if's else branch                          */
    struct ASTNode* value;    /* assign RHS / return value / print expr    */
    struct ASTNode* members;  /* class member list (fields + methods)      */

    /* assignment target: either a var name (use `name`) or a field LHS */
    struct ASTNode* lhsField; /* non-NULL => assigning to obj.field        */

    struct ASTNode* next;     /* generic list linkage                      */
} ASTNode;

/* ---- Expression constructors ---- */
ASTNode* newNum(int v);
ASTNode* newVar(char* name);
ASTNode* newSelf(void);
ASTNode* newBinOp(char op, ASTNode* l, ASTNode* r);
ASTNode* newFieldAccess(ASTNode* base, char* field);
ASTNode* newMethodCall(ASTNode* base, char* method, ASTNode* args);
ASTNode* newFuncCall(char* name, ASTNode* args);
ASTNode* newNewObj(char* className, ASTNode* args);

/* ---- Statement constructors ---- */
ASTNode* newDecl(char* typeName, char* name);
ASTNode* newAssignVar(char* name, ASTNode* value);
ASTNode* newAssignField(ASTNode* fieldAccess, ASTNode* value);
ASTNode* newPrint(ASTNode* e);
ASTNode* newIf(ASTNode* cond, ASTNode* thenB, ASTNode* elseB);
ASTNode* newWhile(ASTNode* cond, ASTNode* body);
ASTNode* newReturn(ASTNode* value);
ASTNode* newExprStmt(ASTNode* e);

/* ---- Definition constructors ---- */
ASTNode* newParam(char* typeName, char* name);
ASTNode* newFuncDef(char* retType, char* name, ASTNode* params, ASTNode* body);
ASTNode* newMethodDef(char* retType, char* name, ASTNode* params, ASTNode* body);
ASTNode* newFieldDef(char* typeName, char* name);
ASTNode* newClassDef(char* name, char* parent, ASTNode* members);

/* ---- List helpers (append b to the end of list a; return head) ---- */
ASTNode* listAppend(ASTNode* listHead, ASTNode* node);

/* ---- Debug ---- */
void printAST(ASTNode* node, int indent);

#endif /* AST_H */
