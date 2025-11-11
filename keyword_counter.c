
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

int keyword_counts[NUM_KEYWORDS] = {0};
int getKeywordIndex(char *buffer) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(keywords[i], buffer) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE *fp;
    char ch;
    char buffer[100];
    int j = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Counting keyword frequency in 'input.c'...\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha(ch) || ch == '_') {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            
            int index = getKeywordIndex(buffer);
            if (index != -1) {
                keyword_counts[index]++;
            }
            ungetc(ch, fp); 
        }
        
        
    }
    
    fclose(fp);

    printf("\n--- Keyword Frequency ---\n");
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (keyword_counts[i] > 0) {
            printf("%-10s : %d\n", keywords[i], keyword_counts[i]);
        }
    }
    printf("--- End ---\n");

    return 0;
}
