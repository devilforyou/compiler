
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char ch;
    int line_number = 1;

    int in_multi_comment = 0;
    int in_string = 0;
    char buffer[256];
    int j = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Scanning 'input.c' for lexical errors...\n");

    while ((ch = fgetc(fp)) != EOF) {
        
        if (ch == '\n') {
            line_number++;
        }

        if (in_multi_comment) {
            if (ch == '*') {
                if ((ch = fgetc(fp)) == '/') {
                    in_multi_comment = 0;
                } else {
                    ungetc(ch, fp);
                }
            }
            continue;
        }
        
        // State: Inside a string literal
        if (in_string) {
            if (ch == '"') {
                in_string = 0;
            } else if (ch == '\\') {
                fgetc(fp); // Skip escaped character
            } else if (ch == '\n') {
                printf("Error [Line %d]: Unclosed string literal (newline found).\n", line_number);
                in_string = 0;
            }
            continue;
        }

        // Check for comment/string starts
        if (ch == '/') {
            char next_ch = fgetc(fp);
            if (next_ch == '*') {
                in_multi_comment = 1;
                continue;
            } else if (next_ch == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                ungetc(ch, fp); // Put back newline or EOF
                continue;
            } else {
                ungetc(next_ch, fp);
            }
        }

        if (ch == '"') {
            in_string = 1;
            continue;
        }

       if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            
                int k = 0;
            while (isdigit(buffer[k])) k++; // Skip initial digits
            if (isalpha(buffer[k])) {
                 printf("Error [Line %d]: Invalid identifier '%s'.\n", line_number, buffer);
            }
            ungetc(ch, fp);
        }
    }

    if (in_multi_comment) {
        printf("Error [Line %d]: Unfinished multi-line comment at EOF.\n", line_number);
    }
    if (in_string) {
        printf("Error [Line %d]: Unclosed string literal at EOF.\n", line_number);
    }

    printf("Scan complete.\n");
    fclose(fp);
    return 0;
}
