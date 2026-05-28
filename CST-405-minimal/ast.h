#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * The AST is an intermediate representation of the program structure.
 * It represents the hierarchical syntax of the source code.
 * Each node represents one construct in the language.
 *
 * Language structure:
 *   1. Global int declarations        int x; int y;
 *   2. func definitions               func add(int a, int b) ... end result;
 *   3. Program_Start() entry block    Program_Start() ... end null;
 */

/* ─────────────────────────────────────────────────────────────────────────
 * NODE TYPES
 * ───────────────────────────────────────────────────────────────────────── */
typedef enum {
    /* ── Expressions ── */
    NODE_NUM,           /* Numeric literal             e.g. 42          */
    NODE_VAR,           /* Variable reference          e.g. x           */
    NODE_BINOP,         /* Binary operation            e.g. x + y       */

    /* ── Statements ── */
    NODE_DECL,          /* Scalar variable declaration e.g. int x;      */
    NODE_ASSIGN,        /* Assignment                  e.g. x = 10;     */
    NODE_PRINT,         /* Print statement             e.g. print(x);   */
    NODE_STMT_LIST,     /* Linked list of statements                     */

    /* ── Multi-declaration helper (parser-internal, expanded before
     *    semantic analysis; not seen by later phases) ── */
    NODE_ID_LIST,       /* Comma-separated id list     e.g. x, y, z     */

    /* ── Functions ── */
    NODE_FUNC_DEF,      /* Function definition         func f(int a)... */
    NODE_FUNC_CALL,     /* Function call               f(x, y)          */
    NODE_PARAM,         /* Single scalar parameter     int a            */
    NODE_PARAM_LIST,    /* Linked list of parameters                     */
    NODE_ARG_LIST,      /* Linked list of call args                      */
    NODE_END_CLAUSE,    /* end null; or end x;                           */
    NODE_PROGRAM_START, /* Program_Start() block (entry point)          */
    NODE_PROGRAM,       /* Root node: globals + funcs + Program_Start   */

    /* ── Control flow ── */
    NODE_IF,            /* if / if-else statement                        */
    NODE_WHILE,         /* while loop                                    */
    NODE_BLOCK,         /* Braced block { ... }                          */

    /* ── Arrays ── */
    NODE_ARRAY_DECL,    /* Array declaration           e.g. int arr[10] */
    NODE_ARRAY_INDEX    /* Array element access        e.g. arr[i]      */
} NodeType;


/* ─────────────────────────────────────────────────────────────────────────
 * AST NODE STRUCTURE
 * ───────────────────────────────────────────────────────────────────────── */
typedef struct ASTNode {
    NodeType type;   /* What kind of node this is    */
    int      lineno; /* Source line (for error msgs) */

    union {

        /* NODE_NUM ─ integer literal value */
        int num;

        /* NODE_VAR, NODE_END_CLAUSE ─ variable name or return var
         * NODE_END_CLAUSE: name == NULL means "end null;" (void)
         *                  name != NULL means "end x;"   (return x)   */
        char* name;

        /* NODE_DECL ─ scalar variable declaration */
        struct {
            char* name;     /* Variable name            */
            char* varType;  /* Type string (e.g. "int") */
        } decl;

        /* NODE_BINOP ─ binary (and unary-minus) operation */
        struct {
            char             op;     /* '+' '-' '*' '/' '<' '>' 'l'(<=)
                                        'g'(>=) 'e'(==) 'n'(!=) 'u'(unary-) */
            struct ASTNode*  left;
            struct ASTNode*  right;  /* NULL for unary minus */
        } binop;

        /* NODE_ASSIGN ─ assignment statement
         *   Scalar:  var != NULL, arrayLHS == NULL
         *   Array:   var == NULL, arrayLHS points to NODE_ARRAY_INDEX  */
        struct {
            char*           var;       /* Target variable name (scalar) */
            struct ASTNode* value;     /* RHS expression                */
            struct ASTNode* arrayLHS;  /* LHS index node (array assign) */
        } assign;

        /* NODE_PRINT ─ single expression to print */
        struct ASTNode* expr;

        /* NODE_STMT_LIST ─ singly-linked list of statements */
        struct {
            struct ASTNode* stmt;   /* Current statement */
            struct ASTNode* next;   /* Next in list      */
        } stmtlist;

        /* NODE_ID_LIST ─ comma-separated identifier list used only
         * during parsing of multi-declarations (int x, y, z;).
         * createMultiDecl() expands this into individual NODE_DECLs. */
        struct {
            char*           name;   /* This identifier          */
            struct ASTNode* next;   /* Next identifier in list  */
        } idlist;

        /* NODE_FUNC_DEF ─ function definition
         *   "func name(params) <body> end returnVar;"
         *   "func name(params) <body> end null;"
         *
         *   end_clause is a NODE_END_CLAUSE node:
         *     end_clause->data.name == NULL  → void ("end null;")
         *     end_clause->data.name != NULL  → named var ("end result;") */
        struct {
            char*           name;        /* Function name                 */
            struct ASTNode* params;      /* NODE_PARAM / NODE_PARAM_LIST  */
            struct ASTNode* body;        /* NODE_STMT_LIST of body        */
            struct ASTNode* end_clause;  /* NODE_END_CLAUSE               */
        } func_def;

        /* NODE_FUNC_CALL ─ function invocation */
        struct {
            char*           name;  /* Callee name                        */
            struct ASTNode* args;  /* NODE_ARG_LIST / single expr / NULL */
        } func_call;

        /* NODE_PARAM ─ single scalar parameter "int name" */
        struct {
            char* name;
        } param;

        /* NODE_PARAM_LIST ─ linked list of parameters */
        struct {
            struct ASTNode* param;  /* One NODE_PARAM or NODE_ARRAY_DECL */
            struct ASTNode* next;   /* Rest of the list                  */
        } param_list;

        /* NODE_ARG_LIST ─ linked list of call arguments */
        struct {
            struct ASTNode* expr;  /* One argument expression */
            struct ASTNode* next;  /* Rest of the list        */
        } arg_list;

        /* NODE_PROGRAM_START ─ the Program_Start() entry block.
         * NODE_BLOCK         ─ reuses the same layout.                 */
        struct {
            struct ASTNode* stmt_list;  /* Body statements              */
            struct ASTNode* end_clause; /* NODE_END_CLAUSE (always null) */
        } block;

        /* NODE_PROGRAM ─ root of the entire program tree */
        struct {
            struct ASTNode* globals;  /* Global declarations (may be NULL) */
            struct ASTNode* funcs;    /* Function definitions (may be NULL) */
            struct ASTNode* start;    /* Program_Start() block             */
        } program;

        /* NODE_IF ─ conditional statement */
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_stmt;
            struct ASTNode* else_stmt;  /* NULL if no else branch */
        } if_stmt;

        /* NODE_WHILE ─ while loop */
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;

        /* NODE_ARRAY_DECL ─ array declaration or array parameter
         *   isParam == 0 → declaration  e.g. int arr[10];
         *   isParam == 1 → parameter    e.g. int arr[]     (size == 0) */
        struct {
            char* name;
            int   size;     /* Element count; 0 for parameters */
            int   isParam;  /* 1 if function parameter         */
        } array_decl;

        /* NODE_ARRAY_INDEX ─ array element access  e.g. arr[i] */
        struct {
            char*           name;   /* Array name          */
            struct ASTNode* index;  /* Index expression    */
        } array_index;

    } data;

} ASTNode;


/* ─────────────────────────────────────────────────────────────────────────
 * CONSTRUCTOR FUNCTIONS  (called by the parser)
 * ───────────────────────────────────────────────────────────────────────── */

/* Expressions */
ASTNode* createNum(int value);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);

/* Statements */
ASTNode* createDecl(char* type, char* name);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);

/* Multi-declaration helpers */
ASTNode* createIdList(char* name);
ASTNode* appendIdList(ASTNode* list, char* name);
ASTNode* createMultiDecl(ASTNode* id_list);

/* Functions */
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body,
                         ASTNode* end_clause);
ASTNode* createFuncCall(char* name, ASTNode* args);
ASTNode* createParam(char* name);
ASTNode* createParamList(ASTNode* param, ASTNode* next);
ASTNode* appendParamList(ASTNode* list, ASTNode* param);
ASTNode* createArgList(ASTNode* expr);
ASTNode* appendArgList(ASTNode* list, ASTNode* expr);
ASTNode* createEndClause(char* returnVar);
ASTNode* createProgramStart(ASTNode* body, ASTNode* end_clause);
ASTNode* createProgram(ASTNode* globals, ASTNode* funcs, ASTNode* start);

/* Control flow */
ASTNode* createIf(ASTNode* condition, ASTNode* then_stmt,
                   ASTNode* else_stmt);
ASTNode* createWhile(ASTNode* condition, ASTNode* body);
ASTNode* createBlock(ASTNode* stmt_list);

/* Arrays */
ASTNode* createArrayDecl(char* name, int size);
ASTNode* createArrayParam(char* name);
ASTNode* createArrayIndex(char* name, ASTNode* index);

/* Debug / display */
void printAST(ASTNode* node, int level);

#endif /* AST_H */