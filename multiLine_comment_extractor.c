

#include <stdio.h>

int main() {
    FILE *fp;
    char ch, next_ch;
    int in_multi_comment = 0;
    int found_comment = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Extracting multi-line comments from 'input.c':\n");
    printf("---------------------------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (in_multi_comment) {
            if (ch == '*') {
                next_ch = fgetc(fp);
                if (next_ch == '/') {
                    in_multi_comment = 0;
                    printf("*/\n\n"); // End of comment
                } else {
                    fputc(ch, stdout);
                    ungetc(next_ch, fp);
                }
            } else {
                fputc(ch, stdout); // Print char inside comment
            }
        } else {
            if (ch == '/') {
                next_ch = fgetc(fp);
                if (next_ch == '*') {
                    in_multi_comment = 1;
                    found_comment = 1;
                    printf("/*"); // Start of comment
                } else {
                    ungetc(next_ch, fp);
                }
            }
        }
    }
    
    printf("---------------------------------------------\n");
    if (!found_comment) {
        printf("No multi-line comments found.\n");
    }

    fclose(fp);
    return 0;
}
