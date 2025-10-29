#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX], firstSet[MAX][MAX], followSet[MAX][MAX];
int n; // number of productions

int addToSet(char *set, char c) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == c)
            return 0;
    }
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
    return 1;
}

void findFirst(char *result, char c) {
    if (!isupper(c)) {
        addToSet(result, c); // terminal
        return;
    }

    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            if (production[i][2] == '#') { // epsilon
                addToSet(result, '#');
            } else {
                int j = 2;
                while (production[i][j] != '\0') {
                    char next = production[i][j];
                    if (!isupper(next)) {
                        addToSet(result, next);
                        break;
                    } else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        int hasEpsilon = 0;
                        for (int k = 0; temp[k] != '\0'; k++) {
                            if (temp[k] != '#')
                                addToSet(result, temp[k]);
                            else
                                hasEpsilon = 1;
                        }
                        if (!hasEpsilon) break;
                        j++;
                        if (production[i][j] == '\0')
                            addToSet(result, '#');
                    }
                }
            }
        }
    }
}

void findFollowHelper(char *result, char c, char *visited) {
    for (int i = 0; visited[i] != '\0'; i++) {
        if (visited[i] == c)
            return; // already visited
    }

    int len = strlen(visited);
    visited[len] = c;
    visited[len + 1] = '\0';

    if (production[0][0] == c) {
        addToSet(result, '$');
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                int k = j + 1;
                int allEpsilon = 1;

                while (production[i][k] != '\0' && allEpsilon) {
                    allEpsilon = 0;
                    char next = production[i][k];

                    if (!isupper(next)) {
                        addToSet(result, next);
                        break;
                    } else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        int hasEpsilon = 0;
                        for (int x = 0; temp[x] != '\0'; x++) {
                            if (temp[x] != '#')
                                addToSet(result, temp[x]);
                            else
                                hasEpsilon = 1;
                        }
                        if (hasEpsilon)
                            allEpsilon = 1;
                    }
                    k++;
                }

                if ((production[i][k] == '\0' && production[i][0] != c) || allEpsilon) {
                    char temp2[MAX] = "";
                    findFollowHelper(temp2, production[i][0], visited);
                    for (int x = 0; temp2[x] != '\0'; x++)
                        addToSet(result, temp2[x]);
                }
            }
        }
    }
}

void findFollow(char *result, char c) {
    char visited[MAX] = "";
    findFollowHelper(result, c, visited);
}

int main() {
    int i;
    char first[MAX], follow[MAX];
    char c;
    char printed[MAX] = ""; // ✅ NEW — to track printed non-terminals

    printf("Enter Number of Productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter Productions (like E=E+T or T=T*F):\n");
    for (i = 0; i < n; i++) {
        fgets(production[i], MAX, stdin);
        for (int j = 0; production[i][j] != '\0'; j++) {
            if (production[i][j] == '\n') {
                production[i][j] = '\0';
                break;
            }
        }
    }

    printf("\nFIRST and FOLLOW sets:\n");

    for (i = 0; i < n; i++) {
        c = production[i][0];

        // ✅ Skip already processed non-terminals
        int alreadyPrinted = 0;
        for (int k = 0; printed[k] != '\0'; k++) {
            if (printed[k] == c) {
                alreadyPrinted = 1;
                break;
            }
        }
        if (alreadyPrinted) continue;

        int len = strlen(printed);
        printed[len] = c;
        printed[len + 1] = '\0';

        memset(first, 0, sizeof(first));
        memset(follow, 0, sizeof(follow));

        findFirst(first, c);
        findFollow(follow, c);

        printf("\n%c:\n", c);
        printf("FIRST(%c) = { ", c);
        for (int j = 0; first[j] != '\0'; j++)
            printf("%c ", first[j]);
        printf("}\n");

        printf("FOLLOW(%c) = { ", c);
        for (int j = 0; follow[j] != '\0'; j++)
            printf("%c ", follow[j]);
        printf("}\n");
    }

    return 0;
}

