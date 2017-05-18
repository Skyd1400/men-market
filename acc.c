//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include "lib/conio2.h"
#include "acc.h"
#include "Maket.h"
#include "page.h"
#include "menu.h"


Meni meni_akey[6] = {
        {"SUCCURSALES", MM_MENI_SIKISAL},
        {"PRODUITS", MM_MENI_PWODWI},
        {"CLIENT", MM_MENI_KLIYAN},
        {"VENTES", MM_MENI_VANT},
        {"RAPPORTS", MM_MENI_RAPO},
        {"Quitter le programme", MM_SORTIE}
};


int afficher_accueil() {
    ScreenClear();
    afficher_en_tete("BIENVENUE");
    return  afficher_menu(meni_akey, 6);
}

void creer_page_accueil(Paj* page){
    page->id = MM_AKEY;
    page->afiche = afficher_accueil;
}