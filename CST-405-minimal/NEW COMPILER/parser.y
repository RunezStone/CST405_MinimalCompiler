%{
/* ============================================================================
 * OOMini  —  Syntax Analyzer (Bison)
 * Phase 2: checks grammar and builds the AST.
 *
 * Program grammar (high level):
 *     program       ::= { class_def | func_def }
 *     class_def     ::= 'class' ID ['extends' ID] '{' member* '}'
 *     member        ::= field_def | method_def
 *     field_def     ::= type ID ';'
 *     method_def    ::= 'func' ret_type ID '(' params? ')' block
 *     func_def      ::= 'func' ret_type ID '(' params? ')' block
 *     entry point   ::= 'func' 'void' 'main' '(' ')' block
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern int yylineno;
extern char* yytext;
void yyerror(const char* s);

ASTNode* astRoot = NULL;   /* parser writes the finished program tree here */
int syntaxErrors = 0;
%}

%union {
    int             ival;
    char            op;
    char*           str;
    struct ASTNode* node;
}

%token <ival> NUM
%token <op>   RELOP
%token <str>  ID
%token CLASS EXTENDS FUNC NEW SELF RETURN IF ELSE WHILE PRINT INT VOID
%token PLUS MINUS STAR SLASH ASSIGN
%token LPAREN RPAREN LBRACE RBRACE SEMI COMMA DOT

%type <node> program item_list item class_def func_def method_def field_def
%type <node> member_list member params_opt param_list param
%type <node> block stmt_list_opt stmt_list stmt
%type <node> expr postfix primary args_opt arg_list
%type <str>  type ret_type ext_opt

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left RELOP
%left PLUS MINUS
%left STAR SLASH
%right UMINUS

%%

program
    : item_list                 { astRoot = $1; }
    ;

item_list
    : /* empty */               { $$ = NULL; }
    | item_list item            { $$ = listAppend($1, $2); }
    ;

item
    : class_def                 { $$ = $1; }
    | func_def                  { $$ = $1; }
    ;

/* ---------------------------------------------------------------- classes */
class_def
    : CLASS ID ext_opt LBRACE member_list RBRACE
        { $$ = newClassDef($2, $3, $5); }
    ;

ext_opt
    : /* empty */               { $$ = NULL; }
    | EXTENDS ID                { $$ = $2; }
    ;

member_list
    : /* empty */               { $$ = NULL; }
    | member_list member        { $$ = listAppend($1, $2); }
    ;

member
    : field_def                 { $$ = $1; }
    | method_def                { $$ = $1; }
    ;

field_def
    : type ID SEMI              { $$ = newFieldDef($1, $2); }
    ;

method_def
    : FUNC ret_type ID LPAREN params_opt RPAREN block
        { $$ = newMethodDef($2, $3, $5, $7); }
    ;

/* -------------------------------------------------------------- functions */
func_def
    : FUNC ret_type ID LPAREN params_opt RPAREN block
        { $$ = newFuncDef($2, $3, $5, $7); }
    ;

type
    : INT                       { $$ = strdup("int"); }
    | ID                        { $$ = $1; }
    ;

ret_type
    : INT                       { $$ = strdup("int"); }
    | VOID                      { $$ = strdup("void"); }
    | ID                        { $$ = $1; }
    ;

params_opt
    : /* empty */               { $$ = NULL; }
    | param_list                { $$ = $1; }
    ;

param_list
    : param                     { $$ = $1; }
    | param_list COMMA param    { $$ = listAppend($1, $3); }
    ;

param
    : type ID                   { $$ = newParam($1, $2); }
    ;

/* --------------------------------------------------------------- blocks */
block
    : LBRACE stmt_list_opt RBRACE   { $$ = $2; }
    ;

stmt_list_opt
    : /* empty */               { $$ = NULL; }
    | stmt_list                 { $$ = $1; }
    ;

stmt_list
    : stmt                      { $$ = $1; }
    | stmt_list stmt            { $$ = listAppend($1, $2); }
    ;

/* --------------------------------------------------------------- statements */
stmt
    : INT ID SEMI               { $$ = newDecl(strdup("int"), $2); }
    | ID ID SEMI                { $$ = newDecl($1, $2); }      /* object decl */
    | expr ASSIGN expr SEMI
        {
            if ($1->type == NODE_VAR)
                $$ = newAssignVar($1->name, $3);
            else if ($1->type == NODE_FIELD_ACCESS)
                $$ = newAssignField($1, $3);
            else { yyerror("invalid assignment target"); $$ = newExprStmt($1); }
        }
    | expr SEMI                 { $$ = newExprStmt($1); }
    | PRINT LPAREN expr RPAREN SEMI { $$ = newPrint($3); }
    | RETURN expr SEMI          { $$ = newReturn($2); }
    | RETURN SEMI               { $$ = newReturn(NULL); }
    | IF LPAREN expr RPAREN block %prec LOWER_THAN_ELSE
                                { $$ = newIf($3, $5, NULL); }
    | IF LPAREN expr RPAREN block ELSE block
                                { $$ = newIf($3, $5, $7); }
    | WHILE LPAREN expr RPAREN block { $$ = newWhile($3, $5); }
    ;

/* --------------------------------------------------------------- expressions */
expr
    : expr PLUS expr            { $$ = newBinOp('+', $1, $3); }
    | expr MINUS expr           { $$ = newBinOp('-', $1, $3); }
    | expr STAR expr            { $$ = newBinOp('*', $1, $3); }
    | expr SLASH expr           { $$ = newBinOp('/', $1, $3); }
    | expr RELOP expr           { $$ = newBinOp($2, $1, $3); }
    | MINUS expr %prec UMINUS   { $$ = newBinOp('-', newNum(0), $2); }
    | postfix                   { $$ = $1; }
    ;

postfix
    : primary                                   { $$ = $1; }
    | postfix DOT ID                            { $$ = newFieldAccess($1, $3); }
    | postfix DOT ID LPAREN args_opt RPAREN     { $$ = newMethodCall($1, $3, $5); }
    ;

primary
    : NUM                           { $$ = newNum($1); }
    | ID                            { $$ = newVar($1); }
    | SELF                          { $$ = newSelf(); }
    | ID LPAREN args_opt RPAREN     { $$ = newFuncCall($1, $3); }
    | NEW ID LPAREN args_opt RPAREN { $$ = newNewObj($2, $4); }
    | LPAREN expr RPAREN            { $$ = $2; }
    ;

args_opt
    : /* empty */               { $$ = NULL; }
    | arg_list                  { $$ = $1; }
    ;

arg_list
    : expr                      { $$ = $1; }
    | arg_list COMMA expr       { $$ = listAppend($1, $3); }
    ;

%%

void yyerror(const char* s) {
    syntaxErrors++;
    fprintf(stderr, "Syntax error (line %d): %s near '%s'\n",
            yylineno, s, yytext ? yytext : "?");
}
