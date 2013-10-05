#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Menu.h"

extern struct Menu_Erreur menu_erreur;

void Menu_initialiser(void) {
    menu_erreur.erreur = 0;
    menu_erreur.fonction = 0;
    menu_erreur.nom[0] = '\0';
}

void Menu_GetErreur(FILE *f, int ligne, char *fichier) {
    fprintf(f,  "Fichier : %s\n"
                "Ligne : %d\n",
                fichier, ligne);
    if(menu_erreur.fonction == MENU_AJOUTER_FONCTION) {
        fprintf(f,  "Fonction : API_AjouterFonction\n");
        if(menu_erreur.erreur == MENU_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Un pointeur nul a ete passe en parametre : %s\n", menu_erreur.nom);
        else if(menu_erreur.erreur == MENU_OVERFLOW_CALLBACK)
            fprintf(f,  "\tErreur : Tentative d'ajout d'une fonction alors qu'un menu ne peut en contenir que %d\n", NOMBRE_MAX);

    } else if(menu_erreur.fonction == MENU_EXECUTER) {
        fprintf(f,  "Fonction : API_executerFonction\n");
        if(menu_erreur.erreur == MENU_OVERFLOW_CALLBACK)
            fprintf(f,  "\tErreur : tentative d'acces a la fonction numero %s\n", menu_erreur.nom);
        else if(menu_erreur.erreur == MENU_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Le menu passe en parametre est un pointeur nul.\n");

    } else if(menu_erreur.fonction == MENU_AFFICHER) {
        fprintf(f,  "Fonction : API_afficherMenu\n");
        if(menu_erreur.erreur == MENU_NULL_POINTER_PARAMETER)
            fprintf(f,  "\tErreur : Le menu passe en parametre est un pointeur nul.\n");
    }
}

struct Menu *Menu_allouerMenu(void) {
    struct Menu *ret = malloc(sizeof *ret);
    if(ret != NULL)
        ret->nombre = 0;
    return ret;
}

int Menu_ajouterFonction(struct Menu *menu, callback fonction, char *nom) {
    if(menu == NULL || fonction == NULL || nom == NULL) {
        menu_erreur.fonction = MENU_AJOUTER_FONCTION;
        strcpy(menu_erreur.nom, menu == NULL ? "menu" : fonction == NULL ? "fonction" : "nom");
        menu_erreur.erreur = MENU_NULL_POINTER_PARAMETER;
        return !MENU_SUCCESS;
    }
    if(menu->nombre == NOMBRE_MAX) {
        menu_erreur.fonction = MENU_AJOUTER_FONCTION;
        strcpy(menu_erreur.nom, nom);
        menu_erreur.erreur = MENU_OVERFLOW_CALLBACK;
    }
    strcpy(menu->fonctions[menu->nombre].nom, nom);
    menu->fonctions[menu->nombre].ptr = fonction;
    ++menu->nombre;
    return MENU_SUCCESS;
}

int Menu_afficherMenu(struct Menu *menu) {
    int i = 0;
    if(menu == NULL) {
        menu_erreur.fonction = MENU_AFFICHER;
        menu_erreur.erreur = MENU_NULL_POINTER_PARAMETER;
        return !MENU_SUCCESS;
    }
    for(; i < menu->nombre; ++i)
        printf("%d. %s\n", i, menu->fonctions[i].nom);
    putchar('\n');
    return MENU_SUCCESS;
}

struct Menu *Menu_desallouerMenu(struct Menu *menu) {
    menu->nombre = 0;
    free(menu);
    menu = NULL;
    return menu;
};

int Menu_executerFonction(struct Menu *menu, int index) {
    if(menu == NULL) {
        menu_erreur.fonction = MENU_EXECUTER;
        menu_erreur.erreur = MENU_NULL_POINTER_PARAMETER;
        return !MENU_SUCCESS;
    }
    if(index > menu->nombre) {
        menu_erreur.fonction = MENU_EXECUTER;
        menu_erreur.erreur = MENU_OVERFLOW_CALLBACK;
        sprintf(menu_erreur.nom, "%d / %d", index, menu->nombre);
        return !MENU_SUCCESS;
    }
    menu->fonctions[index].ptr();
    return MENU_SUCCESS;
}

void Menu_Quitter(void) {
    ;
}

