#include <stdio.h>
#include <stdlib.h>
#include "ATR.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define TAILLE_MAX 80

ATR creer_ATR_vide()
{
    ATR Arbre;
    Arbre = (ATR)malloc(sizeof(Noeud));
    if (Arbre != NULL)
    {
        Arbre->fd = NULL;
        Arbre->fg = NULL;
        Arbre->fils = NULL;
        return Arbre;
    }
    return Arbre;
}

void liberer_ATR(ATR *A)
{
    if (*A == NULL)
        return;
    liberer_ATR(&((*A)->fg));
    liberer_ATR(&((*A)->fils));
    liberer_ATR(&((*A)->fd));
    free(*A);
    *A = NULL;
}

int recherche_ATR(ATR A, char *mot)
{
    if (A == NULL)
        return 0;
    if (*mot == A->lettre)
    {
        if (*mot == '\0')
        {
            return 1;
        }
        return recherche_ATR(A->fils, (mot + 1));
    }
    else if (A->lettre > *mot)
        return recherche_ATR(A->fg, mot);
    else
        return recherche_ATR(A->fd, mot);
}

int inserer_dans_ATR(ATR *A, char *mot)
{
    if (*A == NULL)
    {
        *A = creer_ATR_vide();
        (*A)->lettre = *mot;
        if (*mot != '\0')
            inserer_dans_ATR(&((*A)->fils), (mot + 1));
        return 1;
    }
    else if ((*A)->lettre == *mot && *mot != '\0')
    {

        inserer_dans_ATR(&((*A)->fils), (mot + 1));
    }
    else if ((*A)->lettre > *mot)
    {
        inserer_dans_ATR(&((*A)->fg), mot);
    }
    else if ((*A)->lettre < *mot)
    {
        inserer_dans_ATR(&((*A)->fd), mot);
    }
    return 0;
}

ATR extrait_max_ATR(ATR *A)
{
    ATR tmp = *A, precedent = tmp;
    ATR save;
    while (tmp->fd != NULL)
    {
        precedent = tmp;
        tmp = tmp->fd;
    }
    precedent->fd = NULL;
    save = tmp;
    while (tmp->fg != NULL)
    {
        tmp = tmp->fg;
    }
    tmp->fg = (*A)->fg;
    return save;
}

void supprimer_dans_ATR(ATR *A, char *mot)
{
    ATR save;
    if (*A == NULL)
    {
        return;
    }
    else if ((*A)->lettre == *mot)
    {
        supprimer_dans_ATR(&((*A)->fils), (mot + 1));
    }
    else if ((*A)->lettre < *mot)
    {
        supprimer_dans_ATR(&((*A)->fd), mot);
    }
    else if ((*A)->lettre > *mot)
    {
        supprimer_dans_ATR(&((*A)->fg), mot);
    }
    if ((*A)->lettre == *mot && (*A)->fg == NULL && (*A)->fd == NULL && (*A)->fils == NULL)
    {
        free(*A);
        *A = NULL;
    }
    else if ((*A)->lettre == *mot && (*A)->fg == NULL && (*A)->fd != NULL && (*A)->fils == NULL)
    {
        save = (*A)->fd;
        free(*A);
        *A = save;
    }
    else if ((*A)->lettre == *mot && (*A)->fg != NULL && (*A)->fd == NULL && (*A)->fils == NULL)
    {
        save = (*A)->fg;
        free(*A);
        *A = save;
    }
    else if ((*A)->lettre == *mot && (*A)->fg != NULL && (*A)->fd != NULL && (*A)->fils == NULL)
    {
        save = extrait_max_ATR(&(*A));
        free(*A);
        *A = save;
    }
    return;
}

int file_to_ATR(char *argument, ATR *A)
{
    FILE *f;
    char nvmot[TAILLE_MAX];
    f = NULL;
    f = fopen(argument, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%s", nvmot) != EOF)
        {
            inserer_dans_ATR(A, nvmot);
        }
    }
    fclose(f);
    return 1;
}

int hauteur_arbre(ATR A)
{
    int a, b, c;
    if (A == NULL)
    {
        return -1;
    }
    else
    {
        a = hauteur_arbre(A->fd);
        b = hauteur_arbre(A->fg);
        c = hauteur_arbre(A->fils);
        return MAX(MAX(a, b), MAX(b, c)) + 1;
    }
}

void afficher_auxiliaire(ATR A, char *mot, int hauteur)
{
    if (A == NULL)
    {
        return;
    }
    afficher_auxiliaire(A->fg, mot, hauteur);
    mot[hauteur] = A->lettre;
    if (A->lettre == '\0')
    {
        printf("%s\n", mot);
    }
    afficher_auxiliaire(A->fils, mot, hauteur + 1);
    afficher_auxiliaire(A->fd, mot, hauteur);
}

void afficher_ATR(ATR A)
{
    int hauteur;
    char *mot;
    if (A == NULL)
    {
        return;
    }
    hauteur = hauteur_arbre(A);
    mot = (char *)malloc(hauteur * sizeof(char));
    if (mot == NULL)
    {
        return;
    }
    else
    {
        afficher_auxiliaire(A, mot, 0);
    }
}
