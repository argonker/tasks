%{

#include <stdio.h>
#include <ctype.h>

void yyerror(char *s);
int  yylex(void);
%}

%token NUMBER

%%

P: expr { printf("= %d\n", $1); }

expr: expr '+' sum { $$ = $1 + $3; } | expr '-' sum  { $$ = $1 - $3; } | sum { $$ = $1; }

sum: sum '*' mult { $$ = $1 * $3; } | sum '/' mult  { $$ = $1 / $3; } | mult { $$ = $1; }

mult: '(' expr ')' { $$ = $2; } | '-' mult { $$ = -$2; } | NUMBER { $$ = $1; }

%%

int main(void)
{
    printf("Enter your expression: ");
    yyparse();
    return 0;
}

int yylex(void)
{
    int c;

    while ((c = getchar()) == ' ' || c == '\t' || c == '\n');

    if (c == EOF)
        return 0;

    if (isdigit(c)) {
        int val = 0;
        do {
            val = val * 10 + (c - '0');
            c = getchar();
        } while (isdigit(c));
        ungetc(c, stdin);
        yylval = val;
        return NUMBER;
    }

    return c;
}

void yyerror(char *s)
{
    printf("Error: %s\n", s);
}
