#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "BK.h"
#include "Liste.h"
#include "Levenshtein.h"

#define TAILLE_MAX 80

ArbreBK alloue_nv_BK(char *mot, int val)
{
    ArbreBK nv_noeud = (ArbreBK)malloc(sizeof(NoeudBK));
    if (nv_noeud)
    {
        nv_noeud->mot = (char *)malloc(sizeof(char) * TAILLE_MAX);
        strcpy(nv_noeud->mot, mot);
        nv_noeud->valeur = val;
        nv_noeud->filsG = nv_noeud->frereD = NULL;
    }
    return nv_noeud;
}

int inserer_dans_ArbreBK(ArbreBK *A, char *mot)
{
    ArbreBK nv_noeud, tmp, prec;
    if ((*A) == NULL)
    {
        (*A) = alloue_nv_BK(mot, 0);
        return 1;
    }
    else if (strcmp((*A)->mot, mot) == 0)
        return 0;
    else if ((*A)->filsG == NULL)
    {
        nv_noeud = alloue_nv_BK(mot, Levenshtein(mot, (*A)->mot));
        (*A)->filsG = nv_noeud;
        return 1;
    }
    else
    {
        /* parcourt des filsG du noeud ou l'on veut inserer le mot */
        tmp = prec = (*A)->filsG;
        while (tmp)
        {
            /* si le mot est deja present dans l'arbre */
            if (strcmp(tmp->mot, mot) == 0)
                return 0;
            /* si la distance de levenshtein est la meme on appelle recursivement la fonction sur ce noeud */
            else if (tmp->valeur == Levenshtein(mot, (*A)->mot))
                return inserer_dans_ArbreBK(&(tmp), mot);
            else if (tmp->valeur > Levenshtein(mot, (*A)->mot))
            {
                nv_noeud = alloue_nv_BK(mot, Levenshtein(mot, (*A)->mot));
                /* si tmp est le 1er filsG */
                if (tmp == (*A)->filsG)
                {
                    nv_noeud->frereD = (*A)->filsG;
                    (*A)->filsG = nv_noeud;
                    return 1;
                }
                nv_noeud->frereD = tmp;
                prec->frereD = nv_noeud;
                return 1;
            }
            prec = tmp;
            tmp = tmp->frereD;
        }
        /* insere Ã  la fin des frereD */
        nv_noeud = alloue_nv_BK(mot, Levenshtein(mot, (*A)->mot));
        prec->frereD = nv_noeud;
        return 1;
    }
    return 0;
}

ArbreBK creer_ArbreBK(FILE *dico)
{
    ArbreBK a = NULL;
    char mot[TAILLE_MAX];
    while (fscanf(dico, "%s", mot) != EOF)
    {
        inserer_dans_ArbreBK(&a, mot);
    }
    return a;
}

void liberer_ArbreBK(ArbreBK *A)
{
    if (*A == NULL)
        return;
    liberer_ArbreBK(&((*A)->filsG));
    liberer_ArbreBK(&((*A)->frereD));
    free(*A);
    *A = NULL;
}

void ecrireDebut(FILE *f)
{
    fprintf(f, "digraph arbre {\n\tnode [ shape = record , height = .1 ]\n\tedge [ tailclip = false , arrowtail = dot , dir = both ];\n");
}

void ecrireArbre(FILE *f, ArbreBK a)
{
    if (a == NULL)
        return;
    fprintf(f, "\tn%p [label=\"<gauche> | <valeur> %s | <valeur> %d | <droit>\"];\n", (void *)a, a->mot, a->valeur);
    if (a->filsG != NULL)
    {
        fprintf(f, "\tn%p: gauche : c -> n%p: valeur ;\n", (void *)a, (void *)a->filsG);
        ecrireArbre(f, a->filsG);
    }
    if (a->frereD != NULL)
    {
        fprintf(f, "\tn%p: droit : c -> n%p: valeur ;\n", (void *)a, (void *)a->frereD);
        ecrireArbre(f, a->frereD);
    }
}

void ecrireFin(FILE *f)
{
    fprintf(f, "}\n");
}

void afficher_ArbreBK(ArbreBK a)
{
    FILE *out;
    out = fopen("arbre.dot", "w");
    ecrireDebut(out);
    ecrireArbre(out, a);
    ecrireFin(out);
}

void rechercher(ArbreBK A, char *m, Liste *corrections, int *seuil)
{
    int d;
    if (A == NULL)
    {
        return;
    }
    d = Levenshtein(A->mot, m);
    if (d == *seuil)
    {
        inserer_en_tete(corrections, A->mot);
    }
    else if (d < *seuil)
    {
        liberer_Liste(corrections);
        inserer_en_tete(corrections, A->mot);
        *seuil = d;
    }
    rechercher(A->filsG, m, corrections, seuil);
    rechercher(A->frereD, m, corrections, seuil);
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char *m)
{
    Liste l;
    int limit;
    l = NULL;
    limit = INT_MAX;
    rechercher(A, m, &l, &limit);
    return l;
}

int recherche_exacte_aux(ArbreBK A, char *mot, int seuil)
{
    if (A == NULL)
    {
        return 0;
    }
    if (A->valeur == seuil)
    {
        if (Levenshtein(A->mot, mot) == 0)
        {
            return 1;
        }
        else
        {
            seuil = Levenshtein(A->mot, mot);
            return recherche_exacte_aux(A->filsG, mot, seuil);
        }
    }
    else if (A->valeur > seuil)
    {
        return 0;
    }
    else
    {
        return recherche_exacte_aux(A->frereD, mot, seuil);
    }
    return 0;
}

int recherche_exacte(ArbreBK A, char *mot)
{
    int dist;
    if (A == NULL)
    {
        return 0;
    }
    dist = Levenshtein(A->mot, mot);
    if (dist == 0)
    {
        return 1;
    }
    if (A->valeur == 0 && A->filsG == NULL) /*Cas ou la racine est l'unique mot et n'est pas le mot recherché*/
    {
        return 0;
    }
    return recherche_exacte_aux(A->filsG, mot, dist);
}
