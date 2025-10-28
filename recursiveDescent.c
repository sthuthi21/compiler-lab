#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input[50];
int i=0;
char derivation[100] = "E";

void E();
void Edash();
void T();
void Tdash();
void F();

void printDerivation(const char *replace, const char *with){
	char temp[100];
	char *pos;
	strcpy(temp, derivation);
	pos = strstr(temp, replace);
	if(pos){
		int index = pos - temp;
		derivation[index] = '\0';
		
		if(strcmp(with , "e") != 0)
			strcat(derivation, with);
		strcat(derivation , temp + index + strlen(replace));
	}
	printf("E=%-25s \t%s->%s\n", derivation , replace , with);
}

void E(){
	printDerivation("E" , "TE'");
	T();
	Edash();
}

void Edash(){
	if(input[i] == '+'){
		i++;
		printDerivation("E'","+TE'");
		T();
		Edash();
	}
	else{
		printDerivation("E'","e");
		return;
	}
}

void T(){
	printDerivation("T", "FT'");
	F();
	Tdash();
}

void Tdash(){
	if(input[i] == '*'){
		i++;
		printDerivation("T'","*FT'");
		F();
		Tdash();
	}
	else{
		printDerivation("T'", "e");
		return;
	}
}

void F(){
	if(input[i] == 'i'){
		i++;
		printDerivation("F","i");
	}
	else if(input[i] == '('){
		i++;
		printDerivation("F" , "(E)");
		E();
		if(input[i] == ')')
			i++;
		else{
			printf("Error: ) missing \n");
		}
	}
	else{
		printf("Error: Invalid symbol %c \n",input[i]);
	}
}

void main(){
	printf("Enter The Input Expression: ");
	scanf("%s", input); 
	strcat(input, "$"); 
	printf("\n%-30s\t%s\n", "Derivation", "Production Used");
	printf("\n"); 
	printf("%s\n", derivation); 
	E(); 
	if (input[i] == '$') 
		printf("\nParsing Completed Successfully.\n"); 
	else 
		printf("\nParsing Failed.\n"); 
}


/*output

Enter The Input Expression: i+i*i

Derivation                      Production Used

E
E=TE'                           E->TE'
E=FT'E'                         T->FT'
E=iT'E'                         F->i
E=iE'                           T'->e
E=i+TE'                         E'->+TE'
E=i+FT'E'                       T->FT'
E=i+iT'E'                       F->i
E=i+i*FT'E'                     T'->*FT'
E=i+i*iT'E'                     F->i
E=i+i*iE'                       T'->e
E=i+i*i                         E'->e

Parsing Completed Successfully.*/
