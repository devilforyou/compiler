
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[512];

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file 'input.c'\n");
        return 1;
    }

    printf("Preprocessor directives found in 'input.c':\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }
        
         if (line[i] == '#') {
           printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
