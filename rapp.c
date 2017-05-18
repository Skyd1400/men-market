//
// Created by Hash Skyd on 4/5/2017.
//

#include <stddef.h>
#include <stdio.h>
#include "Maket.h"
#include "page.h"
#include "menu.h"
#include "rapp.h"
#include "data.h"
#include "util.h"

Meni meni_rapo[5] = {
        {"Liste des clients", MM_LIS_KLIYAN_PA_DEPATMAN},
        {"Resume des ventes", MM_LIS_VANT_AK_PWODWI},
        {"Liste des produits a commander", MM_LIS_KOMAND},
        {"Liste des succursales a approvisionner", MM_LIS_SIKISAL_POU_APPWOVIZYONE},
        {"Retour", MM_AKEY}
};


int liste_kliyan();

/*
 * Fonksyon sa afiche meni pou modil rapo a e responsab jesyon pou paj modil la
 */
int afiche_meni_rapo() {
    ScreenClear();
    afficher_en_tete("Rapports");
    int ret = afficher_menu(meni_rapo, 5);
    switch (ret){
        case MM_LIS_KLIYAN_PA_DEPATMAN:
            ret = liste_kliyan();
    }
    return ret;
}

int liste_kliyan() {
    ScreenClear();
    afficher_en_tete("Liste des clients");
    textcolor(WHITE);

    Lis lis[10]; //varyab sa ap kenbe lis pou chak depatman yo
    for (int j = 0; j < 10; j++) {
        inisyalize_lis(&lis[j], MM_LIS_KLIYAN);
    }
    Lis * lis_kliyan = jwenn_lis(MM_LIS_KLIYAN);
    Mayon * mayon = lis_kliyan->premye; //pran premye mayon an
    while (mayon != NULL) {
        // gen eleman pou nou trete
        Kliyan *kliyan = mayon->done;
        mete_nan_lis(&lis[kliyan->adres->depatman], kliyan); //ajoute li nan lis depatman pal
        mayon = mayon->apre; //
    }
    for (int i = 0; i < 10; i++) { // Pou chak lis
        Lis lis_i = lis[i];
        textcolor(LIGHTBLUE);
        printf("\n:: %s ::", jwenn_non_depatman(i));//Afiche depatman an
        textcolor(WHITE);
        Mayon * mayon_i = lis_i.premye; //pran premye mayon an
        while (mayon_i != NULL) {
            // gen eleman pou nou trete
            Kliyan *kliyan = mayon_i->done;
            printf("\n%6d %s %s", kliyan->id, kliyan->non, kliyan->telefon);
            mayon_i = mayon_i->apre; //
        }
        printf("\n"); // yon ti espas a la fin
    }
    printf("\nAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;
}

void kreye_paj_rapo(Paj * page) {
    page->id = MM_MENI_RAPO;
    page->afiche = afiche_meni_rapo;
}
