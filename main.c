#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "fonctions.h"

int main(int argc, char *argv[]) {
    int n = 0, ret;
    struct Menu *menu;
    Menu_initialiser();
    atexit(Menu_Quitter);
    menu = Menu_allouerMenu();
    if(menu != NULL) {
        if(Menu_ajouterFonction(menu, riri, "riri") != MENU_SUCCESS)
            printf("Ajouter riri : %s\n", Menu_GetErreur());
        if(Menu_ajouterFonction(menu, fifi, "fifi") != MENU_SUCCESS)
            printf("Ajouter fifi : %s\n", Menu_GetErreur());
        if(Menu_ajouterFonction(menu, loulou, "loulou") != MENU_SUCCESS)
            printf("Ajouter loulou : %s\n", Menu_GetErreur());
        if(Menu_afficherMenu(menu) != MENU_SUCCESS)
            printf("Afficher menu : %s\n", Menu_GetErreur());
        scanf("%d", &n);
        if(Menu_executerFonction(menu, n, argc, argv, &ret) != MENU_SUCCESS)
            printf("Executer fonction : %s\n", Menu_GetErreur());
        else
            printf("retourne : %d", ret);
        menu = Menu_desallouerMenu(menu);
    }
    return 0;
}
