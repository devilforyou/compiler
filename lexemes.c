
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char ch, next_ch;
    char buffer[100];
    int j = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Extracting lexemes from 'input.c':\n---\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) {
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            printf("%s\n", buffer);
            ungetc(ch, fp); 
        }
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = fgetc(fp)) || ch == '.') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            printf("%s\n", buffer);
            ungetc(ch, fp); 
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || 
                 ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '&' || ch == '|') {
            
            buffer[j++] = ch;
            next_ch = fgetc(fp);
            
            if ((ch == '=' && next_ch == '=') || (ch == '!' && next_ch == '=') ||
                (ch == '<' && next_ch == '=') || (ch == '>' && next_ch == '=') ||
                (ch == '&' && next_ch == '&') || (ch == '|' && next_ch == '|') ||
                (ch == '+' && next_ch == '+') || (ch == '-' && next_ch == '-')) {
                buffer[j++] = next_ch;
            } else {
                ungetc(next_ch, fp);
            }
            
            buffer[j] = '\0';
            j = 0;
            printf("%s\n", buffer);
        }
        else if (ch == '"') {
            buffer[j++] = ch;
            while ((ch = fgetc(fp)) != '"' && ch != EOF) {
                buffer[j++] = ch;
                if (ch == '\\') {
                    buffer[j++] = fgetc(fp);
                }
            }
            buffer[j++] = '"';
            buffer[j] = '\0';
            j = 0;
            printf("%s\n", buffer);
        }
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',' || ch == ':' || ch == '#') {
            printf("%c\n", ch);
        }
    }

    printf("---\n");
    fclose(fp);
    return 0;
}
