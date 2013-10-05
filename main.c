#include <stdio.h>
#include "Menu.h"
#include "fonctions.h"

int main(void) {
    int n = 0;
    struct Menu *menu;
    Menu_initialiser();
    menu = Menu_allouerMenu();
    if(menu != NULL) {
        if(Menu_ajouterFonction(menu, riri, "riri") != MENU_SUCCESS)
            Menu_erreur(stdout);
        if(Menu_ajouterFonction(menu, fifi, "fifi") != MENU_SUCCESS)
            Menu_erreur(stdout);
        if(Menu_ajouterFonction(menu, loulou, "loulou") != MENU_SUCCESS)
            Menu_erreur(stdout);
        if(Menu_afficherMenu(menu) != MENU_SUCCESS)
            Menu_erreur(stdout);
        scanf("%d", &n);
        if(Menu_executerFonction(menu, n) != MENU_SUCCESS)
            Menu_erreur(stdout);
        menu = Menu_desallouerMenu(menu);
    }
    Menu_Quitter();
    return 0;
}


