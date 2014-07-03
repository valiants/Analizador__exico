#include "lex.h"
#define A1 2
#define ERROR -1
#define A2 3


int isLetter(char c)
{
    if (c >= 'A' && c <= 'z')
    {
        return TRUE;
    }
    return FALSE;
}

int isnumber(char c)
{
    if(c >= '0' && c <= '9')
    {
        return TRUE;
    }
    return FALSE;
}

int isalphanum(char c)
{
    if(isLetter(c) || isnumber(c) )
    {
        return TRUE;
    }
    return FALSE;
}

int ishex(char c)
{
    if(isnumber(c) || c >= 'A' && c <= 'F' )
    {
        return TRUE;
    }
    return FALSE;
}

token_tag* Com_Numero(FILE *pf)
{
    //int x = 0;
    token_tag *t;
    char c;
    int state = 0, is_token = FALSE, count=0;
    long int pos;
    pf = fopen("/home/EdwinLara/Documentos/Proyectos/AnalizadorLexico/dato.txt","rb");
    if(pf != NULL)
    {
        pos = ftell(pf);
        do
        {
            switch(state)
            {
                case 0:
                c = fgetc(pf);
                if(isnumber(c))
                {
                    state = A1;
                    count++;
                }
                else
                {
                    if(c=='+' || c=='-')
                    {
                        state = 1;
                        count++;
                    }
                    else
                    {
                        state = ERROR;
                    }
                }break;
                case 1:
                {
                    c = fgetc(pf);
                    if(isnumber(c))
                    {
                        state = A1;
                        count++;
                    }
                        else
                    {
                        state = ERROR;
                    }
                }break;
                case A1:
                {
                    c = fgetc(pf);
                    if(isnumber(c))
                    {
                        state = A1;
                        count++;
                    }
                    else
                    {
                        if(c == '.')
                        {
                            state = A2;
                            count++;
                        }
                        else
                        {
                            state = ERROR;
                            is_token = TRUE;
                        }
                    }
                }break;
                case A2:
                {
                    c = fgetc(pf);
                    if(isnumber(c))
                    {
                        state = A1;
                        count++;
                    }
                    else
                    {
                        state = ERROR;
                        is_token = TRUE;
                    }
                }break;
            }
        }while(state != ERROR);
        if(is_token)
        {
            fseek(pf,pos,SEEK_SET);
            t = tokenCreate();
            t->lexema = (char*)malloc(sizeof(char)*(count+1));
            for(int k=0;k<count;k++)
            {
                t->lexema[k] = fgetc(pf);
                t->id = ID_NUMBER;
            }
            t->lexema[count] = '\0';
        }
        else
        {
            fseek(pf,pos,SEEK_SET);
            return NULL;
        }
    }
    else
    {
        printf("Error al abrir el archivo\n");
    }
    fclose(pf);
    return t;
}

token_tag* tokenCreate()
{
    token_tag *retval;
    retval = (token_tag*)malloc(sizeof(token_tag));
    retval->lexema=NULL;
    retval->id = 0;

    return retval;
}

void tokenfree(token_tag *t)
{
    if(t->lexema != NULL)
    {
        free(t->lexema);
        t->id = 0;
        free(t);
    }
}

void tokenSetlex(token_tag *t, char *lex)
{
    int k;
    int l = strlen(lex);
    t->lexema = (char*)malloc(sizeof(char)*(l+1));
    for(k=0;k<l;k++)
    {
        t->lexema[k] = lex[k];
    }
    t->lexema[l] = '\0';
}
