#include<stdio.h>
#include <stdlib.h>

int braceCounter = 0;
int bracketCounter = 0;
int parenthesisCounter = 0;

void counters(char ch) {
    if(ch == '(') {
        parenthesisCounter++;
    }
    else if(ch == ')') {
        parenthesisCounter--;
    }
    else if(ch == '[') {
        bracketCounter++;
    }
    else if(ch == ']') {
        bracketCounter--;
    }
    else if(ch == '{') {
        braceCounter++;
    }
    else if(ch == '}') {
        braceCounter--;
    }
}

int main(int argc, char const *argv[]) {
    const char *fileName = argv[1];
    FILE *file;
    
    file = fopen(fileName, "r"); 
 
    if (file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("This program it's not using any kind of data structures.\n");

    char ch;
    int hasErrors = 0;
    int forceExit = 0;
    // Check all chars
    while(!forceExit && (ch = fgetc(file)) != EOF) {
        if(ch == '/') {
            char ch2 = fgetc(file);
            // If one line comment, consume char until end of line
            // Prevents the counters from being affected from any quotation mar or parenthisis in the comment
            if(ch2 == '/') {
                while(ch != '\n' && ch != EOF) {
                    ch = fgetc(file);
                    fgetc(file);
                }
                if(ch == EOF) forceExit = 1;
            }
            // For multi-line comment
            else if(ch2 == '*') {
                ch = fgetc(file);
                ch2 = fgetc(file);
                while(ch != '*' && ch2 != '/') {
                    ch = ch2;
                    if((ch2 = fgetc(file)) == EOF) {
                        forceExit = 1;
                        hasErrors = 1;
                        printf("Multi-line comment block not ended.\n");
                        break;
                    }
                }
            }
            else {
                counters(ch);
            }
        }
        else if(ch == '\'' || ch == '"') {
            char temp = ch;
            int done = 0;
            while((ch = fgetc(file)) != EOF) {
                if(ch == temp) {
                    done = 1;
                    break;
                }
                if(ch == '\n') {
                    // If end of line and the quotes haven't been matched, error.
                    break;
                }
            }
            if(!done) {
                printf("Quote unbalanced\n");
                hasErrors = 1;
            }
        }
        else {
            counters(ch);
        }
    }

    if(parenthesisCounter != 0) {
        printf("%d parenthesis unbalanced.\n", parenthesisCounter);
        hasErrors = 1;
    }
    if(bracketCounter != 0) {
        printf("%d brackets unbalanced.\n", bracketCounter);
        hasErrors = 1;
    }
    if(braceCounter != 0) {
        printf("%d braces unbalanced\n", braceCounter);
        hasErrors = 1;
    }

    if(!hasErrors) printf("No errors found!\n");

    fclose(file);

    return 0;
}