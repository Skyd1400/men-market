//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include "Maket.h"
#include "meni.h"
#include "done/strikti.h"
#include "util.h"
#include "antre.h"
#include "done/fichye.h"


/*
 * Fonksyon sa responsab pou jere paj ajoute yon kliyan
 */
int ajoute_kliyan();

/*
 * Fonksyon sa reponsab pou jere paj modifye yon kliyan
 */
int modifye_kliyan();

/*
 * Sa responsab pou mande itilizate a enfomasyon sou yon kliyan
 */
void fomile_kliyan(Kliyan *kliyan);

int afiche_meni_kliyan() {
    ScreenClear();
    afiche_antet("Module Clients");

    Meni meni_kliyan[4] = {
            {"Ajouter un client",                    MM_AJOU_KLIYAN},
            {"Modifier un client",                   MM_MODIF_KLIYAN},
            {"Sauvegarder le fichier sur le disque", MM_SOVGAD},
            {"Retour",                               MM_AKEY}
    };
    int ret = afiche_meni(meni_kliyan, 4);
    int fichye[1] = {MM_LIS_KLIYAN};
    switch (ret) {
        case MM_AJOU_KLIYAN:
            ret = ajoute_kliyan();
            break;
        case MM_MODIF_KLIYAN:
            ret = modifye_kliyan();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(fichye, 1, MM_MENI_KLIYAN);
            break;
    }
    return ret;
}

int ajoute_kliyan() {
    ScreenClear();
    afiche_antet("Ajouter un client");
    // Kreye varyab kap kenbe kliyan nou an
    Kliyan *kliyan = malloc(sizeof(Kliyan));
    kliyan->adres = malloc(sizeof(Adres));
    textcolor(WHITE);

    // Mande itilizate a enfomasyon sou kliyan nap ajoute a

    antre_teks("\n\tEntrez le nom du client :", kliyan->non, 50);

    char * chwa_tip[2] = {"Particulier", "Entreprise"};
    kliyan->tip = antre_chwa("\tEntrez le type de client\n", chwa_tip, 2);

    antre_adres(kliyan->adres);

    antre_nimewo_telefon(kliyan->telefon);

    printf("\n");
    afiche_kliyan(*kliyan); //afiche enfomasyon kliyan an antre
    printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
    char chwa = getch();
    if (chwa == 'O' || chwa == 'o') {
        //Kliyan an deside sovgade done li
        //Pran lis kliyan an
        Lis *lis_kliyan = jwenn_lis(MM_LIS_KLIYAN);
        // mete id ke kliyan sa ka genyen
        kliyan->id = lis_kliyan->id_swivan;
        mete_nan_lis(lis_kliyan, kliyan);// Ajoute li nan lis la
        lis_kliyan->chanje = 1; // gen nouvo enfomasyon ki pa nan fichye
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        printf("\n\tID DU CLIENT -> %d\n", kliyan->id);
        textcolor(WHITE);
    } else {
        free(kliyan->adres);
        free(kliyan);
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_KLIYAN;
}

int modifye_kliyan() {
    ScreenClear();
    afiche_antet("Modifier un client");
    char buffer[1024];
    textcolor(WHITE);

    // Mande itilizate a id
    int id = 0;
    printf("\n");
    do {
        printf("\tEntrez l'identifiant du client: ");
        gets(buffer);
        id = atoi(buffer);
        if (id <= 0) {
            // Pa gen mwayen pou id a pi piti ke zewo
            textcolor(RED);
            printf("\tL'identifiant est incorrect\n");
            textcolor(WHITE);
        }
    } while (id <= 0);
    // Chache id a nan memwa a
    Lis *lis = jwenn_lis(MM_LIS_KLIYAN);
    Mayon *mayon = jwenn_nan_lis(lis, id, 0);
    if (mayon == NULL) {
        // Wow, nou pa jwenn li
        afiche_alet("\tLe client n'existe pas", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    } else {
        // Kliyan an egziste
        Kliyan *kliyan = mayon->done;
        snprintf(buffer, 1024, "\tVous allez modifier le client : %s", kliyan->non);
        afiche_alet(buffer, AVETISMAN);
        textcolor(WHITE);

        // Kliyan an ka chazi sa li vle modifye
        char * opsyon_modifikasyon[4] = {
                "Nom",
                "Type",
                "Adresse",
                "Telephone"
        };
        int chwa_chan = antre_chwa("\n\tQue voulez-vous modifier? \n", opsyon_modifikasyon, 4);

        // Yon done tampore pou modifikasyon
        Kliyan *nouvo_kliyan = malloc(sizeof(Kliyan));
        nouvo_kliyan->adres = malloc(sizeof(Adres));


        char * chwa_tip[2] = {"Particulier", "Entreprise"}; // nou pa ka mete li andedan switch la
        //
        switch (chwa_chan) {
            case 0: // chan non
                antre_teks("\n\tEntrez le nom du client :", nouvo_kliyan->non, 50);
                snprintf(buffer, 1024, "\tAncien Nom : %s", kliyan->non);
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024, "\tNouveau Nom : %s", nouvo_kliyan->non);
                afiche_alet(buffer, SIKSE);
                break;
            case 1: // chan tip
                nouvo_kliyan->tip = antre_chwa("\tEntrez le type de client\n", chwa_tip, 2);
                snprintf(buffer, 1024, "\tAncien Type : %s", kliyan->tip == ENTREPRISE? "Entreprise": "Particulier");
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024, "\tNouveau Nom : %s", kliyan->tip == ENTREPRISE? "Entreprise": "Particulier");
                afiche_alet(buffer, SIKSE);
                break;
            case 2: // chan adres
                antre_adres(nouvo_kliyan->adres);
                snprintf(buffer, 1024,
                         "\tAncien Adresse : \n\t\tNumero : %d\n\t\tRue : %s\n\t\tVille : %s\n\t\tDepartement : %s",
                         kliyan->adres->no,
                         kliyan->adres->ri,
                         kliyan->adres->vil,
                         jwenn_non_depatman(kliyan->adres->depatman));
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024,
                         "\n\tNouvelle Adresse : \n\t\tNumero : %d\n\t\tRue : %s\n\t\tVille : %s\n\t\tDepartement : %s",
                         nouvo_kliyan->adres->no,
                         nouvo_kliyan->adres->ri,
                         nouvo_kliyan->adres->vil,
                         jwenn_non_depatman(nouvo_kliyan->adres->depatman));
                afiche_alet(buffer, SIKSE);
                break;
            case 3: // chan non
                antre_nimewo_telefon(nouvo_kliyan->telefon);
                snprintf(buffer, 1024, "\tAncien Telephone : %s", kliyan->telefon);
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024, "\tNouveau Telephone : %s", nouvo_kliyan->telefon);
                afiche_alet(buffer, SIKSE);
                break;
        }

        printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
        char chwa = getch();
        if (chwa == 'O' || chwa == 'o') {
            Adres * temp = kliyan->adres; // Si moun nan te modifye chan adres la, pou nou ka efase ansyen nou
            switch (chwa_chan) {
                case 1: // anrejistre chan non
                    strncpy(kliyan->non, nouvo_kliyan->non, 50);
                    break;
                case 2: // anrejistre chan tip
                    kliyan->tip = nouvo_kliyan->tip;
                    break;
                case 3: // anrejistre chan adres
                    kliyan->adres = nouvo_kliyan->adres;
                    free(temp);
                    break;
                case 4: // anrejistre chan adres
                    strncpy(kliyan->telefon, nouvo_kliyan->telefon, 9);
                    break;
            }
            lis->chanje = 1; //Nou modifye yon liyn
            afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
            textcolor(WHITE);

        }
        if (chwa_chan != 2) {
            // Apa adres la yo modifye
            free(nouvo_kliyan->adres);
        }
        free(nouvo_kliyan); //detout fason nap detwi nouvo kliyan paske li tampore
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    }
    return MM_MENI_KLIYAN;
}

void antre_tip(Kliyan *kliyan, char *buffer) {
    int tip_kliyan = 0;
    printf("\tEntrez le type de client\n");
    printf("\t1) Particulier\n");
    printf("\t2) Entreprise\n");
    do {
        printf("\tChoisissez un numero : ");
        gets(buffer);
        tip_kliyan = atoi(buffer);
    } while (tip_kliyan <= 0 || tip_kliyan > 2);
    kliyan->tip = tip_kliyan - 1; //

}

void fomile_kliyan(Kliyan *kliyan) {
}




void kreye_paj_kliyan(Paj *page) {
    page->id = MM_MENI_KLIYAN;
    page->afiche = afiche_meni_kliyan;
}
