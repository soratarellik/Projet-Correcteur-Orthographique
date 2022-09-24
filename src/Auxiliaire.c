#include <stdio.h>
#include <stdlib.h>
#include "Auxiliaire.h"
#include <ctype.h>

int est_special(char caractere)
{
    char *symbol = "-,.:;'’";
    int i;
    for (i = 0; symbol[i]; i++)
    {
        if (caractere == symbol[i])
        {
            return 1;
        }
    }
    return 0;
}

FILE *nouveau(char *argument, char *nom)
{
    FILE *ecrire;
    FILE *lire;
    char c;
    lire = fopen(argument, "r");
    ecrire = fopen(nom, "w");
    if (lire != NULL && ecrire != NULL)
    {
        while ((c = getc(lire)) != EOF)
        {
            if (est_special(c) == 1)
            {
                putc(' ', ecrire);
            }
            else
            {
                putc(tolower(c), ecrire);
            }
        }
    }
    fclose(ecrire);
    fclose(lire);
    return ecrire;
}
