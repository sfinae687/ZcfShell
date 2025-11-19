%option prefix="shell_"
%option outfile="lex.shell.c"
%option noyywrap
%{
#include "shell.tab.h"   
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
%}
%x IN_STRING
WORD ([^ \n\t\v<>;|&]+)
%%

\" {BEGIN IN_STRING;}
<IN_STRING>[^"]+ {shell_lval.arg = strdup(yytext); return ARG;}
<IN_STRING>\" {BEGIN INITIAL;}

";" {return SEMICOLON;}
"\n" {return EOL;}
"<" {return RD_IN;}
">" {return RD_OUT;}
">>" {return RD_TR;}
"|" {return TPIPE;}
"&" {return AND_SYM;}

{WORD} {
    shell_lval.arg = strdup(yytext); return ARG;
}

<<EOF>> {exit(0);}

%%