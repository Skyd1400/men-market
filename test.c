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
    Liste *liste = trouver_liste(MM_LISTE_CLIENTS);
    Noeud *noeud = liste->premier;
    do
    {
        Client *temp = noeud->data;
        if (temp != NULL)
            printf("\nId du client : %d", ((Client *) noeud->data)->id);
        noeud = noeud->suivant;
    } while (noeud != NULL);
    getch();
    return MM_ACCUEIL;
}

void creer_page_test(Page *page)
{
    page->id = id_test;
    page->afficher = afficher_test;
}
