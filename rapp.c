//
// Created by Hash Skyd on 4/5/2017.
//

#include <stddef.h>
#include <stdio.h>
#include "Maket.h"
#include "page.h"
#include "menu.h"
#include "done/strikti.h"
#include "util.h"

Meni meni_rapo[5] = {
        {"Liste des clients", MM_LIS_KLIYAN_PA_DEPATMAN},
        {"Resume des ventes", MM_LIS_VANT_AK_PWODWI},
        {"Liste des produits a commander", MM_LIS_KOMAND},
        {"Liste des succursales a approvisionner", MM_LIS_SIKISAL_POU_APPWOVIZYONE},
        {"Retour", MM_AKEY}
};



/*
 * Fonksyon sa afiche paj pou liste kliyan an
 */
int liste_kliyan() {
    ScreenClear();
    afficher_en_tete("Liste des clients");
    textcolor(WHITE);

    Lis lis[10]; //varyab sa ap kenbe lis pou chak depatman yo
    for (int j = 0; j < 10; j++) {
        inisyalize_lis(lis + j);
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
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;
}


int liste_vant() {
    ScreenClear();
    afficher_en_tete("Liste des ventes");
    textcolor(WHITE);

    Lis * lis_pwodwi = jwenn_lis(MM_LIS_PWODWI);
    Mayon * mayon_pwodwi = lis_pwodwi->premye;
    while (mayon_pwodwi != NULL) {
        Pwodwi * pwodwi = mayon_pwodwi->done;
        int montan_total = 0;
        int kantite_total = 0;

        printf("\t-------------------------------------------------------------");
        printf("\n\tProduit : %s", pwodwi->deskripsyon);
        printf("\n\t\tCode : %d", pwodwi->kod);
        printf("\n\t\tMontant par Succursale:");

        Lis * lis_sikisal = jwenn_lis(MM_LIS_SIKISAL);
        Mayon * mayon_sikisal = lis_sikisal->premye;
        while (mayon_sikisal != NULL) {
            //Pou chak sikisal
            Sikisal * sikisal = mayon_sikisal->done;
            int montan = 0;

            Lis * lis_vant = jwenn_lis(MM_LIS_VANT);
            Mayon * mayon_vant = lis_vant->premye;
            while (mayon_vant != NULL) {
                //Pou chak vant nan sikisal sa
                Vant * vant = mayon_vant->done;

                if (vant->sikisal == sikisal->id) {
                    Lis * lis_detay_vant = jwenn_lis(MM_LIS_DETAY_VANT);
                    Mayon * mayon_detay_vant = lis_detay_vant->premye;
                    while (mayon_detay_vant != NULL) {
                        //Pou chak vant nan sikisal sa
                        DetayVant * detayVant = mayon_detay_vant->done;

                        if (detayVant->vant == vant->id) {
                            montan += detayVant->kantite_atik * detayVant->pri_inite;
                            kantite_total += detayVant->kantite_atik;
                        }

                        mayon_detay_vant = mayon_detay_vant->apre;
                    }
                }

                mayon_vant = mayon_vant->apre;
            }

            printf("\n\t\t\t(%d) %s -> %d", sikisal->id, sikisal->deskripsyon, montan);

            montan_total += montan;
            mayon_sikisal = mayon_sikisal->apre;
        }

        printf("\n\t\tMontant total -> %d", montan_total);
        printf("\n\t\tQuantite totale vendue -> %d\n", kantite_total);
        mayon_pwodwi = mayon_pwodwi->apre; // pran lot ki swiv li a
    }

    printf("\n\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;
}

int liste_komand() {
    ScreenClear();
    afficher_en_tete("Liste des commandes");
    textcolor(WHITE);

    Lis * lis_pwodwi = jwenn_lis(MM_LIS_PWODWI);
    Mayon * mayon_pwodwi = lis_pwodwi->premye;
    while (mayon_pwodwi != NULL) {
        Pwodwi * pwodwi = mayon_pwodwi->done;
        int montan_total = 0;
        int kantite_total = 0;

        if (pwodwi->kantite < pwodwi->stok_sekirite) {

            printf("\t-------------------------------------------------------------");
            printf("\n\tProduit : %s", pwodwi->deskripsyon);
            printf("\n\t\tCode : %d", pwodwi->kod);
            printf("\n\t\tQuantite a commander: %d\n", pwodwi->stok_sekirite * 2 - pwodwi->kantite);
        }

        mayon_pwodwi = mayon_pwodwi->apre; // pran lot ki swiv li a
    }
    printf("\t-------------------------------------------------------------");

    printf("\n\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;
}

int liste_sikisal() {
    ScreenClear();
    afficher_en_tete("Succursales a approvisionner");
    textcolor(WHITE);

    Lis * lis_sikisal = jwenn_lis(MM_LIS_SIKISAL);
    Mayon * mayon_sikisal = lis_sikisal->premye;
    while (mayon_sikisal != NULL) {
        //Pou chak sikisal
        Sikisal * sikisal = mayon_sikisal->done;
        int apwovizyonman_reki = 0;

        printf("\t-------------------------------------------------------------");
        printf("\n\tSuccursale : %s", sikisal->deskripsyon);
        printf("\n\t\tId : %d", sikisal->id);
        printf("\n\t\tA approvisionner en:");

        Lis * lis_pwodwi_sikisal = jwenn_lis(MM_LIS_PWODWI_SIKISAL);
        Mayon * mayon_pwodwi_sikisal = lis_pwodwi_sikisal->premye;
        while (mayon_pwodwi_sikisal != NULL) {
            PwodwiSikisal * pwodwi_sikisal = mayon_pwodwi_sikisal->done;

            if (pwodwi_sikisal->sikisal == sikisal->id) {
                if (pwodwi_sikisal->kantite_dispo <= pwodwi_sikisal->kantite_min) {
                    apwovizyonman_reki = 1;
                    Pwodwi * pwodwi = jwenn_nan_lis(jwenn_lis(MM_LIS_PWODWI), pwodwi_sikisal->pwodwi, 1);
                    printf("\n\t\t\t%s | Code -> %d | Quantite requis -> %d",
                           pwodwi->deskripsyon,
                           pwodwi->kod,
                           pwodwi_sikisal->kantite_max - pwodwi_sikisal->kantite_min);
                }
            }
            mayon_pwodwi_sikisal = mayon_pwodwi_sikisal->apre; // pran lot ki swiv li a
        }
        if (!apwovizyonman_reki) printf("\n\t\t\tAucun produit");

        printf("\n");
        mayon_sikisal = mayon_sikisal->apre;
    }
    printf("\t-------------------------------------------------------------");

    printf("\n\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;

    return MM_MENI_RAPO;
}

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
            break;
        case MM_LIS_VANT_AK_PWODWI:
            ret = liste_vant();
            break;
        case MM_LIS_KOMAND:
            ret = liste_komand();
            break;
        case MM_LIS_SIKISAL_POU_APPWOVIZYONE:
            ret = liste_sikisal();
    }
    return ret;
}



void kreye_paj_rapo(Paj * page) {
    page->id = MM_MENI_RAPO;
    page->afiche = afiche_meni_rapo;
}
