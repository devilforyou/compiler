#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char line[256];
    char *token;
    const char *delimiters = " \t\n=;(){}";

    printf("Enter a line of code: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }

    printf("\n--- Constants Found ---\n");
    token = strtok(line, delimiters);

    while (token != NULL) {
        int is_float = 0;
        int is_int = 1;
        int len = strlen(token);

        if (len >= 3 && token[0] == '\'' && token[len - 1] == '\'') {
            printf("Character: %s\n", token);
        }
        else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            for (int i = 1; token[i] != '\0'; i++) {
                if (token[i] == '.') {
                    is_float = 1;
                    is_int = 0;
                } else if (!isdigit(token[i])) {
                    is_int = 0;
                    is_float = 0; // Not a simple number
                    break;
                }
            }
            
            if (is_int) {
                printf("Integer:   %s\n", token);
            } else if (is_float) {
                printf("Float:     %s\n", token);
            }
        }

        token = strtok(NULL, delimiters);
    }
    printf("--- End ---\n");
    return 0;
}
