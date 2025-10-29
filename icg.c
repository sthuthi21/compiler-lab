#include <stdio.h>
#include <string.h>

// Function to generate intermediate code for a specific operator
void generate(char *expr, char op, char *reg) {
    char temp[100];  // Temporary string to hold the modified expression
    int i = 0, j = 0;

    // Loop through the expression character by character
    while (expr[i] != '\0') {
        
        // If the current character matches the operator we're handling
        if (expr[i] == op) {
            
            // Print one line of three-address code: Op  Result  Arg1  Arg2
            // Example: *   Z   c   d
            printf("%c\t%c\t%c\t%c\n", op, *reg, expr[i - 1], expr[i + 1]);

            // Replace the previous operand (expr[i-1]) in the temp string
            // with the result register (like Z, Y, X...)
            temp[j - 1] = *reg;

            // Skip over the operator and next operand
            i += 2;

            // Move to the next available register (Z → Y → X → ...)
            (*reg)--;
        }
        else {
            // Otherwise, copy the character into the temp expression
            temp[j++] = expr[i++];
        }
    }

    // End the modified expression string
    temp[j] = '\0';

    // Copy the modified expression back into expr for the next pass
    strcpy(expr, temp);
}

// Function that generates code for the entire expression
void gencode(char *expr) {
    char reg = 'Z'; // Start with register Z (temporary result names)

    // Generate code in order of operator precedence
    generate(expr, '/', &reg); // Division has highest precedence
    generate(expr, '*', &reg); // Then multiplication
    generate(expr, '+', &reg); // Then addition
    generate(expr, '-', &reg); // Then subtraction
    generate(expr, '=', &reg); // Finally, assignment
}

int main() {
    char expr[100];

    printf("Enter expression: ");
    scanf("%s", expr); // Input expression (e.g., a=b+c*d)

    printf("\nOp\tRes\tArg1\tArg2\n");
    gencode(expr); // Generate and print intermediate code

    return 0;
}

