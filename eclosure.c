#include<stdio.h>

#define MAX 50

int eps[MAX][MAX]; //epsilon trannsition matrix
int n; //number of states in nfa

void dfs(int state , int visited[]){
	visited[state] = 1;
	for(int v=0;v<n;v++){
		if(eps[state][v] && !visited[v]){
			dfs(v , visited);
		}
	}
}

int main(){
	int et;
	printf("Enter the number of states in NFA:");
	scanf("%d", &n);
	
	printf("Enter the number of epsilon transitions:");
	scanf("%d", &et);
	
	//setting all eps values to 0
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			eps[i][j] = 0;
		}
	}
	
	printf("Enter the pair of states for e transitions: (from to):\n");
	for(int i=0;i<et;i++){
		int u,v;
		scanf("%d %d", &u, &v);
		eps[u][v] = 1;
	}
	
	for(int i=0;i<n;i++){
		int visited[MAX] = {0};
		dfs(i , visited);
		
		//printing the closure of state n
		printf("Epsilon Closure of state %d: {", i);
		for(int i=0;i<n;i++){
			if(visited[i]){
				printf(" %d ", i);
			}
		}
		printf("} \n");
	}
}
