#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "API.h"

extern struct Erreur API_Erreur_variable;

void API_initialiser(void) {
    API_Erreur_variable.erreur = 0;
    API_Erreur_variable.fonction = 0;
    API_Erreur_variable.nom[0] = '\0';
}

void _API_Erreur(FILE *f, int ligne, char *fichier) {
    fprintf(f,  "Fichier : %s\n"
                "Ligne : %d\n",
                fichier, ligne);
    if(API_Erreur_variable.fonction == API_AJOUTER_FONCTION) {
        fprintf(f,  "Fonction : API_AjouterFonction\n");
        if(API_Erreur_variable.erreur == API_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Un pointeur nul a ete passe en parametre : %s\n", API_Erreur_variable.nom);
        else if(API_Erreur_variable.erreur == API_OVERFLOW_CALLBACK)
            fprintf(f,  "\tErreur : Tentative d'ajout d'une fonction alors qu'un menu ne peut en contenir que %d\n", NOMBRE_MAX);

    } else if(API_Erreur_variable.fonction == API_EXECUTER) {
        fprintf(f,  "Fonction : API_executerFonction\n");
        if(API_Erreur_variable.erreur == API_OVERFLOW_CALLBACK)
            fprintf(f,  "\tErreur : tentative d'acces a la fonction numero %s\n", API_Erreur_variable.nom);
        else if(API_Erreur_variable.erreur == API_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Le menu passe en parametre est un pointeur nul.\n");

    } else if(API_Erreur_variable.fonction == API_AFFICHER) {
        fprintf(f,  "Fonction : API_afficherMenu\n");
        if(API_Erreur_variable.erreur == API_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Le menu passe en parametre est un pointeur nul.\n");
    }
}

struct Menu *API_allouerMenu(void) {
    struct Menu *ret = malloc(sizeof *ret);
    if(ret != NULL)
        ret->nombre = 0;
    return ret;
}

int API_ajouterFonction(struct Menu *menu, callback fonction, char *nom) {
    if(menu == NULL || fonction == NULL || nom == NULL) {
        API_Erreur_variable.fonction = API_AJOUTER_FONCTION;
        strcpy(API_Erreur_variable.nom, menu == NULL ? "menu" : fonction == NULL ? "fonction" : "nom");
        API_Erreur_variable.erreur = API_NULL_POINTER_PARAMETER;
        return !API_SUCCESS;
    }
    if(menu->nombre == NOMBRE_MAX) {
        API_Erreur_variable.fonction = API_AJOUTER_FONCTION;
        strcpy(API_Erreur_variable.nom, nom);
        API_Erreur_variable.erreur = API_OVERFLOW_CALLBACK;
    }
    strcpy(menu->fonctions[menu->nombre].nom, nom);
    menu->fonctions[menu->nombre].ptr = fonction;
    ++menu->nombre;
    return API_SUCCESS;
}

int API_afficherMenu(struct Menu *menu) {
    int i = 0;
    if(menu == NULL) {
        API_Erreur_variable.fonction = API_AFFICHER;
        API_Erreur_variable.erreur = API_NULL_POINTER_PARAMETER;
        return !API_SUCCESS;
    }
    for(; i < menu->nombre; ++i)
        printf("%d. %s\n", i, menu->fonctions[i].nom);
    putchar('\n');
    return API_SUCCESS;
}

struct Menu *API_desallouerMenu(struct Menu *menu) {
    menu->nombre = 0;
    free(menu);
    menu = NULL;
    return menu;
};

int API_executerFonction(struct Menu *menu, int index) {
    if(menu == NULL) {
        API_Erreur_variable.fonction = API_EXECUTER;
        API_Erreur_variable.erreur = API_NULL_POINTER_PARAMETER;
        return !API_SUCCESS;
    }
    if(index > menu->nombre) {
        API_Erreur_variable.fonction = API_EXECUTER;
        API_Erreur_variable.erreur = API_OVERFLOW_CALLBACK;
        sprintf(API_Erreur_variable.nom, "%d / %d", index, menu->nombre);
        return !API_SUCCESS;
    }
    menu->fonctions[index].ptr();
    return API_SUCCESS;
}

void API_Quitter(void) {
    ;
}

