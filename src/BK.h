#ifndef __BK__
#define __BK__

#include <stdio.h>
#include "Liste.h"

typedef struct noeudBK
{
    char *mot;
    int valeur;
    struct noeudBK *filsG;
    struct noeudBK *frereD;
} NoeudBK, *ArbreBK;

/**
 * @brief insere un mot dans l'arbre BK
 *
 * @param A adresse d'une adresse d'un arbre BK
 * @param mot chaine de caractere à ajouter
 * @return int 1 si l'insertion s'est bien passée 0 sinon
 */
int inserer_dans_ArbreBK(ArbreBK *A, char *mot);

/**
 * @brief fonction qui recherche les mots présents dans l'arbre Bk se rapprochant du mot mis en paramètre
 *
 * @param A adresse d'un arbre BK
 * @param mot chaine de caractere à rechercher
 * @return Liste retourne une liste chainée de mot à proposer pour la correction
 */
Liste rechercher_dans_ArbreBK(ArbreBK A, char *mot);

/**
 * @brief fonction qui crée un l'arbre BK à partir d'un dictionnaire donné
 *
 * @param dico fichier contenant le dictionnaire
 * @return ArbreBK retourne l'adresse d'un arbre BK contenant le dictionnaire
 */
ArbreBK creer_ArbreBK(FILE *dico);

/**
 * @brief fonction permettant de libérer la mémoire de l'arbre BK
 *
 * @param A adresse d'une adresse d'un arbre BK
 */
void liberer_ArbreBK(ArbreBK *A);

/**
 * @brief Fonction permettant de créer un .dot pour afficher l'arbre BK sous forme de pdf
 *
 * @param A adresse d'un arbre BK
 */
void afficher_ArbreBK(ArbreBK A);

/**
 * @brief fonction permettant de savoir si un mot est présent dans l'arbre BK
 *
 * @param A adresse d'un arbre BK
 * @param mot chaine de caractere à rechercher
 * @return int revoie 1 s'il est présent, 0 sinon
 */
int recherche_exacte(ArbreBK A, char *mot);

#endif