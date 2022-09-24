#ifndef __AUXILIAIRE__
#define __AUXILIAIRE__

/**
 * @brief vérifie si un caractère est un caractère spécial
 *
 * @param caractere caractère lu
 * @return int return 1 si caractère spécial, 0 sinon
 */
int est_special(char caractere);

/**
 * @brief Crée un nouveau fichier sans caractère spécial
 *
 * @param argument nom du premier fichier
 * @param nom nom du nouveau fichier
 * @return FILE* nouveau fichier crée
 */
FILE *nouveau(char *argument, char *nom);

#endif