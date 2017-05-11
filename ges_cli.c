//
// Created by Hash Skyd on 4/5/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include "Maket.h"
#include "ges_cli.h"
#include "menu.h"
#include "data.h"
#include "util.h"


Meni meni_kliyan[4] = {
        {"Ajouter un client",                    MM_AJOU_KLIYAN},
        {"Modifier un client",                   MM_MODIF_KLIYAN},
        {"Sauvegarder le fichier sur le disque", MM_SOVGAD},
        {"Retour",                               MM_AKEY}
};

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
    afficher_en_tete("Module Clients");
    int ret = afficher_menu(meni_kliyan, 4);
    switch (ret) {
        case MM_AJOU_KLIYAN:
            ret = ajoute_kliyan();
            break;
        case MM_MODIF_KLIYAN:
            ret = modifye_kliyan();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(MM_LIS_KLIYAN, MM_MENI_KLIYAN);
            break;
    }
    return ret;
}

int ajoute_kliyan() {
    ScreenClear();
    afficher_en_tete("Ajouter un client");
    // Kreye varyab kap kenbe kliyan nou an
    Kliyan *kliyan = malloc(sizeof(Kliyan));
    kliyan->adres = malloc(sizeof(Adres));
    textcolor(WHITE);

    // Mande itilizate a enfomasyon sou kliyan nap ajoute a
    fomile_kliyan(kliyan);

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
    afficher_en_tete("Modifier un client");
    char buffer[1024];
    textcolor(WHITE);

    int id = 0;
    printf("\n");
    do {
        printf("\tEntrez l'identifiant du client: ");
        gets(buffer);
        id = atoi(buffer);
        if (id <= 0) {
            textcolor(RED);
            printf("\tL'identifiant est incorrect\n");
            textcolor(WHITE);
        }
    } while (id <= 0);
    // Chache id a nan memwa a
    Lis *lis = jwenn_lis(MM_LIS_KLIYAN);
    Mayon *mayon = jwenn_nan_lis(lis, id, 0);
    Kliyan *kliyan = mayon->done;
    if (kliyan == NULL) {
        afiche_alet("\tLe client n'existe pas", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    } else {
        // Kliyan egziste
        snprintf(buffer, 1024, "\tVous allez modifier le client : %s", kliyan->non);
        afiche_alet(buffer, AVETISMAN);
        textcolor(WHITE);

        Kliyan *nouvo_kliyan = malloc(sizeof(Kliyan));
        nouvo_kliyan->adres = malloc(sizeof(Adres));

        fomile_kliyan(nouvo_kliyan);

        textcolor(LIGHTRED);
        printf("\n\tANCIEN\n");
        afiche_kliyan(*kliyan);

        textcolor(LIGHTGREEN);
        printf("\n\tNOUVEAU\n");
        afiche_kliyan(*nouvo_kliyan);
        textcolor(WHITE);

        printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
        char chwa = getch();
        if (chwa == 'O' || chwa == 'o') {
            nouvo_kliyan->id = kliyan->id;
            mayon->done = nouvo_kliyan; // nou anrejistre done an nan menm mayon an
            // nou detwi ansyen kliyan an
            free(kliyan->adres);
            free(kliyan);
            lis->chanje = 1; //Nou modifye yon liyn
            afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
            textcolor(WHITE);

        } else {
            free(nouvo_kliyan->adres);
            free(nouvo_kliyan);
        }
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    }
    return MM_MENI_KLIYAN;
}

void fomile_kliyan(Kliyan *kliyan) {
    char buffer[1024]; // lapp kenbe antre itilizate a, nou sipoze ke li pap antre plis ke 1024 karakte
    printf("\n\tEntrez le nom du client : ");
    gets(buffer);
    strncpy(kliyan->non, buffer, 49);
    kliyan->non[49] = 0;

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

    printf("\tEntrez l'adresse du client\n");
    do {
        printf("\t\tEntrez le numero : ");
        gets(buffer);
        kliyan->adres->no = atoi(buffer);
    } while (kliyan->adres->no <= 0); //fok li se yon chif antye pozitif

    printf("\t\tEntrez le nom de la rue : ");
    gets(buffer);
    strncpy(kliyan->adres->ri, buffer, 49);
    kliyan->adres->ri[49] = 0;

    printf("\t\tEntrez le nom de la ville : ");
    gets(buffer);
    strncpy(kliyan->adres->vil, buffer, 24);
    kliyan->adres->vil[24] = 0;


    int depatman = 0;
    printf("\t\tEntrez le departement\n");
    for (int i = 0; i < 10; i++) {
        printf("\t\t%d) %s\n", i + 1, jwenn_non_depatman(i));
    }
    do {
        printf("\t\tChoisissez un numero : ");
        gets(buffer);
        depatman = atoi(buffer);
    } while (depatman <= 0 || depatman > 10);
    kliyan->adres->depatman = depatman - 1; //

    int correct;
    do {
        correct = 1;//nou asime ke itilizate ap byen antre enformasyon
        printf("\tEntrez le numero de telephone (12345678): ");
        gets(buffer);
        buffer[8] = 0; //limit 8 character
        for (int i = 0; i < 8; i++) {
            if (!isdigit(buffer[i])) correct = 0; // nou gen youn ki pa chif nan pami an
        }
    } while (!correct);
    strncpy(kliyan->telefon, buffer, 8);
    kliyan->telefon[8] = 0; //kloz chen nan
}


void kreye_paj_kliyan(Page *page) {
    page->id = MM_MENI_KLIYAN;
    page->afiche = afiche_meni_kliyan;
}
