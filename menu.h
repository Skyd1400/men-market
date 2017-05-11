//
//
//

#ifndef CCINTERFACE_MENU_H
#define CCINTERFACE_MENU_H

#include "page.h"

typedef struct {
    char *nom;
    int page_suivante;
} Meni;


int afficher_menu(Meni *menu, int choix_possibles);

#endif //CCINTERFACE_MENU_H
