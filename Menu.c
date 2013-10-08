#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Menu.h"

void Menu_initialiser(void) {
    ;
}

const char *Menu_GetErreur() {
    return Menu_Erreur;
}

struct Menu *Menu_allouerMenu(void) {
    struct Menu *ret = malloc(sizeof *ret);
    if(ret != NULL)
        ret->nombre = 0;
    return ret;
}

int Menu_ajouterFonction(struct Menu *menu, callback fonction, char *nom) {
    if(menu == NULL || fonction == NULL || nom == NULL) {
        sprintf(Menu_TMPerreur, "Parametre \"%s\" nul", menu == NULL ? "menu" : fonction == NULL ? "fonction" : "nom");
        Menu_actuErreur("Menu_ajouterFonction", Menu_TMPerreur);
        return !MENU_SUCCESS;
    }
    if(menu->nombre == NOMBRE_MAX) {
        Menu_actuErreur("Menu_ajouterFonction", "Menu plein. Plus possible d'ajouter des fonctions");
        return !MENU_SUCCESS;
    }
    strcpy(menu->fonctions[menu->nombre].nom, nom);
    menu->fonctions[menu->nombre].ptr = fonction;
    ++menu->nombre;
    return MENU_SUCCESS;
}

int Menu_afficherMenu(struct Menu *menu) {
    int i = 0;
    if(menu == NULL) {
        Menu_actuErreur("Menu_afficherMenu", "Parametre \"menu\" nul");
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

int Menu_executerFonction(struct Menu *menu, int index, int argv, char *argc[], int *ret) {
    if(menu == NULL) {
        Menu_actuErreur("Menu_executerFonction", "Parametre \"menu\" nul");
        return !MENU_SUCCESS;
    } else if(ret == NULL) {
        Menu_actuErreur("Menu_executerFonction", "Parametre \"ret\" nul");
        return !MENU_SUCCESS;
    }
    if(index > menu->nombre-1) {
        sprintf(Menu_TMPerreur, "tentative d'acces a la focntion %d / %d", index, menu->nombre-1);
        Menu_actuErreur("Menu_executerFonction", Menu_TMPerreur);
        return !MENU_SUCCESS;
    }
    *ret = menu->fonctions[index].ptr(argv, argc);
    return MENU_SUCCESS;
}

void Menu_Quitter(void) {
    free(Menu_Erreur);
}

void Menu_actuErreur(const char *fonction, const char *erreur) {
    sprintf(Menu_TMPerreur, "Fonction : %s\n\tErreur : %s\n", fonction, erreur);
    free(Menu_Erreur);
    Menu_Erreur = malloc(strlen(Menu_TMPerreur)+1);
    if(Menu_Erreur != NULL)
        strcpy(Menu_Erreur, Menu_TMPerreur);
}

