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

int id_test()
{
    return MM_TEST_DONNEES;
};

int afficher_test()
{
    ScreenClear();
    afficher_en_tete("TEST DES DONNEES");
    textcolor(WHITE);
    Lis *liste = trouver_liste(MM_LIS_KLIYAN);
    Mayon *noeud = liste->premye;
    do
    {
        Kliyan *temp = noeud->done;
        if (temp != NULL)
            printf("\n\tId du client : %d", temp->id);
            printf("\n\tNom du client : %s", temp->non);
            printf("\n\tType : %s", temp->tip == ENTREPRISE? "Entreprise" : "Particulier");
            printf("\n\tTelephone : %s", temp->telefon);
            printf("\n=====================================================");
        noeud = noeud->apre;
    } while (noeud != NULL);
    getch();
    return MM_ACCUEIL;
}

void creer_page_test(Page *page)
{
    page->id = id_test;
    page->afficher = afficher_test;
}
