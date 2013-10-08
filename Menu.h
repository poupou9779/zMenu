#ifndef MENU_H
#define MENU_H

#define MENU_SUCCESS 0x0000

#define NOMBRE_MAX 20
#define LONGUEUR 100

typedef int (*callback)(int , char *[]);

char *Menu_Erreur;

/**Buffer temporaire pour mettre le message d'erreur dans Menu_Erreur*/
char Menu_TMPerreur[128];

struct Menu_Fonction {
    callback ptr;
    char nom[LONGUEUR];
};

struct Menu {
    int nombre;
    struct Menu_Fonction fonctions[NOMBRE_MAX];
};

/**Modifie Menu_Erreur en "Fonction : <fonction>\n\tErreur : <erreur>\n"*/
void Menu_actuErreur(const char *fonction, const char *erreur);

/**Actuellement, ne fait rien. Pourrait servir aux éventuelles allocations dynamiques, ...*/
void Menu_initialiser(void);

/**Revoie un pointeur constant sur Menu_Erreur.
    Renvoie NULL si Menu_actuErreur a échoué*/
const char *Menu_GetErreur(void);

/**Renvoie un pointeur sur un menu alloué.
    Renvoie NULL si l'allocation a échoué*/
struct Menu *Menu_allouerMenu(void);

/**Ajoute la fonction "fonction" dans le menu "menu", et nomme cette fonction "nom".
    Renvoie MENU_SUCCESS si nom, fonction et menu ne sont pas NULL*/
int Menu_ajouterFonction(struct Menu *menu, callback fonction, char *nom);

/**Liste tous les éléments du menu passé en paramètre.
    Renvoie MENU_SUCCESS si menu n'est pas NULL*/
int Menu_afficherMenu(struct Menu *menu);

/**Libère la mémoire allouée pour le menu.
    Renvoie NULL*/
struct Menu *Menu_desallouerMenu(struct Menu *menu);

/**Appelle la fonction n° index dans menu. Envoie argc et argv en paramètres, et récupère le résultat dans ret.
    Renvoie MENU_SUCCESS en cas de réussite*/
int Menu_executerFonction(struct Menu *menu, int index, int argc, char *argv[], int *ret);

/**Libère Menu_Erreur*/
void Menu_Quitter(void);

#endif // MENU_H
