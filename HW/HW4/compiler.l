%{
#include <stdio.h>
#define YY_DECL int yylex(FILE *outFile)
%}

%%
f                       fprintf(outFile, "floatdcl");
i                       fprintf(outFile, "intdcl");
p                       fprintf(outFile, "print");
[a-eg-hj-oq-z]          fprintf(outFile, "id");
=                       fprintf(outFile, "assign");
[+]                     fprintf(outFile, "plus");
-                       fprintf(outFile, "minus");
\/                      fprintf(outFile, "div");
\*                      fprintf(outFile, "mult");
[0-9]+                  fprintf(outFile, "inum");
[0-9]+[.][0-9]+         fprintf(outFile, "fnum");
[ ]                     fprintf(outFile, " ");
[\r\n]                  fprintf(outFile, "\n");
^\/\/.*                 fprintf(outFile, "COMMENT");
%%

int main(int argc, char **argv) {
    FILE    *fd;
    FILE    *outFile = fopen("lex.out", "w");

    if (argc == 2)
    {
        if (!(fd = fopen(argv[1], "r")))
        {
            perror("Error: ");
            return (-1);
        }
        yyset_in(fd);
        yylex(outFile);
        fclose(fd);
        fclose(outFile);
    }
    else
        printf("Usage: a.out filename\n");
    return (0);
}