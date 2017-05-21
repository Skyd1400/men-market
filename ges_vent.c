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


    char *opsyon_nouvo[2] = {"Oui", "Non"};
    int konfimasyon_nouvo = antre_chwa("\n\tEst-ce que c'est un nouveau client?\n", opsyon_nouvo, 2);

    if (konfimasyon_nouvo == 0) {
        afiche_alet("\n\tAjouter le client via la page \"Ajouter un client\"", AVETISMAN);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour aller au module client...");
        getch();
        return MM_MENI_KLIYAN;
    }
    int id_kliyan = antre_chif("n\tEntrez l'identifiant du client : ");
    if (id_kliyan < 1) {
        afiche_alet("\tL'identifiant est incorrect\n", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
        return MM_MENI_VANT;
    }
    Kliyan *kliyan = jwenn_nan_lis(jwenn_lis(MM_LIS_KLIYAN), id_kliyan, 1);

    if (kliyan == NULL) {
        afiche_alet("\tLe client n'existe pas", DANJE);
        afiche_alet("\n\tAjouter le client via la page ", AVETISMAN);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour aller au module Client...");
        getch();
        return MM_MENI_KLIYAN;
    }

    int id_sikisal = antre_chif("\tEntrez l'identifiant de la succursale : ");
    if (id_sikisal < 1) {
        afiche_alet("\tL'identifiant est incorrect\n", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
        return MM_MENI_VANT;
    }
    Sikisal *sikisal = jwenn_nan_lis(jwenn_lis(MM_LIS_SIKISAL), id_sikisal, 1);
    if (sikisal == NULL) {
        afiche_alet("\tCette succursale n'existe pas", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
        return MM_MENI_VANT;
    }

    time_t moman_kouran = time(NULL);
    struct tm *dat_lokal = localtime(&moman_kouran);

    Dat *dat = malloc(sizeof(Dat));
    konveti_dat(dat_lokal, dat);

    Vant *vant = malloc(sizeof(Vant));

    vant->kliyan = id_kliyan;
    vant->sikisal = id_sikisal;
    vant->dat = dat;

    //Pran lis kliyan an
    Lis *lis_vant = jwenn_lis(MM_LIS_VANT); // pa bliye li
    // mete id ke kliyan sa ka genyen
    vant->id = lis_vant->id_swivan;

    //afiche detay vant la pou itilizate a we
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

    char continuer;
    Lis * lis_detay = jwenn_lis(MM_LIS_DETAY_VANT); // pou nou ka pran pwochen id a ladan li
    Lis lis = {0, 0, lis_detay->id_swivan, NULL, NULL, MM_LIS_DETAY_VANT}; // sa se yon lis tampore
    do { // Fo li achte kan menm
        Pwodwi * pwodwi = NULL;
        int kod_pwodwi = antre_chif("\n\tEntrer le code du produit : ");
        if (kod_pwodwi < 1) {
            afiche_alet("\tL'identifiant est incorrect\n", DANJE);
            textcolor(WHITE);
        }
        pwodwi = jwenn_nan_lis(jwenn_lis(MM_LIS_PWODWI), kod_pwodwi, 1); // Pou nou ka pran pri vant
        PwodwiSikisal * pwodwi_sikisal = NULL;
        Mayon * mayon_pwodwi_sikisal = jwenn_lis(MM_LIS_PWODWI_SIKISAL)->premye;
        while (mayon_pwodwi_sikisal != NULL) {
            PwodwiSikisal * ps = (PwodwiSikisal *) mayon_pwodwi_sikisal->done;
            if (ps->pwodwi == kod_pwodwi && ps->sikisal == id_sikisal) {
                pwodwi_sikisal = ps;
                break;
            }
            mayon_pwodwi_sikisal = mayon_pwodwi_sikisal->apre;
        }
        if (pwodwi == NULL && pwodwi_sikisal == NULL) {
            // Verifye ke se pa yon lot kote li soti ak li
            afiche_alet("\tCe produit n'existe pas dans le magasin\n", DANJE);
            textcolor(WHITE);
        } else {
            int kantite = 0;
            do {
                kantite = antre_chif("\tEntrez la quantite achetee : ");
            } while (kantite < 1 && kantite > pwodwi_sikisal->kantite_dispo); // Yon moun pa ka achte -1 pwodwi oswa anyen

            DetayVant * detay_vant = malloc(sizeof(DetayVant));
            detay_vant->pwodwi = kod_pwodwi;
            detay_vant->kantite_atik = kantite;
            detay_vant->pri_inite = pwodwi->pri_vant_inite;
            detay_vant->vant = vant->id; // raple ke mwenn te setup sa anle a
            detay_vant->id = lis.id_swivan; // nou te inisyalize vale sa anle a tou
            // Nap anrejistre li nan lis tanpore a
            mete_nan_lis(&lis, detay_vant);
        }
        printf("\n\tContinuer l'ajout [(O)ui|(N)on] : ");
        continuer = getch();
    }while (continuer == 'O' || continuer == 'o');

    printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
    char chwa = getch();
    if (chwa == 'O' || chwa == 'o') {
        if (lis.nonb > 0) { // Fok gen yon atiki ki van
            mete_nan_lis(lis_vant, vant);// anrejistre vant la nan lis la
            // Yon ti maji nwa
            if (lis_detay->denye != NULL) lis_detay->denye->apre = lis.premye; // Nou ajoute fen lis la nan lis prensipal la
            lis.premye->anvan = lis_detay->denye; // nou ajoute lis prensipal la anvan lis nou an
            lis_detay->denye = lis.denye;
            if (lis_detay->premye == NULL) lis_detay->premye = lis.premye; // pat gen anyen nan lis la;
            // Nou mete a jou done sou lis la
            lis_detay->nonb += lis.nonb;
            lis_detay->id_swivan = lis.id_swivan;
            // Retire pwodwi a nan magazen an
            Mayon * mayon = lis.premye;
            while (mayon != NULL) {
                DetayVant * dv = mayon->done;

                PwodwiSikisal * pwodwi_sikisal = NULL;
                Mayon * mayon_pwodwi_sikisal = jwenn_lis(MM_LIS_PWODWI_SIKISAL)->premye;
                while (mayon_pwodwi_sikisal != NULL) {
                    PwodwiSikisal * ps = (PwodwiSikisal *) mayon_pwodwi_sikisal->done;
                    if (ps->pwodwi == dv->pwodwi && ps->sikisal == id_sikisal) {
                        ps->kantite_dispo -= dv->kantite_atik;
                    }
                    mayon_pwodwi_sikisal = mayon_pwodwi_sikisal->apre;
                }
                mayon = mayon->apre;
            }
            // Seyans maji nwa a fini
            afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
            printf("\n\tID DE LA VENTE -> %d\n", vant->id);
            textcolor(WHITE);
        }
    } else {
        Mayon * mayon = lis.premye;
        while (mayon != NULL) {
            free(mayon->done);
            Mayon * m = mayon;
            mayon = mayon->apre;
            free(m);
        }
        free(vant->dat);
        free(vant);
        textcolor(WHITE);
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_VANT;
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
        Vant *vant = jwenn_nan_lis(jwenn_lis(MM_LIS_VANT), id, 1);
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
                DetayVant *detay_vant = NULL;
                Mayon *mayon_detay_vant = jwenn_lis(MM_LIS_DETAY_VANT)->premye;
                while (mayon_detay_vant != NULL) {

                    if (((DetayVant *) mayon_detay_vant->done)->pwodwi == id) {
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

int afiche_meni_vant() {
    ScreenClear();
    afficher_en_tete("Module Ventes");
    Meni meni_vant[4] = {
            {"Ajouter une vente.",          MM_AJOU_VANT},
            {"Retourner un article vendu.", MM_RETOU_ATIK},
            {"Enregistrer les fichiers.",   MM_SOVGAD},
            {"Retour",                      MM_AKEY}
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
