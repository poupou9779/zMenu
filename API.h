#ifndef API_H
#define API_H

#define API_Erreur(a) _API_Erreur(a, __LINE__, __FILE__)

#define API_SUCCESS                  0x0000
#define API_NULL_POINTER_PARAMETER  -0x0001
#define API_OVERFLOW_CALLBACK       -0x0002

#define NOMBRE_MAX 20
#define LONGUEUR 100

enum {API_AJOUTER_FONCTION, API_EXECUTER, API_AFFICHER};

typedef void (*callback)(void);

struct Erreur {
    int erreur;
    int fonction;
    //si fonction == API_AJOUTER_FONCTION
    char nom[LONGUEUR];
};
struct Erreur API_Erreur_variable;

struct Fonction {
    callback ptr;
    char nom[LONGUEUR];
};

struct Menu {
    unsigned int nombre;
    struct Fonction fonctions[NOMBRE_MAX];
};

void            API_initialiser(void);
void        _API_Erreur(FILE *, int, char *);
struct Menu *   API_allouerMenu(void);
int             API_ajouterFonction(struct Menu *, callback, char *);
int             API_afficherMenu(struct Menu *);
struct Menu *   API_desallouerMenu(struct Menu *);
int             API_executerFonction(struct Menu *, int);
void            API_Quitter(void);

#endif // API_H
