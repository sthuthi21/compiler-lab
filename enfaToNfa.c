#include<stdio.h>
#include<stdlib.h>

#define MAXN 10
#define MAXS 10

int n , symCount;  //no of states and no of symbols
char symbols[MAXS];  // symbols
int eps[MAXN][MAXN]; // epsilon transitions
int epclosure[MAXN][MAXN]; // computed epsilon closures
int trans[MAXN][MAXS][MAXN]; //normal transitions [from][symbolIndex][to]
int visited[MAXN];

void dfsEpclosure(int state , int start){
	visited[state] = 1;
	epclosure[start][state] = 1;
	for(int i=0;i<n;i++){
		if(eps[state][i] && !visited[i]){
			dfsEpclosure(i , start);
		}
	}
}

int findSymbolIndex(char c){
	for(int i=0;i<symCount;i++){
		if(symbols[i] == c) return i;
	}
	return -1;
}

void initialiseMatrices(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			eps[i][j] = 0;
			for(int k=0;k<symCount;k++){
				trans[i][k][j] = 0;
			}
		}
	}
}

int main(){
	printf("Enter the number of states in the NFA:");
	scanf(" %d" , &n);
	printf("Enter the number of symbols (excluding epsilon):");
	scanf(" %d", &symCount);
	printf("Enter the symbols:");
	for(int i=0; i<symCount; i++){
		scanf(" %c", &symbols[i]);
	}
	
	initialiseMatrices();
	
	int eCount , tCount;
	printf("Enter the number of epsilon transitions:");
	scanf("%d" , &eCount);
	printf("Enter the epsilon transitions (from to):\n");
	for(int i=0;i<eCount;i++){
		int from; 
		int to;
		scanf("%d %d", &from , &to);
		eps[from][to] = 1;
	}
	
	printf("Enter the number of normal transitions:");
	scanf("%d", &tCount);
	printf("Enter the normal transitions (from symbol to):\n");
	for(int i=0; i<tCount; i++){
		int from , to;
		char sym;
		scanf(" %d %c %d", &from , &sym , &to);
		int symIndex = findSymbolIndex(sym);
		trans[from][symIndex][to] = 1;
	}
	
	//computing the epsilon closures
	
	for(int state = 0; state<n; state++){
		for(int i = 0; i<n; i++) //resetting the visited array
			visited[i] = 0;
		dfsEpclosure(state , state);
	}
	
	//printing the epsilon closures
	for(int state = 0; state<n; state++){
		printf("Epsilon Closure of state %d: {", state);
		for(int i=0;i<n;i++){
			if(epclosure[state][i]){
				printf(" %d ", i);
			}
		}
		printf("} \n");
	}
	
	//computing the new transitions
	printf("The new transition table:\n");
	for(int state = 0; state<n; state++){ //for each state
		for(int sym=0; sym<symCount; sym++){ //for each symbol
			int result[MAXN] = {0};
			for(int s=0;s<n;s++){ //for each state in epsilon closure of state
				if(epclosure[state][s]){
					for(int p=0;p<n;p++){ //find destination of s and sym
						if(trans[s][sym][p]){
							for(int q=0;q<n;q++){ //if q is in the epsilon closure of p then add it to the result
								if(epclosure[p][q]){
									result[q] = 1;
								}
							}
						}
					}
				}
			}
			//printing the transition for each state and symbol
			printf("%d --%c--> {", state , symbols[sym]);
			for(int i=0;i<n;i++){
				if(result[i]){
					printf(" %d " , i);
				}
			}
			printf("} \n");
		}
		
	}
	
}
