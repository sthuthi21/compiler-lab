%{
#include <stdio.h>
int v = 0, c = 0;
%}

%%
[aeiouAEIOU]        { v++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]  { c++; }
\n                  { return 0; }   // Stop reading when newline entered
.                   ;               // Ignore everything else
%%

int main() {
    printf("Enter a string: ");
    yylex();
    printf("\nNumber of vowels: %d\n", v);
    printf("Number of consonants: %d\n", c);
    return 0;
}

int yywrap() {
    return 1;
}

