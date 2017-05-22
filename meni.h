//
//
//

#ifndef CCINTERFACE_MENU_H
#define CCINTERFACE_MENU_H

#include "page.h"

typedef struct {
    char *non;
    int paj_swivan;
} Meni;


int afiche_meni(Meni *meni, int chwa_posib);

#endif //CCINTERFACE_MENU_H
