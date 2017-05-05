//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include "lib/conio2.h"
#include "acc.h"
#include "Maket.h"
#include "page.h"



int afficher_accueil() {
    ScreenClear();
    afficher_en_tete("BIENVENUE");

    gotoxy(1, 18);
    getch();
    return MM_TEST_DONNEES;
}

void creer_page_accueil(Page* page){
    page->id = MM_ACCUEIL;
    page->afficher = afficher_accueil;
}