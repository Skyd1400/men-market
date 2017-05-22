//
//
//

#include <stdio.h>
#include <stdlib.h>
#include "lib/conio2.h"
#include "meni.h"

int chwa(int chwa_posib){
    char cchwa[2];
    cchwa[1] = 0;
    int ichwa;
    // saisie du numero
    do {
        cchwa[0] = getch();
        ichwa = atoi(cchwa)- 1;
    } while(ichwa < 0 || ichwa >= chwa_posib);

    cputs(cchwa);
    // attendez que l'utilisateur presse entree
    while (getch() != '\r'){}
    return ichwa;
}

int afiche_meni(Meni *meni, int chwa_posib) {
    int y = wherey() + 1;
    for (int i = 0; i < chwa_posib; i++) {
        char text[100];
        gotoxy(5, y + i);
        textcolor(WHITE);
        textbackground(BLACK);
        sprintf(text, "| %d - %s", i+1, meni[i].non);
        cputs(text);
        // Afficher l'invite de choix
    }
    gotoxy(5, wherey() + 2);    
    cputs("Entrez votre choix [...] : ");
    int i = 0;
    int entree_x = wherex();
    int entree_y = wherey();

    //affiche le pied de page
    gotoxy(1, wherey() + 2);
    textcolor(LIGHTRED);
    //cputs(bordure);
    textcolor(WHITE);
    gotoxy(entree_x, entree_y);
    int ret =  meni[chwa(chwa_posib)].paj_swivan;
    return ret;
}