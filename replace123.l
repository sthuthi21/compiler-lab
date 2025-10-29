%{
	#include<stdio.h>
%}

%option noyywrap

%%
abc  {printf("123");}
.    {printf("%s" , yytext);}
\n   {printf("\nEnter string: ");}
%%

int main(){
	printf("Enter string: ");
	yylex();
	return 0;
}


