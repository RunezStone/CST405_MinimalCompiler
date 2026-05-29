%{
/* SYNTAX ANALYZER (PARSER)
 * This is the second phase of compilation - checking grammar rules
 * Bison generates a parser that builds an Abstract Syntax Tree (AST)
 * The parser uses tokens from the scanner to verify syntax is correct
 *
 * LANGUAGE STRUCTURE:
 *   1. Global variable declarations  (int x; int y;)
 *   2. Function declarations         (func add(int a, int b) ... end result;)
 *   3. Program_Start block           (Program_Start() ... end null;)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* External declarations for lexer interface */
extern int yylex();      /* Get next token from scanner */
extern int yyparse();    /* Parse the entire input */
extern FILE* yyin;       /* Input file handle */
extern int yylineno;     /* Current line number from scanner */
extern char* yytext;     /* Current token text from scanner */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */
%}

/* SEMANTIC VALUES UNION
 * Defines possible types for tokens and grammar symbols
 */
%union {
    int num;                /* For integer literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
}

/* TOKEN DECLARATIONS */
%token <num> NUM            /* Number literal: carries integer value */
%token <str> ID             /* Identifier: carries string name */
%token INT PRINT            /* Original keywords */
%token FUNC PROGRAM_START   /* Function keywords */
%token END NULLTOK          /* End-clause keywords */

/* NON-TERMINAL TYPES */
%type <node> program
%type <node> global_list
%type <node> func_decl_list func_decl
%type <node> param_list param_item
%type <node> end_clause
%type <node> program_start
%type <node> stmt_list stmt
%type <node> decl assign print_stmt
%type <node> id_list
%type <node> expr
%type <node> func_call arg_list

/* OPERATOR PRECEDENCE */
%left '+'

%%

/* ================================================================
 * TOP-LEVEL PROGRAM STRUCTURE
 * globals → functions → Program_Start
 * ================================================================ */

program:
    global_list func_decl_list program_start {
        /* Full program: globals, functions, then entry point */
        root = createProgram($1, $2, $3);
    }
    | global_list program_start {
        /* No functions — just globals then Program_Start */
        root = createProgram($1, NULL, $2);
    }
    ;

/* ================================================================
 * GLOBAL VARIABLE DECLARATIONS
 * Zero or more "int x;" statements at the top of the file
 * ================================================================ */

global_list:
    /* empty */ {
        $$ = NULL;
    }
    | global_list decl {
        $$ = createStmtList($1, $2);
    }
    ;

/* ================================================================
 * FUNCTION DECLARATIONS
 * One or more func blocks before Program_Start
 * ================================================================ */

func_decl_list:
    func_decl {
        /* Base case: single function */
        $$ = $1;
    }
    | func_decl_list func_decl {
        /* Multiple functions: build a list */
        $$ = createStmtList($1, $2);
    }
    ;

/* SINGLE FUNCTION:
 *   func add(int a, int b)
 *       int result;
 *       result = a + b;
 *   end result;
 */
func_decl:
    FUNC ID '(' param_list ')' stmt_list end_clause {
        /* Function with parameters */
        $$ = createFuncDecl($2, $4, $6, $7);
        free($2);
    }
    | FUNC ID '(' ')' stmt_list end_clause {
        /* Function with no parameters */
        $$ = createFuncDecl($2, NULL, $5, $6);
        free($2);
    }
    | FUNC ID '(' param_list ')' end_clause {
        /* Function with params but empty body */
        $$ = createFuncDecl($2, $4, NULL, $6);
        free($2);
    }
    | FUNC ID '(' ')' end_clause {
        /* Function with no params and empty body */
        $$ = createFuncDecl($2, NULL, NULL, $5);
        free($2);
    }
    | FUNC error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed function declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'func name(int a, int b) ... end null;'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * PARAMETER LIST
 * "int a" or "int a, int b, int c"
 * ================================================================ */

param_list:
    param_item {
        /* Single parameter — wrap in NODE_PARAM_LIST so appendParamList
         * always receives a list head, never a raw NODE_PARAM */
        $$ = createParamList($1, NULL);
    }
    | param_list ',' param_item {
        /* Multiple parameters */
        $$ = appendParamList($1, $3);
    }
    | param_list ',' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'int <name>' after comma in parameter list\n");
        fprintf(stderr, "   💡 Suggestion: Each parameter must have a type, e.g. 'int x'\n\n");
        $$ = $1;
        yyerrok;
    }
    ;

/* SINGLE PARAMETER — "int x" */
param_item:
    INT ID {
        $$ = createParam($2);
        free($2);
    }
    | error ID {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing type in parameter declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'int %s' instead of just '%s'\n\n", $2, $2);
        $$ = createParam($2);
        free($2);
        yyerrok;
    }
    ;

/* ================================================================
 * END CLAUSE
 * "end null;" = void return
 * "end x;"    = return the value of variable x
 * ================================================================ */

end_clause:
    END NULLTOK ';' {
        /* Void return — function returns nothing */
        $$ = createEndClause(NULL);
    }
    | END ID ';' {
        /* Return a variable's value */
        $$ = createEndClause($2);
        free($2);
    }
    | END NULLTOK error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after 'end null'\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;'\n\n");
        $$ = createEndClause(NULL);
        yyerrok;
    }
    | END ID error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end %s;'\n\n", $2);
        $$ = createEndClause($2);
        free($2);
        yyerrok;
    }
    | END error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;' or 'end <variable>;'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * PROGRAM_START BLOCK
 * The entry point — must be last, always ends with "end null;"
 *
 *   Program_Start()
 *       statement1;
 *       statement2;
 *   end null;
 * ================================================================ */

program_start:
    PROGRAM_START '(' ')' stmt_list end_clause {
        /* Standard form with parentheses and statements */
        $$ = createProgramStart($4, $5);
    }
    | PROGRAM_START '(' ')' end_clause {
        /* Empty Program_Start body */
        $$ = createProgramStart(NULL, $4);
    }
    | PROGRAM_START error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed Program_Start block\n");
        fprintf(stderr, "   💡 Suggestion: Use 'Program_Start() ... end null;'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * STATEMENT LIST
 * One or more statements in sequence
 * ================================================================ */

stmt_list:
    stmt {
        /* Base case: single statement */
        $$ = $1;
    }
    | stmt_list stmt {
        /* Recursive case: list followed by another statement */
        $$ = createStmtList($1, $2);
    }
    ;

/* STATEMENT TYPES */
stmt:
    decl            /* Variable declaration:  int x;          */
    | assign        /* Assignment:            x = expr;        */
    | print_stmt    /* Print statement:       print(expr);     */
    ;

/* ================================================================
 * ID LIST
 * Comma-separated identifiers used in declarations
 * "x" or "x, y, z"
 * ================================================================ */

id_list:
    ID {
        /* Base case: single identifier */
        $$ = createIdList($1);
        free($1);
    }
    | id_list ',' ID {
        /* Recursive case: extend list */
        $$ = appendIdList($1, $3);
        free($3);
    }
    | id_list ',' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected identifier after comma in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add a variable name after ','\n\n");
        $$ = $1;
        yyerrok;
    }
    ;

/* ================================================================
 * DECLARATION
 * "int x;" or "int x, y, z;"
 * ================================================================ */

decl:
    INT id_list ';' {
        $$ = createMultiDecl($2);
    }
    | INT ID '[' NUM ']' ';' {         
        $$ = createArrayDecl($2, $4);
        free($2);
    }
    | INT id_list error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after variable declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the identifier list\n\n");
        $$ = NULL;
        yyerrok;
    }
    | INT error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected 'int <identifier>;' or 'int x, y, z;'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * ASSIGNMENT
 * "x = expr;"      — plain expression
 * "x = add(a, b);" — function call on the right-hand side
 * ================================================================ */

assign:
    ID '=' expr ';' {
        $$ = createAssign($1, $3);
        free($1);
    }
    | ID '=' func_call ';' {
        /* Function call as RHS: z = add(x, y); */
        $$ = createAssign($1, $3);
        free($1);
    }
    | ID '[' expr ']' '=' expr ';' {
    ASTNode* lhs = createArrayIndex($1, $3);
    ASTNode* node = createAssign(NULL, $6);
    node->data.assign.arrayLHS = lhs;
    $$ = node;
    free($1);
    }
    | ID '=' expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <expression>'\n\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    | ID '=' func_call error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after function call assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <func>(...)'\n\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    | ID '=' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment\n");
        fprintf(stderr, "   💡 Suggestion: Check the expression after '=' for '%s'\n\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    | ID error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement\n");
        fprintf(stderr, "   💡 Suggestion: Use '%s = <expression>;'\n\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * FUNCTION CALL
 * "add(x, y)" or "foo()"
 * Used as the RHS of an assignment: z = add(x, y);
 * ================================================================ */

func_call:
    ID '(' arg_list ')' {
        $$ = createFuncCall($1, $3);
        free($1);
    }
    | ID '(' ')' {
        /* No arguments */
        $$ = createFuncCall($1, NULL);
        free($1);
    }
    | ID '(' arg_list error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing ')' in function call\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' after the argument list\n\n");
        $$ = createFuncCall($1, $3);
        free($1);
        yyerrok;
    }
    | ID '(' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid argument in function call\n");
        fprintf(stderr, "   💡 Suggestion: Use 'funcName(x, y)' or 'funcName()'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ================================================================
 * ARGUMENT LIST
 * Expressions passed to a function call
 * "x" or "x, y, z" or "1 + 2, x"
 * ================================================================ */

arg_list:
    expr {
        /* Single argument */
        $$ = createArgList($1);
    }
    | arg_list ',' expr {
        /* Multiple arguments */
        $$ = appendArgList($1, $3);
    }
    | arg_list ',' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected expression after comma in argument list\n");
        fprintf(stderr, "   💡 Suggestion: Provide a value or variable after ','\n\n");
        $$ = $1;
        yyerrok;
    }
    ;

/* ================================================================
 * EXPRESSIONS
 * Builds expression trees for arithmetic and variables
 * ================================================================ */

expr:
    NUM {
        /* Integer literal */
        $$ = createNum($1);
    }
    | ID {
        /* Variable reference */
        $$ = createVar($1);
        free($1);
    }
    | expr '+' expr {
        /* Binary addition — left-associative via %left above */
        $$ = createBinOp('+', $1, $3);
    }
    | '(' expr ')' {
        /* Parenthesized expression */
        $$ = $2;
    }
    | ID '[' expr ']' {   
        $$ = createArrayIndex($1, $3);
        free($1); 
    }
    ;

/* ================================================================
 * PRINT STATEMENT
 * "print(expr);"
 * ================================================================ */

print_stmt:
    PRINT '(' expr ')' ';' {
        $$ = createPrint($3);
    }
    | PRINT '(' expr ')' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after 'print(<expression>)'\n\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT '(' expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' before semicolon\n\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT '(' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

%%

/* ERROR HANDLING - Called by Bison when a syntax error is detected */
void yyerror(const char* s) {
    fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
    fprintf(stderr, "   %s", s);

    if (yytext && yytext[0] != '\0') {
        fprintf(stderr, " (near token: '%s')\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "   💡 Common fixes:\n");
    fprintf(stderr, "      • Check for missing semicolons\n");
    fprintf(stderr, "      • Verify parentheses and brackets are balanced\n");
    fprintf(stderr, "      • Ensure variables are declared before use\n");
    fprintf(stderr, "      • Check for typos in keywords (int, print, func, end, null)\n");
    fprintf(stderr, "      • Global declarations must come before func declarations\n");
    fprintf(stderr, "      • Program_Start() must be last\n\n");
}
