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
int isValidIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') {
        printf("Error: Must start with a letter or underscore.\n");
        return 0;
    }

    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            printf("Error: Contains invalid character '%c'.\n", token[i]);
            return 0;
        }
    }

    if (isKeyword(token)) {
        printf("Error: Identifier cannot be a keyword.\n");
        return 0;
    }

    return 1;
}

int main() {
    char identifier[100];

    printf("Enter an identifier to validate: ");
    if (scanf("%99s", identifier) != 1) {
        return 1;
    }

    if (isValidIdentifier(identifier)) {
        printf("Input: %s -> Valid\n", identifier);
    } else {
        printf("Input: %s -> Invalid\n", identifier);
    }

    return 0;
}
