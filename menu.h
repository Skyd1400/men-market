//
//
//

#ifndef CCINTERFACE_MENU_H
#define CCINTERFACE_MENU_H

#include "page.h"

typedef struct {
    char *nom;
    int page_suivante;
} Menu;

typedef struct {
    char *titre;
    Menu *Menus;
    int nombre_menu;
} EcranMenu;


int afficher_menu(Menu *menu, int choix_possibles);

#endif //CCINTERFACE_MENU_H
