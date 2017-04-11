//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include "lib/conio2.h"
#include "acc.h"
#include "Maket.h"
#include "page.h"


int id_accueil() {
    return MM_ACCUEIL;
}


int afficher_accueil() {
    ScreenClear();
    afficher_en_tete("BIENVENUE");

    gotoxy(1, 18);
    getch();
    return MM_TEST_DONNEES;
}

void creer_page_accueil(Page* page){
    page->id = id_accueil;
    page->afficher = afficher_accueil;
}