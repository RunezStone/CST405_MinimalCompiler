/* SEMANTIC ANALYSIS
 * Performs semantic checks on the Abstract Syntax Tree AFTER parsing.
 *
 * Language rules enforced here:
 *   ✓ No duplicate variable declarations in the same scope
 *   ✓ No use of undeclared variables
 *   ✓ No duplicate function definitions
 *   ✓ Function calls reference defined functions
 *   ✓ Argument count matches parameter count
 *   ✓ "end <var>;" — the return variable must be declared in the function
 *   ✓ Array sizes must be positive
 *   ✓ No duplicate array declarations
 *
 * Architecture — two passes:
 *   Pass 1: Register all function signatures (enables forward calls)
 *   Pass 2: Check every function body and Program_Start body
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symtab.h"

#define MAX_FUNCTIONS   100
#define MAX_PARAMS       20
#define MAX_SCOPE_DEPTH  10
#define MAX_VARS        200

typedef struct {
    char* name;
    int   paramCount;
    char* params[MAX_PARAMS];
    int   paramIsArray[MAX_PARAMS];
    int   isDefined;
    int   isVoid;
    char* returnVar;
} FunctionSymbol;

typedef struct {
    char* names[MAX_VARS];
    int   count;
} Scope;

static SemanticInfo   semInfo;
static FunctionSymbol functions[MAX_FUNCTIONS];
static int            functionCount   = 0;
static Scope          scopes[MAX_SCOPE_DEPTH];
static int            scopeDepth      = 0;
static char*          currentFunction = NULL;
static int            inFunction      = 0;

/* ─────────────────────────────────────────────────────────────────────────
 * HELPER: get return variable name from end_clause node
 * ───────────────────────────────────────────────────────────────────────── */
static char* getReturnVar(ASTNode* funcDefNode) {
    if (!funcDefNode) return NULL;
    ASTNode* ec = funcDefNode->data.func_def.end_clause;
    if (!ec) return NULL;
    return ec->data.name;
}

/* ─────────────────────────────────────────────────────────────────────────
 * SCOPE MANAGEMENT
 * ───────────────────────────────────────────────────────────────────────── */
static void enterScope(void) {
    if (scopeDepth >= MAX_SCOPE_DEPTH) {
        fprintf(stderr, "SEMANTIC ERROR: Maximum scope depth exceeded\n");
        semInfo.errorCount++;
        return;
    }
    scopes[scopeDepth].count = 0;
    scopeDepth++;
}

static void exitScope(void) {
    if (scopeDepth <= 0) return;
    for (int i = 0; i < scopes[scopeDepth - 1].count; i++) {
        free(scopes[scopeDepth - 1].names[i]);
        scopes[scopeDepth - 1].names[i] = NULL;
    }
    scopeDepth--;
}

static void printSemanticScopes(void) {
    printf("\n┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ SEMANTIC SCOPE STACK (Depth: %d)\n", scopeDepth);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    if (scopeDepth == 0) {
        printf("│ (no active scopes)\n");
    } else {
        for (int d = 0; d < scopeDepth; d++) {
            if (d == 0)
                printf("│ Scope[0] GLOBAL (%d variable(s))\n", scopes[d].count);
            else if (inFunction && d == scopeDepth - 1)
                printf("│ Scope[%d] Function '%s' (%d variable(s))\n",
                       d, currentFunction ? currentFunction : "?", scopes[d].count);
            else
                printf("│ Scope[%d] LOCAL (%d variable(s))\n", d, scopes[d].count);

            if (scopes[d].count > 0) {
                printf("│   Variables: ");
                for (int i = 0; i < scopes[d].count; i++) {
                    printf("%s", scopes[d].names[i]);
                    if (i < scopes[d].count - 1) printf(", ");
                }
                printf("\n");
            } else {
                printf("│   (empty)\n");
            }
        }
    }
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
}

static int addVarToScope(char* name) {
    if (scopeDepth == 0) {
        fprintf(stderr, "SEMANTIC ERROR: No active scope\n");
        return -1;
    }
    Scope* cur = &scopes[scopeDepth - 1];
    for (int i = 0; i < cur->count; i++)
        if (strcmp(cur->names[i], name) == 0) return -1;
    if (cur->count >= MAX_VARS) {
        fprintf(stderr, "SEMANTIC ERROR: Too many variables in scope\n");
        return -1;
    }
    cur->names[cur->count++] = strdup(name);
    return 0;
}

static int isVarDeclaredInScope(char* name) {
    for (int d = scopeDepth - 1; d >= 0; d--)
        for (int i = 0; i < scopes[d].count; i++)
            if (strcmp(scopes[d].names[i], name) == 0) return 1;
    return 0;
}

/* ─────────────────────────────────────────────────────────────────────────
 * FUNCTION TABLE
 * ───────────────────────────────────────────────────────────────────────── */
static FunctionSymbol* findFunction(char* name) {
    for (int i = 0; i < functionCount; i++)
        if (strcmp(functions[i].name, name) == 0)
            return &functions[i];
    return NULL;
}

static int addFunction(char* name, int paramCount,
                       char** params, int* paramIsArray,
                       int isVoid, char* returnVar) {
    if (functionCount >= MAX_FUNCTIONS) {
        fprintf(stderr, "SEMANTIC ERROR: Too many functions defined\n");
        return -1;
    }
    if (findFunction(name)) {
        fprintf(stderr,
            "\n╔════════════════════════════════════════════════════════════╗\n"
            "║ SEMANTIC ERROR - Duplicate Function Definition             ║\n"
            "╚════════════════════════════════════════════════════════════╝\n"
            "  ❌ Function '%s' is defined more than once\n"
            "  💡 Remove or rename one of the definitions.\n\n", name);
        semInfo.errorCount++;
        return -1;
    }
    FunctionSymbol* fs = &functions[functionCount++];
    fs->name       = strdup(name);
    fs->paramCount = paramCount;
    fs->isDefined  = 1;
    fs->isVoid     = isVoid;
    fs->returnVar  = returnVar ? strdup(returnVar) : NULL;
    for (int i = 0; i < paramCount && i < MAX_PARAMS; i++) {
        fs->params[i]       = strdup(params[i]);
        fs->paramIsArray[i] = paramIsArray ? paramIsArray[i] : 0;
    }
    printf("  ✓ Function '%s' registered  (%d param(s), returns: %s)\n",
           name, paramCount, isVoid ? "null" : (returnVar ? returnVar : "?"));
    return 0;
}

/* ─────────────────────────────────────────────────────────────────────────
 * PARAMETER COLLECTION
 *
 * FIX: collectParams now handles both NODE_PARAM at the top level
 * (old single-param path) and NODE_PARAM_LIST chains (new path where
 * the parser always wraps the first param in createParamList).
 * Both paths recurse correctly so all params are counted.
 * ───────────────────────────────────────────────────────────────────────── */
static int collectParams(ASTNode* params, char** names, int* isArray) {
    if (!params) return 0;

    switch (params->type) {
        case NODE_PARAM:
            names[0]   = params->data.param.name;
            isArray[0] = 0;
            return 1;

        case NODE_ARRAY_DECL:
            names[0]   = params->data.array_decl.name;
            isArray[0] = 1;
            return 1;

        case NODE_PARAM_LIST: {
            int n = collectParams(params->data.param_list.param, names, isArray);
            n    += collectParams(params->data.param_list.next,
                                  names + n, isArray + n);
            return n;
        }
        default:
            return 0;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * ARGUMENT COUNTING
 *
 * FIX: countArgs now handles the case where args is a plain expression
 * node (not wrapped in NODE_ARG_LIST) as well as full ARG_LIST chains.
 * ───────────────────────────────────────────────────────────────────────── */
static int countArgs(ASTNode* args) {
    if (!args) return 0;
    if (args->type == NODE_ARG_LIST)
        return 1 + countArgs(args->data.arg_list.next);
    /* Single expression passed directly (not wrapped) */
    return 1;
}

/* ─────────────────────────────────────────────────────────────────────────
 * FORWARD DECLARATIONS
 * ───────────────────────────────────────────────────────────────────────── */
static void checkExpr(ASTNode* node);
static void checkStmt(ASTNode* node);
static void checkStmtList(ASTNode* node);

/* ─────────────────────────────────────────────────────────────────────────
 * EXPRESSION CHECKER
 * ───────────────────────────────────────────────────────────────────────── */
static void checkExpr(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_NUM:
            break;

        case NODE_VAR:
            if (!isVarDeclaredInScope(node->data.name)) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Undeclared Variable                       ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Variable '%s' is used before being declared\n"
                    "  💡 Add 'int %s;' before line %d\n\n",
                    node->lineno, node->data.name,
                    node->data.name, node->lineno);
                semInfo.errorCount++;
            }
            break;

        case NODE_BINOP:
            checkExpr(node->data.binop.left);
            if (node->data.binop.right)
                checkExpr(node->data.binop.right);
            break;

        case NODE_FUNC_CALL: {
            FunctionSymbol* fs = findFunction(node->data.func_call.name);
            if (!fs) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Undeclared Function                       ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Function '%s()' is called but was never defined\n"
                    "  💡 Define 'func %s(...) ... end null;' before Program_Start()\n\n",
                    node->lineno, node->data.func_call.name,
                    node->data.func_call.name);
                semInfo.errorCount++;
            } else {
                int argCount = countArgs(node->data.func_call.args);
                if (argCount != fs->paramCount) {
                    fprintf(stderr,
                        "\n╔════════════════════════════════════════════════════════════╗\n"
                        "║ SEMANTIC ERROR - Wrong Argument Count                      ║\n"
                        "╚════════════════════════════════════════════════════════════╝\n"
                        "  📍 Line %d\n"
                        "  ❌ '%s()' expects %d argument(s) but got %d\n"
                        "  💡 %s\n\n",
                        node->lineno, fs->name, fs->paramCount, argCount,
                        argCount < fs->paramCount
                            ? "Add the missing argument(s)"
                            : "Remove the extra argument(s)");
                    semInfo.errorCount++;
                } else {
                    printf("  ✓ Call to '%s()' — %d argument(s) OK\n",
                           fs->name, argCount);
                }
                /* Check each argument expression */
                ASTNode* arg = node->data.func_call.args;
                while (arg) {
                    if (arg->type == NODE_ARG_LIST) {
                        checkExpr(arg->data.arg_list.expr);
                        arg = arg->data.arg_list.next;
                    } else {
                        checkExpr(arg);
                        break;
                    }
                }
            }
            break;
        }

        case NODE_ARRAY_INDEX:
            if (!isVarDeclaredInScope(node->data.array_index.name)) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Undeclared Array                          ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Array '%s' is used before being declared\n"
                    "  💡 Add 'int %s[SIZE];' before this line\n\n",
                    node->lineno, node->data.array_index.name,
                    node->data.array_index.name);
                semInfo.errorCount++;
            }
            checkExpr(node->data.array_index.index);
            break;

        default:
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * STATEMENT CHECKER
 * ───────────────────────────────────────────────────────────────────────── */
static void checkStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_DECL:
            if (addVarToScope(node->data.decl.name) == -1) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Duplicate Variable Declaration            ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Variable '%s' is already declared in this scope\n"
                    "  💡 Remove the duplicate, or use a different name\n\n",
                    node->lineno, node->data.decl.name);
                semInfo.errorCount++;
            } else {
                printf("  ✓ Variable '%s' declared  (line %d)\n",
                       node->data.decl.name, node->lineno);
            }
            break;

        case NODE_ASSIGN:
            if (node->data.assign.arrayLHS) {
                checkExpr(node->data.assign.arrayLHS);
                printf("  ✓ Array-element assignment  (line %d)\n", node->lineno);
            } else {
                if (!isVarDeclaredInScope(node->data.assign.var)) {
                    fprintf(stderr,
                        "\n╔════════════════════════════════════════════════════════════╗\n"
                        "║ SEMANTIC ERROR - Assignment to Undeclared Variable         ║\n"
                        "╚════════════════════════════════════════════════════════════╝\n"
                        "  📍 Line %d\n"
                        "  ❌ Variable '%s' has not been declared\n"
                        "  💡 Add 'int %s;' before line %d\n\n",
                        node->lineno, node->data.assign.var,
                        node->data.assign.var, node->lineno);
                    semInfo.errorCount++;
                } else {
                    printf("  ✓ Assignment to '%s'  (line %d)\n",
                           node->data.assign.var, node->lineno);
                }
            }
            checkExpr(node->data.assign.value);
            break;

        case NODE_PRINT:
            checkExpr(node->data.expr);
            printf("  ✓ Print statement  (line %d)\n", node->lineno);
            break;

        case NODE_IF:
            printf("  ✓ Checking if statement  (line %d)\n", node->lineno);
            checkExpr(node->data.if_stmt.condition);
            checkStmt(node->data.if_stmt.then_stmt);
            if (node->data.if_stmt.else_stmt)
                checkStmt(node->data.if_stmt.else_stmt);
            break;

        case NODE_WHILE:
            printf("  ✓ Checking while loop  (line %d)\n", node->lineno);
            checkExpr(node->data.while_stmt.condition);
            checkStmt(node->data.while_stmt.body);
            break;

        case NODE_FOR_WHILE:
            printf("  ✓ Checking C-style while loop  (line %d)\n", node->lineno);
            checkStmt(node->data.for_while.init);
            checkExpr(node->data.for_while.condition);
            checkStmt(node->data.for_while.update);
            checkStmt(node->data.for_while.body);
            break;

        case NODE_BLOCK:
            enterScope();
            checkStmtList(node->data.block.stmt_list);
            exitScope();
            break;

        case NODE_FUNC_CALL:
            checkExpr(node);
            break;

        case NODE_STMT_LIST:
            checkStmtList(node);
            break;

        case NODE_ARRAY_DECL:
            if (node->data.array_decl.isParam) break;
            if (node->data.array_decl.size <= 0) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Invalid Array Size                        ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Array '%s' has size %d — must be a positive integer\n"
                    "  💡 Use: int %s[10];\n\n",
                    node->lineno, node->data.array_decl.name,
                    node->data.array_decl.size, node->data.array_decl.name);
                semInfo.errorCount++;
            } else if (addVarToScope(node->data.array_decl.name) == -1) {
                fprintf(stderr,
                    "\n╔════════════════════════════════════════════════════════════╗\n"
                    "║ SEMANTIC ERROR - Duplicate Array Declaration               ║\n"
                    "╚════════════════════════════════════════════════════════════╝\n"
                    "  📍 Line %d\n"
                    "  ❌ Array '%s' is already declared in this scope\n"
                    "  💡 Remove the duplicate, or use a different name\n\n",
                    node->lineno, node->data.array_decl.name);
                semInfo.errorCount++;
            } else {
                printf("  ✓ Array '%s[%d]' declared  (line %d)\n",
                       node->data.array_decl.name,
                       node->data.array_decl.size, node->lineno);
            }
            break;

        default:
            break;
    }
}

static void checkStmtList(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        checkStmt(node->data.stmtlist.stmt);
        checkStmtList(node->data.stmtlist.next);
    } else {
        checkStmt(node);
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * ADD PARAMETERS TO FUNCTION SCOPE
 *
 * FIX: NODE_PARAM_LIST now recurses on both .param and .next so every
 * parameter in a multi-param function is added to the scope.
 * Previously the break after NODE_PARAM prevented the list walk from
 * continuing — which meant only the first param was ever visible inside
 * the function body, causing false "undeclared variable" errors for b,
 * c, etc.
 * ───────────────────────────────────────────────────────────────────────── */
static void addParamsToScope(ASTNode* param) {
    if (!param) return;
    switch (param->type) {
        case NODE_PARAM:
            addVarToScope(param->data.param.name);
            printf("  ✓ Parameter '%s' added to function scope\n",
                   param->data.param.name);
            break;
        case NODE_ARRAY_DECL:
            if (param->data.array_decl.isParam) {
                addVarToScope(param->data.array_decl.name);
                printf("  ✓ Array parameter '%s[]' added to function scope\n",
                       param->data.array_decl.name);
            }
            break;
        case NODE_PARAM_LIST:
            /* Recurse on the head param, then continue down the chain */
            addParamsToScope(param->data.param_list.param);
            addParamsToScope(param->data.param_list.next);
            break;
        default:
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * CHECK A SINGLE FUNCTION DEFINITION  (Pass 2)
 * ───────────────────────────────────────────────────────────────────────── */
static void checkFuncDef(ASTNode* node) {
    if (!node || node->type != NODE_FUNC_DEF) return;

    currentFunction = node->data.func_def.name;
    inFunction      = 1;

    enterScope();
    printf("  Entered scope for function '%s'\n", currentFunction);
    printSemanticScopes();

    /* Add ALL parameters to the function scope before checking the body */
    if (node->data.func_def.params)
        addParamsToScope(node->data.func_def.params);

    printSemanticScopes();

    /* Check body */
    checkStmtList(node->data.func_def.body);

    /* Validate return variable */
    char* retVar = getReturnVar(node);
    if (retVar != NULL) {
        if (!isVarDeclaredInScope(retVar)) {
            fprintf(stderr,
                "\n╔════════════════════════════════════════════════════════════╗\n"
                "║ SEMANTIC ERROR - Unknown Return Variable                   ║\n"
                "╚════════════════════════════════════════════════════════════╝\n"
                "  📍 Function '%s'\n"
                "  ❌ 'end %s;' — '%s' is not declared in this function\n"
                "  💡 Declare 'int %s;' inside the function body,\n"
                "     or use 'end null;' for a void function.\n\n",
                node->data.func_def.name, retVar, retVar, retVar);
            semInfo.errorCount++;
        } else {
            printf("  ✓ Return variable '%s' declared in '%s'\n",
                   retVar, node->data.func_def.name);
        }
    }

    printf("  Exiting scope for function '%s'\n", currentFunction);
    exitScope();
    printSemanticScopes();

    inFunction      = 0;
    currentFunction = NULL;
}

/* ─────────────────────────────────────────────────────────────────────────
 * PASS 1 — REGISTER ALL FUNCTION SIGNATURES
 * ───────────────────────────────────────────────────────────────────────── */
static void registerFunctions(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_PROGRAM:
            registerFunctions(node->data.program.funcs);
            break;
        case NODE_STMT_LIST:
            registerFunctions(node->data.stmtlist.stmt);
            registerFunctions(node->data.stmtlist.next);
            break;
        case NODE_FUNC_DEF: {
            char* paramNames[MAX_PARAMS];
            int   paramIsArray[MAX_PARAMS];
            int   count  = collectParams(node->data.func_def.params,
                                          paramNames, paramIsArray);
            char* retVar = getReturnVar(node);
            int   isVoid = (retVar == NULL);
            addFunction(node->data.func_def.name, count,
                        paramNames, paramIsArray, isVoid, retVar);
            break;
        }
        default:
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * PASS 2 — CHECK BODIES, GLOBALS, Program_Start
 * ───────────────────────────────────────────────────────────────────────── */
static void checkAll(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_PROGRAM:
            checkAll(node->data.program.globals);
            checkAll(node->data.program.funcs);
            checkAll(node->data.program.start);
            break;
        case NODE_STMT_LIST:
            checkAll(node->data.stmtlist.stmt);
            checkAll(node->data.stmtlist.next);
            break;
        case NODE_FUNC_DEF:
            printf("─── Checking function: %s ───\n",
                   node->data.func_def.name);
            checkFuncDef(node);
            printf("\n");
            break;
        case NODE_DECL:
            if (addVarToScope(node->data.decl.name) == -1) {
                fprintf(stderr,
                    "  ❌ SEMANTIC ERROR: Global variable '%s' already declared\n",
                    node->data.decl.name);
                semInfo.errorCount++;
            } else {
                printf("  ✓ Global variable '%s' declared\n",
                       node->data.decl.name);
            }
            break;
        case NODE_ARRAY_DECL:
            if (node->data.array_decl.size <= 0) {
                fprintf(stderr,
                    "  ❌ SEMANTIC ERROR: Global array '%s' has invalid size %d\n",
                    node->data.array_decl.name, node->data.array_decl.size);
                semInfo.errorCount++;
            } else if (addVarToScope(node->data.array_decl.name) == -1) {
                fprintf(stderr,
                    "  ❌ SEMANTIC ERROR: Global array '%s' already declared\n",
                    node->data.array_decl.name);
                semInfo.errorCount++;
            } else {
                printf("  ✓ Global array '%s[%d]' declared\n",
                       node->data.array_decl.name,
                       node->data.array_decl.size);
            }
            break;
        case NODE_PROGRAM_START:
            printf("─── Checking Program_Start() ───\n");
            enterScope();
            printSemanticScopes();
            checkStmtList(node->data.block.stmt_list);
            exitScope();
            printSemanticScopes();
            printf("\n");
            break;
        default:
            checkStmt(node);
            break;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * PUBLIC API
 * ───────────────────────────────────────────────────────────────────────── */
void initSemantic(void) {
    semInfo.errorCount   = 0;
    semInfo.warningCount = 0;
    functionCount        = 0;
    scopeDepth           = 0;
    currentFunction      = NULL;
    inFunction           = 0;

    /* Register built-in print() */
    functions[functionCount].name       = strdup("print");
    functions[functionCount].paramCount = 1;
    functions[functionCount].isDefined  = 1;
    functions[functionCount].isVoid     = 1;
    functions[functionCount].returnVar  = NULL;
    functionCount++;

    printf("SEMANTIC ANALYZER: Initialized\n\n");
}

int performSemanticAnalysis(ASTNode* root) {
    if (!root) {
        fprintf(stderr, "SEMANTIC ERROR: No AST to analyze\n");
        return -1;
    }

    printf("Running semantic analysis...\n\n");

    enterScope();
    printf("Entered global scope\n");
    printSemanticScopes();

    printf("Pass 1: Registering function signatures\n");
    printf("───────────────────────────────────────\n");
    registerFunctions(root);
    printf("\n");

    printf("Pass 2: Checking declarations and function bodies\n");
    printf("──────────────────────────────────────────────────\n");
    checkAll(root);

    exitScope();
    return (semInfo.errorCount > 0) ? -1 : 0;
}

void printSemanticSummary(void) {
    printf("═══════════════════════════════════════════════\n");
    printf("  SEMANTIC ANALYSIS SUMMARY\n");
    printf("═══════════════════════════════════════════════\n");
    printf("  Functions defined : %d\n", functionCount);
    printf("  Errors found      : %d\n", semInfo.errorCount);
    printf("  Warnings found    : %d\n", semInfo.warningCount);
    printf("\n");
    if (semInfo.errorCount == 0)
        printf("  ✓ Semantic analysis PASSED — program is valid!\n");
    else
        printf("  ✗ Semantic analysis FAILED — fix errors above.\n");
    printf("═══════════════════════════════════════════════\n\n");
}