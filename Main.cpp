#include "lex.h"
#include <stdio.h>
int main()
{
    char a = 'Z';
    char b = '9';
    float num;
    FILE *dato;
    token_tag *ca;
    ca = Com_Numero(dato);

    printf("%d\n",isLetter(a));
    printf("%d\n",isnumber(b));

    printf("%d\n",ca->id);
    printf("%s\n",ca->lexema);
    return 0;
}
