#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50
#define MAX_PRO 10

char productions[MAX_PRO][MAX];
int numProd = 0;

char input[MAX];
char stack[MAX];
int ip = 0;
int sp = -1;

void push(char c){
	stack[++sp] = c;
	stack[sp+1] = '\0';
	
}
void pop(int n){
	sp -= n;
	if(sp<-1) sp = -1;
	stack[sp+1] = '\0';
}

int matchRhs(const char *rhs){
	int len = strlen(rhs);
	if((sp + 1) < len) return 0;
	for(int i=0;i<len;i++){
		if(stack[sp-len+1+i] != rhs[i])
			return 0;
	}
	return 1;
}

int reduce(){
	char action[50];
	for(int i=0;i<numProd;i++){
		char lhs = productions[i][0];
		char *rhs = productions[i]+2;
		
		if(matchRhs(rhs)){
			int len = strlen(rhs);
			pop(len);
			push(lhs);
			sprintf(action , "REDUCE: %c-->%s" , lhs , rhs);
			printf("%-25s %-25s %-25s\n", stack, input+ip, action);
			return 1;
		}
	}
	return 0;
}

int main(){
	printf("Enter number of productions:");
	scanf("%d" , &numProd);
	
	printf("Enter the productions:\n");
	for(int i=0;i<numProd;i++){
		scanf("%s" , productions[i]);
	}
	
	printf("Enter the input string:");
	scanf("%s" , input);
	
	printf("%-25s %-25s %-25s\n", "STACK" , "INPUT" , "ACTION");
	push('$');
	
	//shift
	
	while(input[ip] != '\0'){
		char action[50];
		char ch = input[ip];
		push(ch);
		sprintf(action , "SHIFT: %c" , ch);
		ip++;
		printf("%-25s %-25s %-25s\n", stack, input+ip, action);
		while(reduce());
	}
	
	while(reduce());
	
	char start = productions[0][0];
	if(sp == 1 && stack[sp] == start && stack[0] == '$'){
		printf("INPUT PARSED SUCCESSFULLY\n");
	}else{
		printf("INPUT NOT PARSED SUCCESSFULLY\n");
	}
}
