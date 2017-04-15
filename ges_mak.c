//
// Created by Hash Skyd on 4/5/2017.
//

#include "ges_mak.h"
#include "lib/conio2.h"
#include "Maket.h"
#include "acc.h"
#include "test.h"
#include "data.h"


#define MAX_PAGES 2

Page pages[MAX_PAGES];
int page_courant;
int prochaine_page;
int derniere_page;
int nombre_de_pages;

int main(){
    // test

    // fin test

    int fini = 0;
    inittextinfo();
    charger_donnees(MM_LIS_KLIYAN);
    creer_page_accueil(&pages[0]);
    creer_page_test(&pages[1]);
    page_courant = 0;
    nombre_de_pages = MAX_PAGES;

    while (!fini) {
        prochaine_page = pages[page_courant].afficher();
        if (prochaine_page != page_courant) {
            for (int i = 0; i < nombre_de_pages; i++){
                if (prochaine_page == MM_SORTIE) {
                    fini = 1;
                } else if (pages[i].id() == prochaine_page) {
                    derniere_page = page_courant;
                    page_courant = i;
                    break;
                }
            }
        }
    }

    return 0;
}