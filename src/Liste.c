#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste.h"

Cellule *allouer_Cellule(char *mot)
{
	Cellule *allocation = (Cellule *)malloc(sizeof(Cellule));
	if (allocation != NULL)
	{
		allocation->mot = (char *)malloc(sizeof(char) * strlen(mot));
		if (allocation->mot)
		{
			strcpy(allocation->mot, mot);
			allocation->suivant = NULL;
			return allocation;
		}
	}
	return allocation;
}

int inserer_en_tete(Liste *L, char *mot)
{
	Cellule *ajout;
	if (*L == NULL)
	{
		ajout = allouer_Cellule(mot);
		if (ajout != NULL)
		{
			*L = ajout;
			return 1;
		}
	}
	else if (*L != NULL)
	{
		ajout = allouer_Cellule(mot);
		if (ajout != NULL)
		{
			ajout->suivant = *L;
			*L = ajout;
			return 1;
		}
	}

	return 0;
}

void afficher_Liste(Liste L)
{
	for (; L; L = L->suivant)
		printf("%s\n", L->mot);
}

void liberer_Liste(Liste *L)
{
	Liste tmp;
	tmp = NULL;
	while (*L != NULL)
	{

		tmp = *L;
		*L = (*L)->suivant;
		free(tmp);
	}
	*L = NULL;
}
