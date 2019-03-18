#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int S();
int D();
int A();
int B();
int O();

char currentTree[256];
char *next;

int IDc;
int floatDCLc;
int intDCLc;
int floatNc;
int intNc;
int Nc;

int match(char c) {
    if(c == *next) {
        next++;
        return 1;
    }
    return 0;
}

int D() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('f') && match('l') && match('o') && match('a') && match('t') && match('d') && match('c') && match('l') && match(' ') && match('i') && match('d')) {
        IDc++;
        floatDCLc++;
        sprintf(inner, "\tD -> {floatdcl%d, id%d}\n\t{rank=same floatdcl%d->id%d [style=invis]}\n", floatDCLc, IDc, floatDCLc, IDc);
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('i') && match('n') && match('t') && match('d') && match('c') && match('l') && match(' ') && match('i') && match('d')) {
        IDc++;
        intDCLc++;
        sprintf(inner, "\tD -> {intdcl%d, id%d}\n\t{rank=same intdcl%d->id%d [style=invis]}\n", intDCLc, IDc, intDCLc, IDc);
        strcat(currentTree, inner);
        return 1;
    }

    return 0;
}


int N() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('i') && match('d')) {
        IDc++;
        Nc++;
        sprintf(inner, "\tN%d -> id%d\n", Nc, IDc);
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('f') && match('n') && match('u') && match('m')) {
        floatNc++;
        Nc++;
        sprintf(inner, "\tN%d -> fnum%d\n", Nc, floatNc);
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('i') && match('n') && match('u') && match('m')) {
        intNc++;
        Nc++;
        sprintf(inner, "\tN%d -> inum%d\n", Nc, intNc);
        strcat(currentTree, inner);
        return 1;
    }

    return 0;
}

int O() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('p') && match('l') && match('u') && match('s')) {
        sprintf(inner, "\tO -> plus\n");
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('m') && match('i') && match('n') && match('u') && match('s')) {
        sprintf(inner, "\tO -> minus\n");
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('d') && match('i') && match('v')) {
        sprintf(inner, "\tO -> plus\n");
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('m') && match('u') && match('l') && match('t')) {
        sprintf(inner, "\tO -> plus\n");
        strcat(currentTree, inner);
        return 1;
    }

    return 0;
}


int B() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match(' ') && O() && match(' ') && N()) {
        IDc++;
        sprintf(inner, "\tB -> {O, N%d}\n\t{rank=same O->N%d [style=invis]}\n", Nc, Nc);
        strcat(currentTree, inner);
        Nc--;
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(1) { // LAMBDA
        sprintf(inner, "\tB -> λ\n");
        strcat(currentTree, inner);
        return 1;
    }

    return 0;
}

int A() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('i') && match('d') && match(' ') && match('a') && match('s') && match('s') && match('i') && match('g') && match('n') && match(' ') &&
        N() && B()) {
        IDc++;
        sprintf(inner, "\tA -> {id%d assign N%d B}\n\t{rank=same id%d->assign->N%d->B [style=invis]}\n", IDc, Nc, IDc, Nc);
        strcat(currentTree, inner);
        Nc--;
        return 1;
    }

    return 0;
}

int getParseTree() {
    char *copyNext = next;
    char copyTree[512];
    char inner[512];
    strcpy(copyTree, currentTree);

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(match('p') && match('r') && match('i') && match('n') && match('t') && match(' ') && match('i') && match('d')) {
        sprintf(inner, "\tS -> {print, id%d}\n\t{rank=same print->id%d [style=invis]}\n", IDc, IDc);
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(D()) {
        sprintf(inner, "\tS -> D\n");
        strcat(currentTree, inner);
        return 1;
    }

    strcpy(currentTree, copyTree);
    next = copyNext;
    if(A()) {
        sprintf(inner, "\tS -> A\n");
        strcat(currentTree, inner);
        return 1;
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    const char *tokensFileName = argv[1];
    FILE *tokensFile = fopen(tokensFileName, "r"); 
    FILE *outFile = fopen("parse_tree.out", "w"); 
 
    if (tokensFile == NULL || outFile == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("This program will output to parse_tree.out.\nNodes contain numbers for logic purposes. Ignore those numbers.\n");

    fprintf(outFile, "//Nodes contain numbers for logic purposes. Ignore those numbers.\n");

    int lineCounter = 0;
    char line[512];
    while(fgets(line, sizeof(line), tokensFile) != NULL) {
        // printf("%s", line);
        if(line[0] == '\n') continue;

        IDc = 0;
        Nc = 0;
        floatDCLc = 0;
        intDCLc = 0;
        intNc = 0;
        floatNc = 0;
        next = line;
        strcpy(currentTree, "");

        fprintf(outFile, "digraph G%d {\n\tlabel=\"Line %d\"\n", lineCounter, lineCounter);
        if(getParseTree()) {
            fprintf(outFile, "%s", currentTree);
        }
        else {
            fprintf(outFile, "\tNULL\n");
        }
        fprintf(outFile, "}\n\n");
        lineCounter++;
    }

    fclose(tokensFile);
    fclose(outFile);
    exit(EXIT_SUCCESS);
}
