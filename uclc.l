%{
	#include<stdio.h>
%}

%option noyywrap

%%
[A-Z]  {printf("%c" , yytext[0] + 32);}
[a-z]  {printf("%s" , yytext);}
.      {printf("%s" , yytext);}
%%

int main(){
	printf("Enter string: ");
	yylex();
	return 0;
}
