%{
	#include<stdio.h>
	#include<stdlib.h>
	void yyerror(const char *s);
	int yylex();
%}

%token FOR OPEN CLOSE LBRACE RBRACE SEMI RELOP INC ID NUM ASSIGN OP INVALID

%%
S : FOR OPEN ASSIGNMENT SEMI CONDITION SEMI INCREMENT CLOSE BODY
	{printf("Valid for loop syntax\n");}
  ;

ASSIGNMENT : ID ASSIGN EXPR
	   ;

EXPR : ID ASSIGN EXPR
     | ID
     | NUM
     | ID OP NUM
     | ID OP ID
     | NUM OP ID
     ;
CONDITION : ID RELOP EXPR
	  ;

INCREMENT : ID INC
	  | INC ID
	  ;

BODY 	  : LBRACE STATEMENTS RBRACE
	  ;

STATEMENTS: STATEMENTS STMT
	  | STMT
	  ;
STMT	  : EXPR SEMI
	  | /*EMPTY*/
	  ;

%%

void yyerror(const char *s){
	printf("Invalid for loop syntax\n");
}

int main(){
	printf("Enter a for loop:\n");
	yyparse();
	return 0;
}
