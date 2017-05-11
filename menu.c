//
//
//

#include <stdio.h>
#include <stdlib.h>
#include "lib/conio2.h"
#include "menu.h"

int choix(int choix_possibles);

int afficher_menu(Meni *menu, int choix_possibles) {
    int y = wherey() + 1;
    for (int i = 0; i < choix_possibles; i++) {
        char text[100];
        gotoxy(5, y + i);
        textcolor(WHITE);
        textbackground(BLACK);
        sprintf(text, "| %d - %s", i+1, menu[i].nom);
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
    int ret =  menu[choix(choix_possibles)].page_suivante;
    return ret;
}

int choix(int choix_possibles){
    char cchoix[2];
    cchoix[1] = 0;
    int ichoix;
    // saisie du numero
    do {
        cchoix[0] = getch();
        ichoix = atoi(cchoix)- 1;
    } while(ichoix < 0 || ichoix >= choix_possibles);

    cputs(cchoix);
    // attendez que l'utilisateur presse entree
    while (getch() != '\r'){}
    return ichoix;
}