#ifndef __LISTE__
#define __LISTE__

typedef struct cell
{
	char *mot;
	struct cell *suivant;
} Cellule, *Liste;

/**
 * @brief Alloue l'espace nécessaire pour une cellule
 *
 * @param mot Chaine de caractères
 * @return Cellule* Adresse de la cellule
 */
Cellule *allouer_Cellule(char *mot);

/**
 * @brief Insére un élément en tête de la liste chainée
 *
 * @param L Liste
 * @param mot mot
 * @return int 1 si l'ajout à pu se faire 0 sinon
 */
int inserer_en_tete(Liste *L, char *mot);

/**
 * @brief Fonction qui libére l'intégralité de la liste
 *
 * @param L Liste à libérer
 */
void liberer_Liste(Liste *L);

/**
 * @brief Fonction qui affiche une Liste chainée
 *
 * @param L
 */
void afficher_Liste(Liste L);

#endif