//
// Created by Hash Skyd on 4/11/2017.
//

#include <stdlib.h>
#include <stdio.h>
#include "lib/conio2.h"
#include "Maket.h"
#include "test.h"
#include "data.h"
#include "page.h"


int afficher_test() {
    ScreenClear();
    afficher_en_tete("TEST DES DONNEES");
    textcolor(WHITE);
    Lis *liste = jwenn_lis(MM_LIS_KLIYAN);
    Mayon *mayon = liste->premye;
    do {
        Kliyan *temp = mayon->done;
        if (temp != NULL) {
            printf("\n\tId du client : %d", temp->id);
            printf("\n\tNom du client : %s", temp->non);
            printf("\n\tType : %s", temp->tip == ENTREPRISE ? "Entreprise" : "Particulier");
            printf("\n\tAdress : ");
            printf("\n\t\tNo : %d", temp->adres->no);
            printf("\n\t\tRue : %s", temp->adres->ri);
            printf("\n\t\tVille : %s", temp->adres->vil);
            printf("\n\t\tDepartement : %s", temp->adres->depatman);
            printf("\n\tTelephone : %s", temp->telefon);
            printf("\n=====================================================");
        }
        mayon = mayon->apre;
    } while (mayon != NULL);
    printf("\n\n=====================================================");
    printf("\nFichye succursales.dat\n\n");
    liste = jwenn_lis(MM_LIS_SIKISAL);
    mayon = liste->premye;
    do {
        Sikisal *temp = mayon->done;
        if (temp != NULL) {
            printf("\n\tId du succursales : %d", temp->id);
            printf("\n\tDescription : %s", temp->deskripsyon);
            printf("\n\tAdress : ");
            printf("\n\t\tNo : %d", temp->adres->no);
            printf("\n\t\tRue : %s", temp->adres->ri);
            printf("\n\t\tVille : %s", temp->adres->vil);
            printf("\n\t\tDepartement : %s", temp->adres->depatman);
            printf("\n\tResponsable : %s", temp->responsab);
            printf("\n\tTelephone : %s", temp->telefon);
            printf("\n=====================================================");
        }
        mayon = mayon->apre;
    } while (mayon != NULL);
    getch();
    return MM_AKEY;
}

void creer_page_test(Paj *page) {
    page->id = MM_TEST_DONNEES;
    page->afiche = afficher_test;
}
