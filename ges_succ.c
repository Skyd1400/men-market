//
// Created by Hash Skyd on 4/5/2017.
//

#include <malloc.h>
#include <stdio.h>
#include <mem.h>
#include "Maket.h"
#include "paj.h"
#include "meni.h"
#include "done/strikti.h"
#include "util.h"
#include "antre.h"
#include "done/fichye.h"


int ajoute_sikisal() {
    ScreenClear();
    afiche_antet("Ajouter une succursale");
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
    ScreenClear();
    afiche_antet("Modifier une  Succursale");
    textcolor(WHITE);

    int id_sikisal = antre_chif("\n\tEntrer l'Id de la succursale : ");
    if (id_sikisal < 1) {
        // id a pa bon
        afiche_alet("\tL'identifiant est incorrect", DANJE);
        textcolor(WHITE);
    } else {
        // id a valid, ann chache sikisal ki gen done sa
        Sikisal *sikisal = jwenn_nan_lis(jwenn_lis(MM_LIS_SIKISAL), id_sikisal, 1);
        if (sikisal == NULL) {
            afiche_alet("\tCette succursale n'existe pas", DANJE);
            textcolor(WHITE);
        } else{
            char * opsyon[4] = {"Description", "Adresse", "Responsable", "Telephone"};
            int chwa_modifikasyon = antre_chwa("\tQuel champ voulez-vous modifier?\n", opsyon, 4);

            Sikisal nouvo_sikisal;
            nouvo_sikisal.adres = malloc(sizeof(Adres));

            char buffer[1024];
            switch (chwa_modifikasyon) {
                case 0:
                    antre_teks("\tEntrez la nouvelle description : ", nouvo_sikisal.deskripsyon, 100);
                    snprintf(buffer, 1024, "\tANCIENNE DESC. : %s", sikisal->deskripsyon);
                    afiche_alet(buffer, DANJE);
                    snprintf(buffer, 1024, "\tNOUVELLE DESC. : %s", nouvo_sikisal.deskripsyon);
                    afiche_alet(buffer, SIKSE);
                    break;
                case 1:
                    antre_adres(nouvo_sikisal.adres);
                    snprintf(buffer, 1024,
                             "\tAncien Adresse : \n\t\tNumero : %d\n\t\tRue : %s\n\t\tVille : %s\n\t\tDepartement : %s",
                             sikisal->adres->no,
                             sikisal->adres->ri,
                             sikisal->adres->vil,
                             jwenn_non_depatman(sikisal->adres->depatman));
                    afiche_alet(buffer, DANJE);
                    snprintf(buffer, 1024,
                             "\n\tNouvelle Adresse : \n\t\tNumero : %d\n\t\tRue : %s\n\t\tVille : %s\n\t\tDepartement : %s",
                             nouvo_sikisal.adres->no,
                             nouvo_sikisal.adres->ri,
                             nouvo_sikisal.adres->vil,
                             jwenn_non_depatman(nouvo_sikisal.adres->depatman));
                    afiche_alet(buffer, SIKSE);
                    break;
                case 2:
                    antre_teks("\tEntrez le nom du reponsable : ", nouvo_sikisal.responsab, 50);
                    snprintf(buffer, 1024, "\tANCIEN RESP. : %s", sikisal->responsab);
                    afiche_alet(buffer, DANJE);
                    snprintf(buffer, 1024, "\tNOUVEAU RESP. : %s", nouvo_sikisal.responsab);
                    afiche_alet(buffer, SIKSE);
                    break;
                case 3:
                    antre_nimewo_telefon(nouvo_sikisal.telefon);
                    snprintf(buffer, 1024, "\tAncien Telephone : %s", sikisal->telefon);
                    afiche_alet(buffer, DANJE);
                    snprintf(buffer, 1024, "\tNouveau Telephone : %s", nouvo_sikisal.telefon);
                    afiche_alet(buffer, SIKSE);
                    break;
            }
            textcolor(WHITE);

            printf("\n\tEnregistrer les changements [(O)ui\\(N)on]: ");
            char chwa = getch();
            if (chwa == 'O' || chwa == 'o') {
                Adres * temp = sikisal->adres; // Si moun nan te modifye chan adres la, pou nou ka efase ansyen nou
                switch (chwa_modifikasyon) {
                    case 0: // anrejistre chan non
                        strncpy(sikisal->deskripsyon, nouvo_sikisal.deskripsyon, 100);
                        break;
                    case 1: // anrejistre chan tip
                        sikisal->adres = nouvo_sikisal.adres;
                        free(temp);
                        break;
                    case 2: // anrejistre chan adres
                        strncpy(sikisal->responsab, nouvo_sikisal.responsab, 50);
                        free(temp);
                        break;
                    case 3: // anrejistre chan adres
                        strncpy(sikisal->telefon, nouvo_sikisal.telefon, 9);
                        break;
                }
                afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
                textcolor(WHITE);

            }
            if (chwa_modifikasyon != 1) {
                // Apa adres la yo modifye
                free(nouvo_sikisal.adres);
            }

            printf("\n\tAppuyer sur une touche  pour retourner au menu...");
            getch();

        }
        return MM_MENI_SIKISAL;
    }
}

int afiche_meni_sikisal() {
    ScreenClear();
    afiche_antet("Module Succursale");

    Meni meni_sikisal[4] = {
            {"Ajouter une succursale",               MM_AJOU_SIKISAL},
            {"Modifier une succursale",              MM_MODIF_SIKISAL},
            {"Sauvegarder le fichier sur le disque", MM_SOVGAD},
            {"Retour",                               MM_AKEY}
    };
    int ret = afiche_meni(meni_sikisal, 4);
    int fichye[1] = {MM_LIS_SIKISAL};
    switch (ret) {
        case MM_AJOU_SIKISAL:
            ret = ajoute_sikisal();
            break;
        case MM_MODIF_SIKISAL:
            ret = modifye_sikisal();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(fichye, 1, MM_MENI_SIKISAL);
            break;
    }
    return ret;
}

void kreye_paj_sikisal(Paj *paj) {
    paj->id = MM_MENI_SIKISAL;
    paj->afiche = afiche_meni_sikisal;
}
