%{
/* LEXICAL ANALYZER (SCANNER)
 * This is the first phase of compilation - breaking input into tokens
 * Flex generates a scanner from these rules that reads character by character
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

extern int displayTokens;

int yycolumn = 1;

#define YY_USER_ACTION \
    yycolumn += yyleng;
%}

%option nounput
%option noinput
%option yylineno

%x COMMENT

%%

"//".*          {
    if (displayTokens) printf("  (ignoring single-line comment)\n");
}

"/*"            {
    if (displayTokens) printf("  (start multi-line comment)\n");
    BEGIN(COMMENT);
}

<COMMENT>"*/"   {
    if (displayTokens) printf("  (end multi-line comment)\n");
    BEGIN(INITIAL);
}

<COMMENT>\n     { }

<COMMENT>.      { }

"int"           {
    if (displayTokens) printf("  TOKEN: INT keyword\n");
    return INT;
}

"float"         {
    if (displayTokens) printf("  TOKEN: FLOAT keyword\n");
    return FLOAT;
}

"print"         {
    if (displayTokens) printf("  TOKEN: PRINT keyword\n");
    return PRINT;
}

"func"          {
    if (displayTokens) printf("  TOKEN: FUNC keyword\n");
    return FUNC;
}

"Program_Start" {
    if (displayTokens) printf("  TOKEN: PROGRAM_START keyword\n");
    return PROGRAM_START;
}

"end"           {
    if (displayTokens) printf("  TOKEN: END keyword\n");
    return END;
}

"null"          {
    if (displayTokens) printf("  TOKEN: NULLTOK keyword\n");
    return NULLTOK;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    if (displayTokens) printf("  TOKEN: ID '%s'\n", yytext);
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+\.[0-9]+  {
    if (displayTokens) printf("  TOKEN: FNUM %s\n", yytext);
    yylval.fnum = atof(yytext);
    return FNUM;
}

[0-9]+          {
    if (displayTokens) printf("  TOKEN: NUM %s\n", yytext);
    yylval.num = atoi(yytext);
    return NUM;
}

"+"             { if (displayTokens) printf("  TOKEN: '+'\n");  return '+'; }
"-"             { if (displayTokens) printf("  TOKEN: '-'\n");  return '-'; }
"*"             { if (displayTokens) printf("  TOKEN: '*'\n");  return '*'; }
"/"             { if (displayTokens) printf("  TOKEN: '/'\n");  return '/'; }
"<"             { if (displayTokens) printf("  TOKEN: '<'\n");  return '<'; }
">"             { if (displayTokens) printf("  TOKEN: '>'\n");  return '>'; }
"="             { if (displayTokens) printf("  TOKEN: '='\n");  return '='; }
";"             { if (displayTokens) printf("  TOKEN: ';'\n");  return ';'; }
"("             { if (displayTokens) printf("  TOKEN: '('\n");  return '('; }
")"             { if (displayTokens) printf("  TOKEN: ')'\n");  return ')'; }
","             { if (displayTokens) printf("  TOKEN: ','\n");  return ','; }
"["             { if (displayTokens) printf("  TOKEN: '['\n");  return '['; }
"]"             { if (displayTokens) printf("  TOKEN: ']'\n");  return ']'; }

[ \t\r]         { }
\n              { yycolumn = 1; }

.               {
    fprintf(stderr, "\n❌ Lexical Error at line %d, column %d:\n", yylineno, yycolumn - 1);
    fprintf(stderr, "   Unknown character: '%c' (ASCII %d)\n", *yytext, *yytext);
    fprintf(stderr, "   💡 Suggestion: Remove this character or check for typos\n\n");
}

<<EOF>>         {
    if (YY_START == COMMENT) {
        fprintf(stderr, "\n❌ Lexical Error at line %d, column %d:\n", yylineno, yycolumn);
        fprintf(stderr, "   Unterminated multi-line comment\n");
        fprintf(stderr, "   💡 Suggestion: Add '*/' to close the comment\n\n");
        return 0;
    }
    yyterminate();
}

%%

int yywrap() {
    return 1;
}
