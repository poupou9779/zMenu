#include <stdio.h>
#include "API.h"
#include "fonctions.h"

int main(void) {
    int n = 0;
    struct Menu *menu;
    API_initialiser();
    menu = API_allouerMenu();
    if(menu != NULL) {
        if(API_ajouterFonction(menu, riri, "riri") != API_SUCCESS)
            API_Erreur(stdout);
        if(API_ajouterFonction(menu, fifi, "fifi") != API_SUCCESS)
            API_Erreur(stdout);
        if(API_ajouterFonction(menu, loulou, "loulou") != API_SUCCESS)
            API_Erreur(stdout);
        if(API_afficherMenu(menu) != API_SUCCESS)
            API_Erreur(stdout);
        scanf("%d", &n);
        if(API_executerFonction(menu, n) != API_SUCCESS)
            API_Erreur(stdout);
        menu = API_desallouerMenu(menu);
    }
    API_Quitter();
    return 0;
}


