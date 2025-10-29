%{
	#include "y.tab.h"
%}

%option noyywrap

%%
"for"   {return FOR;}
"("     {return OPEN;}
")"	{return CLOSE;}
"{"	{return LBRACE;}
"}"	{return RBRACE;}
";"	{return SEMI;}
"<="|">="|"=="|"<"|">"  {return RELOP;}
"++"|"--" {return INC;}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[0-9]+  {return NUM;}
"=" {return ASSIGN;}
"+"|"-"|"*"|"/" {return OP;}
[ \t\n]+   ; 
. {return INVALID;}
%%

