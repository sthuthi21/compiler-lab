%{
	#include<stdio.h>
%}

%option noyywrap

%%
[a-z]  {printf("%c" , yytext[0] - 32);}
[A-Z]  {printf("%s" , yytext);}
.      {printf("%s" , yytext);}
%%

int main(){
	printf("Enter string: ");
	yylex();
	return 0;
}
