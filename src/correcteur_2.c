#include <stdio.h>
#include "Liste.h"
#include "BK.h"
#include "Auxiliaire.h"
#include "Levenshtein.h"
#include "ATR.h"

int main(int argc, char *argv[])
{
    ArbreBK A;
    FILE *dico;
    FILE *texte;
    FILE *clean_texte;
    Liste erronee;
    Liste Corrections;
    char mot_texte[80];
    dico = NULL;
    texte = NULL;
    erronee = NULL;
    A = NULL;
    if (argc < 2)
    {
        printf("Pas assez d'arguments\n");
        return 0;
    }
    texte = fopen(argv[1], "r");
    if (texte == NULL)
    {
        return 0;
    }
    dico = fopen(argv[2], "r");
    if (dico == NULL)
    {
        return 0;
    }
    A = creer_ArbreBK(dico);

    clean_texte = nouveau(argv[1], "obj/nouveau");
    clean_texte = fopen("obj/nouveau", "r");
    while (fscanf(clean_texte, "%s", mot_texte) != EOF)
    {
        if (recherche_exacte(A, mot_texte) == 0)
        {
            inserer_en_tete(&erronee, mot_texte);
        }
    }

    while (erronee != NULL)
    {
        printf("Mot(s) mal orthographié : %s \n", erronee->mot);
        Corrections = NULL;
        Corrections = rechercher_dans_ArbreBK(A, erronee->mot);
        printf("Proposition(s) : ");
        while (Corrections->suivant != NULL)
        {
            printf("%s, ", Corrections->mot);
            Corrections = Corrections->suivant;
        }
        printf("%s", Corrections->mot);
        liberer_Liste(&Corrections);
        printf("\n");
        erronee = erronee->suivant;
    }
    afficher_ArbreBK(A);
    liberer_ArbreBK(&A);
    liberer_Liste(&Corrections);
    liberer_Liste(&erronee);
    return 0;
}