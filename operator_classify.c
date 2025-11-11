
#include <stdio.h>
#include <string.h>

int main() {
    char line[256];
    char buffer[10];
    int j = 0;

    printf("Enter a line of code: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }

    printf("\n--- Operators Found ---\n");

    for (int i = 0; line[i] != '\0'; i++) {
        char ch = line[i];
        char next_ch = line[i+1];
        
        buffer[0] = '\0'; // Clear buffer

        if ((ch == '=' && next_ch == '=') || (ch == '!' && next_ch == '=') ||
            (ch == '<' && next_ch == '=') || (ch == '>' && next_ch == '=')) {
            sprintf(buffer, "%c%c", ch, next_ch);
            printf("'%s' -> Relational Operator\n", buffer);
            i++; // Skip next char
        } else if ((ch == '&' && next_ch == '&') || (ch == '|' && next_ch == '|')) {
            sprintf(buffer, "%c%c", ch, next_ch);
            printf("'%s' -> Logical Operator\n", buffer);
            i++; // Skip next char
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            printf("'%c' -> Arithmetic Operator\n", ch);
        } 
        else if (ch == '<' || ch == '>') {
            printf("'%c' -> Relational Operator\n", ch);
        } 
        else if (ch == '!') {
            printf("'%c' -> Logical Operator\n", ch);
        }
        else if (ch == '=') {
             printf("'%c' -> Assignment Operator\n", ch);
        }
    }
    
    printf("--- End ---\n");
    return 0;
}
