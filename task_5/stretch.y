%{

#include <stdio.h>
void yyerror(char *s);
int yylex(void);
%}

%%

P: S { printf("stretch: %d\n", $1); }

S: '(' S ')' S { $$ = 1 + $4; } | { $$ = 0; }

%%

int main(void)
{
    printf("Enter your bracer system: ");
    yyparse();
    return 0;
}

int yylex(void)
{
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');

    if (c == '\n' || c == EOF)
        return 0; 

    yylval = c;
    return c;
}

void yyerror(char *s)
{
    printf("Error: %s\n", s);
}
