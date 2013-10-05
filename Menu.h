#ifndef MENU_H
#define MENU_H

#define Menu_erreur(a) Menu_GetErreur(a, __LINE__, __FILE__)

#define MENU_SUCCESS                 0x0000
#define MENU_NULL_POINTER_PARAMETER -0x0001
#define MENU_OVERFLOW_CALLBACK      -0x0002

#define NOMBRE_MAX 20
#define LONGUEUR 100

enum {MENU_AJOUTER_FONCTION, MENU_EXECUTER, MENU_AFFICHER};

typedef void (*callback)(void);

struct Menu_Erreur {
    int erreur;
    int fonction;
    //si fonction == API_AJOUTER_FONCTION
    char nom[LONGUEUR];
};
struct Menu_Erreur menu_erreur;

struct Menu_Fonction {
    callback ptr;
    char nom[LONGUEUR];
};

struct Menu {
    unsigned int nombre;
    struct Menu_Fonction fonctions[NOMBRE_MAX];
};

void            Menu_initialiser(void);
void            Menu_GetErreur(FILE *, int, char *);
struct Menu *   Menu_allouerMenu(void);
int             Menu_ajouterFonction(struct Menu *, callback, char *);
int             Menu_afficherMenu(struct Menu *);
struct Menu *   Menu_desallouerMenu(struct Menu *);
int             Menu_executerFonction(struct Menu *, int);
void            Menu_Quitter(void);

#endif // MENU_H
