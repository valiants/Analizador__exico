#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define ID_NUMBER 1000
#define ID_ENTERO 1001
#define ID_OPERADOR 1002

typedef struct token_tag{
    char *lexema;
    int id;
}token;

int isnumber(char c);
int isLetter(char c);
int isalphanum(char c);
int ishex(char c);
token_tag* Com_Numero(FILE *pf);
token_tag* tokenCreate();
void tokenfree(token_tag *t);
void tokwnSetlex(token_tag *t, char *lex);
token *is_Number(FILE *pf);
token *Integer(FILE *pf);
token *Operador(FILE *pf);
