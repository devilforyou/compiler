#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "printf", "scanf", "int", "float", "char", "for", "while", "if", "else", "break" , "include" 
};
#define NUM_KEYWORDS 11

int isKeyword(char *buffer) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch;
    char buffer[100];
    int j = 0;

    int keyword_count = 0;
    int identifier_count = 0;
    int operator_count = 0;
    int number_count = 0;
    int special_symbol_count = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Processing file 'input.c'...\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || 
            ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '&' || ch == '|') {
            
            operator_count++;
            
            char next_ch = fgetc(fp);
            if ((ch == '=' && next_ch == '=') || (ch == '!' && next_ch == '=') ||
                (ch == '<' && next_ch == '=') || (ch == '>' && next_ch == '=') ||
                (ch == '&' && next_ch == '&') || (ch == '|' && next_ch == '|')) {
                
            } else {
                ungetc(next_ch, fp);
            }
        } 
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',' || ch == ':' || ch == '#' || ch == '"' || ch == '\'') {
            special_symbol_count++;
        }
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = fgetc(fp)) || ch == '.') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            number_count++;
            ungetc(ch, fp); 
        }
        else if (isalpha(ch) || ch == '_') {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            
            if (isKeyword(buffer)) {
                keyword_count++;
            } else {
                identifier_count++;
            }
            ungetc(ch, fp); 
        }
        else if (isspace(ch)) {
            continue;
        }
    }

    fclose(fp);

    printf("--- Analysis Complete ---\n");
    printf("Keywords:         %d\n", keyword_count);
    printf("Identifiers:      %d\n", identifier_count);
    printf("Operators:        %d\n", operator_count);
    printf("Numbers:          %d\n", number_count);
    printf("Special Symbols:  %d\n", special_symbol_count);

    return 0;
}
