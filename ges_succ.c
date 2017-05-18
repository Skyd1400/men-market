//
// Created by Hash Skyd on 4/5/2017.
//

#include <malloc.h>
#include <stdio.h>
#include <mem.h>
#include "ges_succ.h"
#include "Maket.h"
#include "page.h"
#include "menu.h"
#include "data.h"
#include "util.h"
#include "antre.h"




int ajoute_sikisal() {
    ScreenClear();
    afficher_en_tete("Ajouter un client");
    // Kreye varyab kap kenbe kliyan nou an
    Sikisal *sikisal = malloc(sizeof(Sikisal));
    sikisal->adres = malloc(sizeof(Adres));
    textcolor(WHITE);

    // Mande itilizate a enfomasyon sou kliyan nap ajoute a
    antre_teks("\n\tEntrez la description de la succursale : ", sikisal->deskripsyon, 50);

    antre_teks("\tEntrez le nom du responsable : ", sikisal->responsab, 50);

    antre_adres(sikisal->adres);

    antre_nimewo_telefon(sikisal->telefon);

    printf("\n");
    afiche_sikisal(*sikisal); //afiche enfomasyon sikisal ki antre
    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = getch();
    if (chwa == 'O' || chwa == 'o') {
        //Kliyan an deside sovgade done li
        //Pran lis sikisal la
        Lis *lis_sikisal = jwenn_lis(MM_LIS_SIKISAL);
        // mete id ke sikisal sa ka genyen
        sikisal->id = lis_sikisal->id_swivan;
        mete_nan_lis(lis_sikisal, sikisal);// Ajoute li nan lis la
        lis_sikisal->chanje = 1; // gen nouvo enfomasyon ki pa nan fichye
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        printf("\n\tID DE LA SUCCURSALE -> %d\n", sikisal->id);
        textcolor(WHITE);
    } else {
        free(sikisal->adres);
        free(sikisal);
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return MM_MENI_SIKISAL;
}

int modifye_sikisal() {
    return MM_MENI_SIKISAL;
}

int afiche_meni_sikisal() {
    ScreenClear();
    afficher_en_tete("Module Clients");

    Meni meni_sikisal[4] = {
            {"Ajouter une succursale",               MM_AJOU_SIKISAL},
            {"Modifier une succursale",              MM_MODIF_SIKISAL},
            {"Sauvegarder le fichier sur le disque", MM_SOVGAD},
            {"Retour",                               MM_AKEY}
    };
    int ret = afficher_menu(meni_sikisal, 4);
    switch (ret) {
        case MM_AJOU_SIKISAL:
            ret = ajoute_sikisal();
            break;
        case MM_MODIF_SIKISAL:
            ret = modifye_sikisal();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(MM_LIS_SIKISAL, MM_MENI_SIKISAL);
            break;
    }
    return ret;
}

void kreye_paj_sikisal(Paj *paj) {
    paj->id = MM_MENI_SIKISAL;
    paj->afiche = afiche_meni_sikisal;
}
