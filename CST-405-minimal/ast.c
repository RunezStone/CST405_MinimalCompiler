/* AST IMPLEMENTATION
 * Functions to create and manipulate Abstract Syntax Tree nodes.
 * The AST is built during parsing and used by every subsequent phase.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Line number provided by the scanner */
extern int yylineno;

/* ─────────────────────────────────────────────────────────────────────────
 * EXPRESSION NODES
 * ───────────────────────────────────────────────────────────────────────── */

/* When the scanner sees a float literal, it sets these before returning NUM.
 * createNum() checks them so the parser doesn't need a new FNUM token type. */
int   pendingFloatLit   = 0;   /* 1 = next NUM is actually a float */
float pendingFloatValue = 0.0f;

/* Create a numeric literal node.
 * If the scanner flagged a pending float, produce NODE_FLOAT instead. */
ASTNode* createNum(int value) {
    if (pendingFloatLit) {
        pendingFloatLit = 0;
        return createFloat(pendingFloatValue);
    }
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type        = NODE_NUM;
    node->lineno      = yylineno;
    node->data.num    = value;
    return node;
}

/* Create a float literal node */
ASTNode* createFloat(float value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type        = NODE_FLOAT;
    node->lineno      = yylineno;
    node->data.fval   = value;
    return node;
}

/* Create a variable reference node */
ASTNode* createVar(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type        = NODE_VAR;
    node->lineno      = yylineno;
    node->data.name   = strdup(name);
    return node;
}

/* Create a binary (or unary-minus) operation node.
 * op codes:  '+' '-' '*' '/' '<' '>'
 *            'l' = <=   'g' = >=   'e' = ==   'n' = !=
 *            'u' = unary minus (right == NULL)              */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type              = NODE_BINOP;
    node->lineno            = yylineno;
    node->data.binop.op     = op;
    node->data.binop.left   = left;
    node->data.binop.right  = right;
    return node;
}

/* ─────────────────────────────────────────────────────────────────────────
 * STATEMENT NODES
 * ───────────────────────────────────────────────────────────────────────── */

/* Create a scalar variable declaration node */
ASTNode* createDecl(char* type, char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type               = NODE_DECL;
    node->lineno             = yylineno;
    node->data.decl.name     = strdup(name);
    node->data.decl.varType  = strdup(type);
    return node;
}

/* Create an assignment node.
 *   Scalar assign:  var != NULL, arrayLHS set to NULL by default.
 *   Array assign:   var == NULL, caller sets arrayLHS after creation.  */
ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                  = NODE_ASSIGN;
    node->lineno                = yylineno;
    node->data.assign.var       = var ? strdup(var) : NULL;
    node->data.assign.value     = value;
    node->data.assign.arrayLHS  = NULL;   /* set by parser for arr[i] = ... */
    node->data.assign.structLHS = NULL;   /* set by parser for p is f = ... */
    return node;
}

/* Create a print statement node */
ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type       = NODE_PRINT;
    node->lineno     = yylineno;
    node->data.expr  = expr;
    return node;
}

/* Create a statement-list node linking two statements together.
 * Builds a right-leaning linked list:  stmt1 → stmt2             */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type               = NODE_STMT_LIST;
    node->lineno             = stmt1 ? stmt1->lineno
                                     : (stmt2 ? stmt2->lineno : yylineno);
    node->data.stmtlist.stmt = stmt1;
    node->data.stmtlist.next = stmt2;
    return node;
}

/* ─────────────────────────────────────────────────────────────────────────
 * MULTI-DECLARATION HELPERS  (parser-internal; never reach later phases)
 * ───────────────────────────────────────────────────────────────────────── */

/* Create the first node of a comma-separated identifier list */
ASTNode* createIdList(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type              = NODE_ID_LIST;
    node->lineno            = yylineno;
    node->data.idlist.name  = strdup(name);
    node->data.idlist.next  = NULL;
    return node;
}

/* Append a new identifier to the END of an id-list chain */
ASTNode* appendIdList(ASTNode* list, char* name) {
    ASTNode* curr = list;
    while (curr->data.idlist.next != NULL)
        curr = curr->data.idlist.next;
    curr->data.idlist.next = createIdList(name);
    return list;   /* return the original head */
}

/* Expand an id_list into a chain of individual NODE_DECL nodes linked
 * as a STMT_LIST.  e.g.  id_list(x→y→z) becomes
 *   STMT_LIST(DECL(x), STMT_LIST(DECL(y), DECL(z)))               */
ASTNode* createMultiDecl(ASTNode* id_list) {
    return createMultiDeclTyped(id_list, "int");
}

ASTNode* createMultiDeclTyped(ASTNode* id_list, char* type) {
    ASTNode* result = NULL;
    ASTNode* curr   = id_list;
    while (curr != NULL) {
        ASTNode* decl = createDecl(type, curr->data.idlist.name);
        if (result == NULL) {
            result = decl;
        } else {
            result = createStmtList(result, decl);
        }
        curr = curr->data.idlist.next;
    }
    return result;
}

/* ─────────────────────────────────────────────────────────────────────────
 * FUNCTION NODES
 * ───────────────────────────────────────────────────────────────────────── */

/* Create the end clause node.
 *   returnVar == NULL  → "end null;"  (void function)
 *   returnVar != NULL  → "end x;"     (returns variable x)           */
ASTNode* createEndClause(char* returnVar) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type        = NODE_END_CLAUSE;
    node->lineno      = yylineno;
    node->data.name   = returnVar ? strdup(returnVar) : NULL;
    return node;
}

/* Create a function declaration node.
 *   func name(params) <body> end <clause>;
 *
 *   params     — NODE_PARAM_LIST chain, or NULL for no parameters
 *   body       — NODE_STMT_LIST of the function body, or NULL if empty
 *   end_clause — NODE_END_CLAUSE node produced by createEndClause()   */
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body,
                         ASTNode* end_clause) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                       = NODE_FUNC_DEF;
    node->lineno                     = yylineno;
    node->data.func_def.name         = strdup(name);
    node->data.func_def.params       = params;
    node->data.func_def.body         = body;
    node->data.func_def.end_clause   = end_clause;
    return node;
}

/* Create a function call node */
ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                 = NODE_FUNC_CALL;
    node->lineno               = yylineno;
    node->data.func_call.name  = strdup(name);
    node->data.func_call.args  = args;
    return node;
}

/* Create a single scalar parameter node  "int name" */
ASTNode* createParam(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type             = NODE_PARAM;
    node->lineno           = yylineno;
    node->data.param.name  = strdup(name);
    return node;
}

/* Create a parameter-list node linking two parameter nodes.
 * Used internally by appendParamList().                              */
ASTNode* createParamList(ASTNode* param, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                   = NODE_PARAM_LIST;
    node->lineno                 = param ? param->lineno : yylineno;
    node->data.param_list.param  = param;
    node->data.param_list.next   = next;
    return node;
}

/* Append a new parameter to the END of a param-list chain.
 * The first param passed from the parser is wrapped in createParamList()
 * so this always receives a list head, never a raw NODE_PARAM.       */
ASTNode* appendParamList(ASTNode* list, ASTNode* param) {
    /* Walk to the last node in the chain */
    ASTNode* curr = list;
    while (curr->data.param_list.next != NULL)
        curr = curr->data.param_list.next;
    curr->data.param_list.next = createParamList(param, NULL);
    return list;   /* return the original head */
}

/* Create an arg-list node from a single expression.
 * Called by the parser for the first argument in a call.             */
ASTNode* createArgList(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type              = NODE_ARG_LIST;
    node->lineno            = expr ? expr->lineno : yylineno;
    node->data.arg_list.expr = expr;
    node->data.arg_list.next = NULL;
    return node;
}

/* Append a new expression to the END of an arg-list chain.
 * Called by the parser for each subsequent argument.                 */
ASTNode* appendArgList(ASTNode* list, ASTNode* expr) {
    ASTNode* curr = list;
    while (curr->data.arg_list.next != NULL)
        curr = curr->data.arg_list.next;
    curr->data.arg_list.next = createArgList(expr);
    return list;   /* return the original head */
}

/* Create the Program_Start() entry-point node.
 *   body       — NODE_STMT_LIST of the entry block
 *   end_clause — NODE_END_CLAUSE (always "end null;" for Program_Start) */
ASTNode* createProgramStart(ASTNode* body, ASTNode* end_clause) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                    = NODE_PROGRAM_START;
    node->lineno                  = yylineno;
    node->data.block.stmt_list    = body;
    node->data.block.end_clause   = end_clause;
    return node;
}

/* Create the root program node.
 *   globals — STMT_LIST of global declarations (may be NULL)
 *   funcs   — STMT_LIST of function definitions (may be NULL)
 *   start   — NODE_PROGRAM_START block                               */
ASTNode* createProgram(ASTNode* globals, ASTNode* funcs, ASTNode* start) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                  = NODE_PROGRAM;
    node->lineno                = yylineno;
    node->data.program.globals  = globals;
    node->data.program.funcs    = funcs;
    node->data.program.start    = start;
    return node;
}

/* ─────────────────────────────────────────────────────────────────────────
 * CONTROL-FLOW NODES
 * ───────────────────────────────────────────────────────────────────────── */

/* Create an if / if-else statement node */
ASTNode* createIf(ASTNode* condition, ASTNode* then_stmt,
                   ASTNode* else_stmt) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                   = NODE_IF;
    node->lineno                 = yylineno;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_stmt = then_stmt;
    node->data.if_stmt.else_stmt = else_stmt;
    return node;
}

/* Create a while loop node */
ASTNode* createWhile(ASTNode* condition, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                     = NODE_WHILE;
    node->lineno                   = yylineno;
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body      = body;
    return node;
}

/* Create a C-style while loop node
 *   "while (init; condition; update) <body> continue;"
 * init/update are NODE_ASSIGN nodes built from assign_init.            */
ASTNode* createForWhile(ASTNode* init, ASTNode* condition,
                         ASTNode* update, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                       = NODE_FOR_WHILE;
    node->lineno                     = yylineno;
    node->data.for_while.init        = init;
    node->data.for_while.condition   = condition;
    node->data.for_while.update      = update;
    node->data.for_while.body        = body;
    return node;
}

/* Create a braced block node { stmt_list } */
ASTNode* createBlock(ASTNode* stmt_list) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                  = NODE_BLOCK;
    node->lineno                = yylineno;
    node->data.block.stmt_list  = stmt_list;
    node->data.block.end_clause = NULL;
    return node;
}

/* ─────────────────────────────────────────────────────────────────────────
 * ARRAY NODES
 * ───────────────────────────────────────────────────────────────────────── */

/* Create an array declaration  int arr[size]; */
ASTNode* createArrayDecl(char* name, int size) {
    return createArrayDeclTyped(name, size, "int");
}

ASTNode* createArrayDeclTyped(char* name, int size, char* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                      = NODE_ARRAY_DECL;
    node->lineno                    = yylineno;
    node->data.array_decl.name      = strdup(name);
    node->data.array_decl.varType   = strdup(type);
    node->data.array_decl.size      = size;
    node->data.array_decl.isParam   = 0;
    return node;
}

/* Create an array parameter node  int arr[]  (size unknown = 0) */
ASTNode* createArrayParam(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                      = NODE_ARRAY_DECL;
    node->lineno                    = yylineno;
    node->data.array_decl.name      = strdup(name);
    node->data.array_decl.varType   = strdup("int");
    node->data.array_decl.size      = 0;
    node->data.array_decl.isParam   = 1;
    return node;
}

/* Create an array index node  arr[index_expr] */
ASTNode* createArrayIndex(char* name, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                   = NODE_ARRAY_INDEX;
    node->lineno                 = yylineno;
    node->data.array_index.name  = strdup(name);
    node->data.array_index.index = index;
    return node;
}

/* Create a struct type definition node  struct Name { ...fields... } */
ASTNode* createStructDef(char* name, ASTNode* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                  = NODE_STRUCT_DEF;
    node->lineno                = yylineno;
    node->data.struct_def.name   = strdup(name);
    node->data.struct_def.fields = fields;
    return node;
}

/* Create a struct field-access node  base is field   (e.g. p is health) */
ASTNode* createStructAccess(ASTNode* base, char* field) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type                     = NODE_STRUCT_ACCESS;
    node->lineno                   = yylineno;
    node->data.struct_access.base  = base;
    node->data.struct_access.field = strdup(field);
    return node;
}

/* ─────────────────────────────────────────────────────────────────────────
 * printAST  — pretty-print the entire tree (for debugging)
 * ───────────────────────────────────────────────────────────────────────── */

/* Print 'level' levels of indentation */
static void indent(int level) {
    for (int i = 0; i < level; i++) printf("  ");
}

void printAST(ASTNode* node, int level) {
    if (!node) return;

    switch (node->type) {

        /* ── Expressions ── */
        case NODE_NUM:
            indent(level);
            printf("NUM: %d\n", node->data.num);
            break;

        case NODE_FLOAT:
            indent(level);
            printf("FLOAT: %g\n", node->data.fval);
            break;

        case NODE_VAR:
            indent(level);
            printf("VAR: %s\n", node->data.name);
            break;

        case NODE_BINOP: {
            const char* opStr;
            switch (node->data.binop.op) {
                case 'l': opStr = "<=";      break;
                case 'g': opStr = ">=";      break;
                case 'e': opStr = "==";      break;
                case 'n': opStr = "!=";      break;
                case 'u': opStr = "unary-";  break;
                default: {
                    static char buf[2] = {0, 0};
                    buf[0] = node->data.binop.op;
                    opStr  = buf;
                }
            }
            indent(level);
            printf("BINOP: %s\n", opStr);
            printAST(node->data.binop.left, level + 1);
            if (node->data.binop.right)
                printAST(node->data.binop.right, level + 1);
            break;
        }

        case NODE_DECL:
            indent(level);
            printf("DECL: %s %s\n", node->data.decl.varType, node->data.decl.name);
            break;

        case NODE_ASSIGN:
            indent(level);
            if (node->data.assign.arrayLHS) {
                printf("ASSIGN (array)\n");
                printAST(node->data.assign.arrayLHS, level + 1);
            } else if (node->data.assign.structLHS) {
                printf("ASSIGN (struct)\n");
                printAST(node->data.assign.structLHS, level + 1);
            } else {
                printf("ASSIGN: %s\n", node->data.assign.var);
            }
            printAST(node->data.assign.value, level + 1);
            break;

        case NODE_PRINT:
            indent(level);
            printf("PRINT\n");
            printAST(node->data.expr, level + 1);
            break;

        case NODE_ID_LIST:
            indent(level);
            printf("ID: %s\n", node->data.idlist.name);
            if (node->data.idlist.next)
                printAST(node->data.idlist.next, level);
            break;

        case NODE_FUNC_DEF:
            indent(level);
            printf("FUNC_DEF: %s\n", node->data.func_def.name);
            if (node->data.func_def.params)
                printAST(node->data.func_def.params, level + 1);
            if (node->data.func_def.body)
                printAST(node->data.func_def.body, level + 1);
            if (node->data.func_def.end_clause)
                printAST(node->data.func_def.end_clause, level + 1);
            break;

        case NODE_FUNC_CALL:
            indent(level);
            printf("CALL: %s\n", node->data.func_call.name);
            if (node->data.func_call.args)
                printAST(node->data.func_call.args, level + 1);
            break;

        case NODE_PARAM:
            indent(level);
            printf("PARAM: %s\n", node->data.param.name);
            break;

        case NODE_PARAM_LIST:
            printAST(node->data.param_list.param, level);
            printAST(node->data.param_list.next,  level);
            break;

        case NODE_ARG_LIST:
            printAST(node->data.arg_list.expr, level);
            printAST(node->data.arg_list.next, level);
            break;

        case NODE_STMT_LIST:
            printAST(node->data.stmtlist.stmt, level);
            if (node->data.stmtlist.next)
                printAST(node->data.stmtlist.next, level);
            break;

        case NODE_PROGRAM_START:
        case NODE_BLOCK:
            indent(level);
            printf("BLOCK\n");
            if (node->data.block.stmt_list)
                printAST(node->data.block.stmt_list, level + 2);
            break;

        case NODE_PROGRAM:
            indent(level);
            printf("PROGRAM\n");
            if (node->data.program.globals)
                printAST(node->data.program.globals, level + 2);
            if (node->data.program.funcs)
                printAST(node->data.program.funcs, level + 2);
            printAST(node->data.program.start, level + 2);
            break;

        case NODE_IF:
            indent(level);
            printf("IF\n");
            printAST(node->data.if_stmt.condition, level + 2);
            printAST(node->data.if_stmt.then_stmt, level + 2);
            if (node->data.if_stmt.else_stmt)
                printAST(node->data.if_stmt.else_stmt, level + 2);
            break;

        case NODE_WHILE:
            indent(level);
            printf("WHILE\n");
            printAST(node->data.while_stmt.condition, level + 2);
            printAST(node->data.while_stmt.body, level + 2);
            break;

        case NODE_FOR_WHILE:
            indent(level);
            printf("FOR_WHILE\n");
            indent(level + 1);
            printf("INIT:\n");
            printAST(node->data.for_while.init, level + 2);
            indent(level + 1);
            printf("CONDITION:\n");
            printAST(node->data.for_while.condition, level + 2);
            indent(level + 1);
            printf("UPDATE:\n");
            printAST(node->data.for_while.update, level + 2);
            indent(level + 1);
            printf("BODY:\n");
            printAST(node->data.for_while.body, level + 2);
            break;

        case NODE_ARRAY_DECL:
            indent(level);
            printf("ARRAY_DECL: %s[%d]\n",
                   node->data.array_decl.name, node->data.array_decl.size);
            break;

        case NODE_ARRAY_INDEX:
            indent(level);
            printf("ARRAY_INDEX: %s\n", node->data.array_index.name);
            printAST(node->data.array_index.index, level + 1);
            break;

        case NODE_STRUCT_DEF:
            indent(level);
            printf("STRUCT_DEF: %s\n", node->data.struct_def.name);
            printAST(node->data.struct_def.fields, level + 1);
            break;

        case NODE_STRUCT_ACCESS:
            indent(level);
            printf("STRUCT_ACCESS: .%s\n", node->data.struct_access.field);
            printAST(node->data.struct_access.base, level + 1);
            break;

        case NODE_END_CLAUSE:
            indent(level);
            printf("END_CLAUSE: %s\n",
                   node->data.name ? node->data.name : "null");
            break;

        default:
            indent(level);
            printf("(unknown node type %d)\n", node->type);
            break;
    }
}
