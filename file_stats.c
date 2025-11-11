
#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char ch, next_ch;
    
    int line_count = 1; 
    int token_count = 0;
    int comment_count = 0;
    
    int in_token = 0;
    int in_single_comment = 0;
    int in_multi_comment = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Analyzing 'input.c'...\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }

        if (in_multi_comment) {
            if (ch == '*' && (next_ch = fgetc(fp)) == '/') {
                in_multi_comment = 0;
            } else {
                ungetc(next_ch, fp);
            }
            continue; // Ignore chars in comment
        } else if (in_single_comment) {
            if (ch == '\n') {
                in_single_comment = 0;
            }
            continue; // Ignore chars in comment
        }

        if (ch == '/') {
            next_ch = fgetc(fp);
            if (next_ch == '/') {
                in_single_comment = 1;
                comment_count++;
                continue;
            } else if (next_ch == '*') {
                in_multi_comment = 1;
                comment_count++;
                continue;
            } else {
                ungetc(next_ch, fp);
            }
        }
        
        if (!isspace(ch) && 
            ch != '(' && ch != ')' && ch != '{' && ch != '}' && 
            ch != ';' && ch != ',' && ch != '#') {
            if (in_token == 0) {
                in_token = 1;
                token_count++;
            }
        } 
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || 
                 ch == ';' || ch == ',' || ch == '#') {
            token_count++;
            in_token = 0; // Reset token state
        }
        else if (isspace(ch)) {
            in_token = 0;
        }
    }

    fclose(fp);

    if (line_count == 0 && token_count > 0) {
        line_count = 1;
    }

    printf("--- Statistics ---\n");
    printf("Total Lines:    %d\n", line_count);
    printf("Total Tokens:   %d\n", token_count);
    printf("Total Comments: %d\n", comment_count);

    return 0;
}
