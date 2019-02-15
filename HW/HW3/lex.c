#include <stdio.h>
#include <string.h>
#include <regex.h> 

regex_t floatdclREG;
regex_t intdclREG;
regex_t printREG;
regex_t idREG;
regex_t assignREG;
regex_t plusREG;
regex_t minusREG;
regex_t divREG;
regex_t multREG;
regex_t inumREG;
regex_t fnumREG;
regex_t blankREG;

void compileRegexes() {
    regcomp(&floatdclREG, "f", 0);
    regcomp(&intdclREG, "i", 0);
    regcomp(&printREG, "p", 0);
    regcomp(&idREG, "[a-eg-hj-oq-z]", 0);
    regcomp(&assignREG, "=", 0);
    regcomp(&plusREG, "[+]", 0);
    regcomp(&minusREG, "-", 0);
    regcomp(&divREG, "/", 0);
    regcomp(&multREG, "*", 0);
    regcomp(&inumREG, "[0-9][0-9]*", 0);
    regcomp(&fnumREG, "[0-9][0-9]*[.][0-9][0-9]*", 0);
    regcomp(&blankREG, " +", 0);
}

int main(int argc, char const *argv[]) {
    compileRegexes();

    FILE *file = fopen(argv[1], "r");
    FILE *outFile = fopen("lex.out", "w");
    char buffer[2048];

    if( file == NULL ){
        fprintf( stderr, "Unable to open file");
    }
    else {
        while(fgets(buffer, 2048, file) != NULL ){
            char *word = strtok(buffer, " ");
            if(strlen(word) >= 2 && word[0] == '/' && word[1] == '/') continue;
            while(word != NULL){
                if(regexec(&floatdclREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "floatdcl");
                }
                else if(regexec(&intdclREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "intdcl");
                }
                else if(regexec(&printREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "print");
                }
                else if(regexec(&idREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "id");
                }
                else if(regexec(&assignREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "assign");
                }
                else if(regexec(&plusREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "plus");
                }
                else if(regexec(&minusREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "minus");
                }
                else if(regexec(&divREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "div");
                }
                else if(regexec(&multREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "mult");
                }
                else if(regexec(&fnumREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "fnum");
                }
                else if(regexec(&inumREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "inum");
                }
                else if(regexec(&blankREG, word, 0, NULL, 0) == 0) {
                    fprintf(outFile, "blank");
                }
                else {
                    printf("LEXICAL ERROR: No match with %s\n", word);
                }
                word = strtok(NULL, " ");
                fprintf(outFile, " ");
            }
            fprintf(outFile, "\n");

        }
    }
    fprintf(outFile, "$");
    
    fclose(file);
    fclose(outFile);

    return 0;
}
