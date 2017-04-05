//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include "lib/conio2.h"
#include "acc.h"
#include "Maket.h"


char *bordure = "=====================================================================\n";
char *bordure_fine = "---------------------------------------------------------------------\n";

char *app_name = "       __   __ _____ _   _      __   __  ___  _   _______ _____\n      |  \\ /  |  ___) \\ | |    |  \\ /  |/ _ \\| | / /  ___|_   _)\n      |   v   | |_  |  \\| |    |   v   | |_| | |/ /| |_    | |\n      | |\\_/| |  _) |     | == | |\\_/| |  _  |   < |  _)   | |\n      | |   | | |___| |\\  |    | |   | | | | | |\\ \\| |___  | |\n      |_|   |_|_____)_| \\_|    |_|   |_|_| |_|_| \\_\\_____) |_|\n";

void afficher_en_tete(char *titre) {
    ScreenClear();
    char text[100];
    textcolor(LIGHTRED);
    cputs(bordure);
    cputs(app_name);
    cputs("\n");
    cputs(bordure);

    gotoxy(26, 11);
    textcolor(YELLOW);
    sprintf(text, ":: %s ::", titre);
    cputs(text);
    gotoxy(1, 13);
    textcolor(RED);
    cputs(bordure_fine);
}


int id_accueil() {
    return MM_ACCUEIL;
}


int afficher_accueil() {
    ScreenClear();
    afficher_en_tete("BIENVENUE");

    gotoxy(1, 18);
    textcolor(LIGHTRED);
    cputs(bordure);
    getch();
    return MM_ACCUEIL;
}

void creer_page_accueil(Page* page){
    page->id = id_accueil;
    page->afficher = afficher_accueil;
}