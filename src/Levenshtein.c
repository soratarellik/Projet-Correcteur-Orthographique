#include <string.h>
#include <stdlib.h>
#include "ATR.h"
#include "Liste.h"

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }
    return b;
}

int min_t(int a, int b, int c)
{
    return min(min(a, b), min(b, c));
}

int Levenshtein(char *un, char *deux)
{
    int i;
    int j;
    int r_value;
    int longueur1;
    int longueur2;
    int insere;
    int supprime;
    int remplace;
    int **tab;
    longueur1 = strlen(un);
    longueur2 = strlen(deux);
    tab = (int **)malloc(sizeof(int *) * longueur1 + 1);
    for (i = 0; i < longueur1 + 1; i++)
    {
        tab[i] = (int *)malloc(sizeof(int) * longueur2 + 1);
    }

    for (i = 0; i <= longueur1; i++)
    {
        tab[i][0] = i;
    }
    for (j = 0; j <= longueur2; j++)
    {
        tab[0][j] = j;
    }
    for (i = 1; i <= longueur1; i++)
    {
        for (j = 1; j <= longueur2; j++)
        {
            if (un[i - 1] == deux[j - 1])
            {
                tab[i][j] = tab[i - 1][j - 1];
            }
            else
            {
                supprime = tab[i - 1][j] + 1;
                insere = tab[i][j - 1] + 1;
                remplace = tab[i - 1][j - 1] + 1;
                tab[i][j] = min_t(supprime, insere, remplace);
            }
        }
    }
    r_value = tab[longueur1][longueur2];

    for (i = 0; i < longueur1 + 1; i++)
    {
        free(tab[i]);
    }
    free(tab);
    return r_value;
}

void lev_aux(ATR A, char *mot, int hauteur, char *mot_corriger, Liste *correction, int *dmin)
{
    int d;
    d = 0;
    if (A == NULL)
    {
        return;
    }
    lev_aux(A->fg, mot, hauteur, mot_corriger, correction, dmin);
    mot[hauteur] = A->lettre;
    if (A->lettre == '\0')
    {
        d = Levenshtein(mot_corriger, mot);
        /*printf("A corriger %s Prop %s Distance %d Dmin %d\n",mot_corriger,mot,d,*dmin);*/
        if (d <= *dmin)
        {
            if (d < *dmin)
            {
                *dmin = d;
                liberer_Liste(correction);
            }
            inserer_en_tete(correction, mot);
        }
    }
    lev_aux(A->fils, mot, hauteur + 1, mot_corriger, correction, dmin);
    lev_aux(A->fd, mot, hauteur, mot_corriger, correction, dmin);
}

void applique_lev(ATR A, char *corriger, Liste *correction, int *dmin)
{
    int hauteur;
    char *mot;
    if (A == NULL)
    {
        return;
    }
    hauteur = hauteur_arbre(A);
    mot = (char *)malloc(sizeof(char) * hauteur);
    if (mot == NULL)
    {
        return;
    }
    else
    {
        lev_aux(A, mot, 0, corriger, correction, dmin);
    }
}