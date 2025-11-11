#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    int in_string = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Finding string literals in 'input.c'...\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '"') {
            if (!in_string) {
                in_string = 1;
                fputc(ch, stdout);
            } else {
                in_string = 0;
                fputc(ch, stdout);
                fputc('\n', stdout);
            }
        } else if (in_string) {
            fputc(ch, stdout);
            
            if (ch == '\\') {
                ch = fgetc(fp); // Print the escaped character
                if (ch != EOF) {
                    fputc(ch, stdout);
                }
            }
        }
    }

    if (in_string) {
        printf("\nError: Unclosed string literal found!\n");
    }

    fclose(fp);
    return 0;
}
