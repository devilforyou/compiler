#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
#define NUM_KEYWORDS 32

int isKeyword(char *token) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(keywords[i], token) == 0) {
            return 1;
        }
    }
    return 0;
}

int isIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') {
        return 0;
    }
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int isConstant(char *token) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        int has_dot = 0;
        for (int i = 1; token[i] != '\0'; i++) {
            if (token[i] == '.') {
                if (has_dot) return 0; // Multiple dots
                has_dot = 1;
            } else if (!isdigit(token[i])) {
                return 0; // Not a digit or a dot
            }
        }
        return 1;
    }
    // Simple check for char constant
    if (token[0] == '\'' && token[1] != '\0' && token[2] == '\'') {
        return 1;
    }
    return 0;
}

int main() {
    char line[256];
    char *token;
    const char *delimiters = " \t\n()[]{};,+-*/%&|!=<>";

    printf("Enter a line of code: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }

    line[strcspn(line, "\n")] = 0;

    printf("\n--- Analysis ---\n");
    token = strtok(line, delimiters);

    while (token != NULL) {
        if (isKeyword(token)) {
            printf("'%s' is a KEYWORD\n", token);
        } else if (isIdentifier(token)) {
            printf("'%s' is an IDENTIFIER\n", token);
        } else if (isConstant(token)) {
            printf("'%s' is a CONSTANT\n", token);
        } else {
            printf("'%s' is OTHER (e.g., part of operator, unclassified)\n", token);
        }
        token = strtok(NULL, delimiters);
    }
    printf("--- End ---\n");

    return 0;
}
