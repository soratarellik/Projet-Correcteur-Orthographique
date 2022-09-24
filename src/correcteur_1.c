#include <stdio.h>
#include "ATR.h"
#include "Liste.h"
#include "Auxiliaire.h"
#include "Levenshtein.h"
#include <limits.h>
#include <stdlib.h>

#define TAILLE_MAX 80

int main(int argc, char *argv[])
{
    int dmin;
    ATR dico;
    Liste a_corriger;
    Liste tmp;
    Liste correction;
    FILE *texte_propre;
    char mot_corriger[TAILLE_MAX];
    char *nom_file;
    nom_file = "texte_propre";
    dico = NULL;
    a_corriger = NULL;
    correction = NULL;
    texte_propre = NULL;
    file_to_ATR(argv[2], &dico);
    texte_propre = nouveau(argv[1], nom_file);
    texte_propre = fopen(nom_file, "r");

    /* MAIN TROUVER MOTS MAL ORTHOGRAPHIES */
    if (texte_propre != NULL)
    {
        while (fscanf(texte_propre, "%s", mot_corriger) != EOF)
        {
            if (recherche_ATR(dico, mot_corriger) == 0)
            {
                inserer_en_tete(&a_corriger, mot_corriger);
            }
        }
    }

    fclose(texte_propre);

    /* MAIN CORRECTION ORTHOGRAPHIQUE */

    tmp = a_corriger;
    while (tmp != NULL)
    {
        dmin = INT_MAX;
        printf("Mot(s) mal orthographié : %s \n", tmp->mot);
        applique_lev(dico, tmp->mot, &correction, &dmin);
        printf("Proposition(s) : ");
        while (correction->suivant != NULL)
        {
            printf("%s, ", correction->mot);
            correction = correction->suivant;
        }
        printf("%s\n", correction->mot);
        tmp = tmp->suivant;
    }
    liberer_ATR(&dico);
    liberer_Liste(&a_corriger);
    liberer_Liste(&correction);
    return 0;
}