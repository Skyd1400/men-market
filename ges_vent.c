//
// Created by Hash Skyd on 4/5/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Maket.h"
#include "menu.h"
#include "done/strikti.h"
#include "util.h"
#include "antre.h"
#include "done/fichye.h"


int ajoute_vant() {
    ScreenClear();
    afficher_en_tete("Ajouter une vente");
    textcolor(WHITE);

    char buffer[1024];

    int konfimasyon_nouvo = 0;
    printf("\n\tEst-ce que c'est un nouveau client? \n");
    printf("\t1) Oui\n");
    printf("\t2) Non\n");
    do {
        printf("\tChoisissez un numero : ");
        gets(buffer);
        konfimasyon_nouvo = atoi(buffer);
    } while (konfimasyon_nouvo <= 0 || konfimasyon_nouvo > 2);

    if (konfimasyon_nouvo == 1) {
        afiche_alet("\n\tAjouter le client via la page ", AVETISMAN);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour aller au module Client...");
        getch();
        return MM_MENI_KLIYAN;
    }
    int id_kliyan = 0;
    printf("\n");
    do {
        printf("\tEntrez l'identifiant du client: ");
        gets(buffer);
        id_kliyan = atoi(buffer);
        if (id_kliyan <= 0) {
            textcolor(RED);
            printf("\tL'identifiant est incorrect\n");
            textcolor(WHITE);
        }
    } while (id_kliyan <= 0);
    // Chache id a nan memwa a
    Lis *lis = jwenn_lis(MM_LIS_KLIYAN);
    Mayon *mayon = jwenn_nan_lis(lis, id_kliyan, 0);
    if (mayon == NULL) {
        afiche_alet("\tLe client n'existe pas", DANJE);
        afiche_alet("\n\tAjouter le client via la page ", AVETISMAN);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour aller au module Client...");
        getch();
        return MM_MENI_KLIYAN;
    }
    Kliyan *kliyan = mayon->done;

    int id_sikisal = 0;
    do {
        printf("\tEntrez l'identifiant de la succursale: ");
        gets(buffer);
        id_sikisal = atoi(buffer);
        if (id_sikisal <= 0) {
            textcolor(RED);
            printf("\tL'identifiant est incorrect\n");
            textcolor(WHITE);
        }
    } while (id_kliyan <= 0);
    // Chache id a nan memwa a
    Lis *lis_sikisal = jwenn_lis(MM_LIS_SIKISAL);
    Mayon *mayon_sikisal = jwenn_nan_lis(lis_sikisal, id_sikisal, 0);
    if (mayon_sikisal == NULL) {
        afiche_alet("\tCette succursale n'existe pas", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
        return MM_MENI_VANT;
    }

    Sikisal * sikisal = mayon_sikisal->done;


    time_t moman_kouran = time(NULL);
    struct tm * dat_lokal = localtime(&moman_kouran);

    Dat * dat = malloc(sizeof(Dat));
    konveti_dat(dat_lokal, dat);

    Vant * vant = malloc(sizeof(Vant));

    vant->kliyan = id_kliyan;
    vant->sikisal = id_sikisal;
    vant->dat = dat;

    printf("\n");
    printf("\n\tVente:");
    printf("\n\tNom du client -> %s", kliyan->non);
    printf("\n\tDescription de la succursale -> %s", sikisal->deskripsyon);
    printf("\n\tDate de la vente -> %d/%d/%d - %02d:%02d:%02d\n",
           vant->dat->jou,
           vant->dat->mwa + 1,
           vant->dat->ane,
           vant->dat->le,
           vant->dat->minit, vant->dat->segond);

    printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
    char chwa = getch();
    if (chwa == 'O' || chwa == 'o') {
        //Kliyan an deside sovgade done li
        //Pran lis kliyan an
        Lis *lis_vant = jwenn_lis(MM_LIS_VANT);
        // mete id ke kliyan sa ka genyen
        vant->id = lis_vant->id_swivan;
        mete_nan_lis(lis_vant, vant);// Ajoute li nan lis la
        lis_vant->chanje = 1; // gen nouvo enfomasyon ki pa nan fichye
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        printf("\n\tID DE LA VENTE -> %d\n", vant->id);
        textcolor(WHITE);
    } else {
        free(vant->dat);
        free(vant);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
        return MM_MENI_VANT;
    }

    getch();
    // detay vant
    return  MM_MENI_VANT;
}

int retou_atik() {
    ScreenClear();
    afficher_en_tete("Retourner un article");
    textcolor(WHITE);

    int id = antre_chif("\n\tEntrer l'identifiant de la vente : ");
    if (id < 1) {
        afiche_alet("\tL'id est invalide", DANJE);
        textcolor(WHITE);
    } else {
        Vant * vant = jwenn_nan_lis(jwenn_lis(MM_LIS_VANT), id, 1);
        if (vant == NULL) {
            afiche_alet("\tCette vente n'a pas eu lieu", DANJE);
            textcolor(WHITE);
        } else {
            // Moun nan pa bay fake resi
            id = antre_chif("\tEntrer le code du produit : ");
            if (id < 1) {
                afiche_alet("\tL'id est invalide", DANJE);
                textcolor(WHITE);
            } else {
                DetayVant * detay_vant = NULL;
                Mayon * mayon_detay_vant = jwenn_lis(MM_LIS_DETAY_VANT)->premye;
                while (mayon_detay_vant != NULL) {

                    if (((DetayVant *)mayon_detay_vant->done)->pwodwi == id) {
                        detay_vant = mayon_detay_vant->done;
                        break;
                    }

                    mayon_detay_vant = mayon_detay_vant->apre;
                }

                if (detay_vant == NULL) {
                    afiche_alet("\tCette vente ne comptait pas ce produit", DANJE);
                    textcolor(WHITE);
                } else {
                    int kantite_retounen = antre_chif("\tEntrez la quantite retournee : ");
                    if (kantite_retounen > detay_vant->kantite_atik) {
                        afiche_alet("\tLa quantite d'articles est superieure a celle vendue", DANJE);
                        textcolor(WHITE);
                    } else {
                        printf("\n\tConfirmer le retour de %d articles [(O)ui|(N)on]: ", kantite_retounen);
                        char chwa = getch();
                        if (chwa == 'O' || chwa == 'o') {
                            detay_vant->kantite_atik -= kantite_retounen;
                            afiche_alet("\n\tChangement enregistre", SIKSE);
                            textcolor(WHITE);
                        }
                    }
                }
            }
        }
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_VANT;
}

int afiche_meni_vant(){
    ScreenClear();
    afficher_en_tete("Module Ventes");
    Meni meni_vant[4] = {
            {"Ajouter une vente.",          MM_AJOU_VANT},
            {"Retourner un article vendu.", MM_RETOU_ATIK},
            {"Enregistrer les fichiers.", MM_SOVGAD},
            {"Retour", MM_AKEY}
    };
    int ret = afficher_menu(meni_vant, 4);
    int fichye[2] = {MM_LIS_VANT, MM_LIS_DETAY_VANT};
    switch (ret) {
        case MM_AJOU_VANT:
            ret = ajoute_vant();
            break;
        case MM_RETOU_ATIK:
            ret = retou_atik();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(fichye, 2, MM_MENI_VANT);
            break;
    }
    return ret;
}



void kreye_paj_vant(Paj *page) {
    page->id = MM_MENI_VANT;
    page->afiche = afiche_meni_vant;
}
