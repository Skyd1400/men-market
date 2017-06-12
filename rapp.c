/*
 * FICHIER : rapp.c
 * DATE CREATION : 4/5/2017
 * DESCRIPTION : Pati sa se li ki gen fonksyonalite an rapo ak modil rapo.
 * Fonksyon ladanl yo afiche meni rapo a e enplemante fonksyonalite ki nan kaye chaj la
 *
 */
#include <stdio.h>
#include "Maket.h"
#include "paj.h"
#include "meni.h"
#include "done/strikti.h"
#include "util.h"
#include "antre.h"

/*
 * Fonksyon sa afiche paj pou liste kliyan an
 */
int liste_kliyan() {
    ScreenClear();
    afiche_antet("Liste des clients");
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
        if (lis_i.nonb > 0) {
            textcolor(LIGHTBLUE);
            printf("\n\t:: %s ::", jwenn_non_depatman(i));//Afiche depatman an
            textcolor(WHITE);
            Mayon *mayon_i = lis_i.premye; //pran premye mayon an
            while (mayon_i != NULL) {
                // gen eleman pou nou trete
                Kliyan *kliyan = mayon_i->done;
                printf("\n%6d %s %s", kliyan->id, kliyan->non, kliyan->telefon);
                mayon_i = mayon_i->apre; //
            }
            printf("\n"); // yon ti espas a la fin
        }
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_RAPO;
}

/*
 * Fonksyon sa afiche tout lis vant ki fet yo pa pwodwi e afiche egalman fos kob ou fe
 */
int liste_vant() {
    ScreenClear();
    afiche_antet("Liste des ventes pour une periode");
    textcolor(WHITE);

    Dat dat_komansman;
    antre_dat("\n\tEntrez La date de debut (Ex: 01/05/2015) : ", &dat_komansman, 0);
    Dat dat_fen;
    antre_dat("\tEntrez La date de fin (Ex: 01/05/2015) : ", &dat_fen, 1);
    if (konpare_dat(dat_komansman, dat_fen) != -1) {
        afiche_alet("\tIntervalle incorrect", DANJE);
        return poz_pou_retounen(MM_MENI_RAPO);
    }
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
                int dat_nan_enteval = (konpare_dat(*vant->dat, dat_komansman) != -1) && (konpare_dat(dat_fen, *vant->dat) != -1);
                if (vant->sikisal == sikisal->id && dat_nan_enteval) {
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

/*
 * Fonksyon sa afiche tout pwodwi ki pou komande ak lis pwodwi pou komande a
 */
int liste_komand() {
    ScreenClear();
    afiche_antet("Liste des commandes");
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

/*
 * Fonksyon sa afiche lis sikisal ki dwe apwovizyone yo
 */
int liste_sikisal() {
    ScreenClear();
    afiche_antet("Succursales a approvisionner");
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
    afiche_antet("Rapports");
    Meni meni_rapo[5] = {
            {"Liste des clients", MM_LIS_KLIYAN_PA_DEPATMAN},
            {"Resume des ventes", MM_LIS_VANT_AK_PWODWI},
            {"Liste des produits a commander", MM_LIS_KOMAND},
            {"Liste des succursales a approvisionner", MM_LIS_SIKISAL_POU_APWOVIZYONE},
            {"Retour", MM_AKEY}
    };
    int ret = afiche_meni(meni_rapo, 5);
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
        case MM_LIS_SIKISAL_POU_APWOVIZYONE:
            ret = liste_sikisal();
    }
    return ret;
}


/*
 * Fonksyon sa kreye paj rapo
 */
void kreye_paj_rapo(Paj * page) {
    page->id = MM_MENI_RAPO;
    page->afiche = afiche_meni_rapo;
}
