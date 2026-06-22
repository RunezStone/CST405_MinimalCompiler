%{
/* ============================================================================
 * OOMini  —  Lexical Analyzer (flex)
 * Phase 1: turns source characters into a token stream for the parser.
 * ==========================================================================*/
#include "ast.h"
#include "parser.tab.h"
#include <string.h>

int displayTokens = 0;   /* set by main.c via -tokens */
%}

%option noyywrap
%option yylineno

DIGIT   [0-9]
ALPHA   [a-zA-Z_]
ALNUM   [a-zA-Z_0-9]

%%

[ \t\r]+            { /* skip whitespace */ }
\n                  { /* yylineno auto-increments */ }
"//"[^\n]*          { /* line comment */ }

"class"             { if (displayTokens) printf("TOKEN class\n");    return CLASS; }
"extends"           { if (displayTokens) printf("TOKEN extends\n");  return EXTENDS; }
"func"              { if (displayTokens) printf("TOKEN func\n");     return FUNC; }
"new"               { if (displayTokens) printf("TOKEN new\n");      return NEW; }
"self"              { if (displayTokens) printf("TOKEN self\n");     return SELF; }
"return"            { if (displayTokens) printf("TOKEN return\n");   return RETURN; }
"if"                { if (displayTokens) printf("TOKEN if\n");       return IF; }
"else"              { if (displayTokens) printf("TOKEN else\n");     return ELSE; }
"while"             { if (displayTokens) printf("TOKEN while\n");    return WHILE; }
"print"             { if (displayTokens) printf("TOKEN print\n");    return PRINT; }
"int"               { if (displayTokens) printf("TOKEN int\n");      return INT; }
"void"              { if (displayTokens) printf("TOKEN void\n");     return VOID; }

"<="                { yylval.op = 'l'; return RELOP; }
">="                { yylval.op = 'g'; return RELOP; }
"=="                { yylval.op = 'e'; return RELOP; }
"!="                { yylval.op = 'n'; return RELOP; }
"<"                 { yylval.op = '<'; return RELOP; }
">"                 { yylval.op = '>'; return RELOP; }

"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return STAR; }
"/"                 { return SLASH; }
"="                 { return ASSIGN; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
";"                 { return SEMI; }
","                 { return COMMA; }
"."                 { return DOT; }

{DIGIT}+            { yylval.ival = atoi(yytext);
                      if (displayTokens) printf("TOKEN NUM %d\n", yylval.ival);
                      return NUM; }

{ALPHA}{ALNUM}*     { yylval.str = strdup(yytext);
                      if (displayTokens) printf("TOKEN ID %s\n", yylval.str);
                      return ID; }

.                   { fprintf(stderr, "Lexical error line %d: unexpected '%s'\n",
                              yylineno, yytext); }

%%
