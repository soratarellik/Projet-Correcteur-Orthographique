#ifndef __ATR__
#define __ATR__

typedef struct noeud
{
    char lettre;
    struct noeud *fils;
    struct noeud *fg;
    struct noeud *fd;
} Noeud, *ATR;

/**
 * @brief Crée un arbre ternaire vide
 *
 * @return ATR adresse de l'arbre
 */
ATR creer_ATR_vide();

/**
 * @brief Libere l'espace mémoire occupée par l'arbre
 *
 * @param A return NULL une fois l'arbre liberée
 */
void liberer_ATR(ATR *A);

/**
 * @brief Insere un mot dans l'arbre
 *
 * @param A Arbre ou on veut ajouter le mot
 * @param mot mot a ajouter
 * @return int 1 si ajout 0 sinon
 */
int inserer_dans_ATR(ATR *A, char *mot);

/**
 * @brief Supprime un mot dans l'arbre
 *
 * @param A Arbre ternaire ou on souhaite effacer un mot
 * @param mot mot a supprimer
 */
void supprimer_dans_ATR(ATR *A, char *mot);

/**
 * @brief Affiche l'arbre
 *
 * @param A Arbre a afficher
 */
void afficher_ATR(ATR A);

/**
 * @brief Cherche un mot dans l'arbre ternaire de  recherche
 *
 * @param A Arbre ou on souhaite chercher le mot
 * @param mot mot qu'on souhaite chercher
 * @return int 1 si le mot est trouvé 0 sinon
 */
int recherche_ATR(ATR A, char *mot);

/**
 * @brief Transforme un fichier en ATR
 *
 * @param argmuent nom du fichier
 * @param A nouvel arbre ternaire
 * @return int return 1 si tout le fichier a pu être ajouté
 */
int file_to_ATR(char *argmuent, ATR *A);

/**
 * @brief Calcule l'hauteur d'un arbre ternaire de recherche
 *
 * @param A Arbre Ternaire de recherche
 * @return int hauteur de l'arbre
 */
int hauteur_arbre(ATR A);

#endif
