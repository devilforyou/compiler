#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fp;
    int c;
    long char_counts[256] = {0}; // Array for all ASCII characters

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Analyzing character frequency in 'input.c'...\n");

    while ((c = fgetc(fp)) != EOF) {
        char_counts[c]++;
    }

    fclose(fp);

    printf("\n--- Character Frequency Analysis ---\n");
    
    for (int i = 0; i < 256; i++) {
        if (isgraph(i) && char_counts[i] > 0) {
            printf("'%c' : %ld\n", (char)i, char_counts[i]);
        }
    }
    
    if (char_counts[' '] > 0) {
        printf("' ' (space) : %ld\n", char_counts[' ']);
    }
    if (char_counts['\n'] > 0) {
        printf("'\\n' (newline) : %ld\n", char_counts['\n']);
    }
     if (char_counts['\t'] > 0) {
        printf("'\\t' (tab) : %ld\n", char_counts['\t']);
    }

    printf("--- End ---\n");

    return 0;
}
