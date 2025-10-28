#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char stack[50] , terminals[10] , input[50] , table[10][10];
int n; //number of terminals

int getIndex(char c){
	for(int i=0;i<n;i++){
		if(terminals[i]==c) return i;
	}
	return -1;
}

int main(){
	printf("Enter number of terminals:");
	scanf("%d" , &n);
	printf("Enter the terminals:");
	for(int i=0;i<n;i++){
		scanf(" %c" ,&terminals[i]);
	}
	printf("Enter the precendence:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("Enter the precedence between %c %c:",terminals[i] , terminals[j]);
			scanf(" %c" , &table[i][j]);
		}
	}
	
	printf("\nPRECEDENCE TABLE\n\t");
	for (int i = 0; i < n; i++) {
	    printf("%c\t", terminals[i]);  // Print header row
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
	    printf("%c\t", terminals[i]);  // Row label
	    for (int j = 0; j < n; j++) {
		printf("%c\t", table[i][j]);  // Table entries
	    }
	    printf("\n");  // Move to next row
	}
	
	printf("Enter the input string with $ at the end:");
	scanf("%s" , input);
	int i = 0 , top = 0;
	stack[top] = '$';
	
	printf("\nStack\tInput\tAction\n");
	
	while(1){
		char a = stack[top];
		while(a == '<' && top>0)
			a = stack[--top];
		char b = input[i];
		
		int x = getIndex(a);
		int y = getIndex(b);
		
		if(x == -1 || y == -1){
			printf("Error unknown terminal\n");
			break;
		}
		
		if(a == '$' && b == '$') {
			printf("ACCEPTED\n");
			break;
		}
		
		//shift operation
		
		if(table[x][y] == '<' || table[x][y] == '='){
			stack[++top] = '<';
			stack[++top] = b;
			stack[top+1] = '\0';
			i++;
			printf("%s\t%s\tSHIFT\n", stack , &input[i]);
		}
		
		//reduce operation
		
		else if(table[x][y] == '>'){
			while(top>0 && stack[top] != '<') top--;
			stack[top+1] = '\0';
			printf("%s\t%s\tREDUCE\n", stack , &input[i]);
		}
		
		else{
			printf("REJECTED\n");
			break;
		}
	}
	

}
