#ifndef __LEV__
#define __LEV__

#include "ATR.h"

/**
 * @brief Calcule la distance de Levenshtein entre deux mots
 *
 * @param un Premier mot
 * @param deux Deuxième mot
 * @return int Distance entre deux mots
 */
int Levenshtein(char *un, char *deux);

/**
 * @brief Fonction qui applique la fonction de Levenshtein à une liste
 *
 * @param A Arbre qu'on doit parcourir
 * @param corriger mot qu'on souhaite corriger
 * @param correction Liste avec les propositions de correction
 * @param dmin Valeur de dmin au premier appel de la fonction INT_MAX
 */
void applique_lev(ATR A, char *corriger, Liste *correction, int *dmin);

#endif