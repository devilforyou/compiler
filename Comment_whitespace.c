#include <ctype.h>
#include <stdio.h>

int main() {
    FILE *fin, *fout;
    char ch, next_ch;
    int in_single_comment = 0;
    int in_multi_comment = 0;
    int last_char_was_space = 0;

    fin = fopen("input.c", "r");
    fout = fopen("output.c", "w");

    if (fin == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }
    if (fout == NULL) {
        printf("Error: Could not open file 'output.c'\n");
        fclose(fin);
        return 1;
    }

    printf("Removing comments and extra whitespace from 'input.c'...\n");

    while ((ch = fgetc(fin)) != EOF) {
        if (in_multi_comment) {
            if (ch == '*' && (next_ch = fgetc(fin)) == '/') {
                in_multi_comment = 0;
                last_char_was_space = 1; // Treat end of comment as space
            } else {
                ungetc(next_ch, fin);
            }
        } 
        else if (in_single_comment) {
            if (ch == '\n') {
                in_single_comment = 0;
                fputc(ch, fout); // Keep the newline
                last_char_was_space = 1;
            }
        }
        else {
            if (ch == '/') {
                next_ch = fgetc(fin);
                if (next_ch == '/') {
                    in_single_comment = 1;
                } else if (next_ch == '*') {
                    in_multi_comment = 1;
                } else {
                    fputc(ch, fout);
                    ungetc(next_ch, fin);
                    last_char_was_space = 0;
                }
            }
            else if (isspace(ch)) {
                if (!last_char_was_space) {
                    if (ch == '\n') {
                         fputc(ch, fout); 
                    } else {
                         fputc(' ', fout); 
                    }
                }
                last_char_was_space = 1;
            }
            // Any other character
            else {
                fputc(ch, fout);
                last_char_was_space = 0;
            }
        }
    }

    fclose(fin);
    fclose(fout);

    printf("Done. Output saved to 'output.c'.\n");
    return 0;
}
