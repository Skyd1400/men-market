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


int afficher_menu(Menu *menu, int choix_possibles);

#endif //CCINTERFACE_MENU_H
