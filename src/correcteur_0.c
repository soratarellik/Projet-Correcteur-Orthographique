#include <stdio.h>
#include "Liste.h"
#include "ATR.h"
#include "Auxiliaire.h"

#define TAILLE_MAX 80

int main(int argc, char *argv[])
{

	ATR dico;
	Liste a_corriger;
	FILE *texte_propre;
	char mot_corriger[TAILLE_MAX];
	char *nom_file;

	nom_file = "texte_propre";
	dico = NULL;
	a_corriger = NULL;
	texte_propre = NULL;
	file_to_ATR(argv[2], &dico);
	texte_propre = nouveau(argv[1], nom_file);
	texte_propre = fopen(nom_file, "r");

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
	printf("Mot(s) mal orthographié(s) :\n");
	afficher_Liste(a_corriger);
	liberer_ATR(&dico);
	liberer_Liste(&a_corriger);
	return 0;
}