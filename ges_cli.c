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


void antre_non(Kliyan * kliyan, char * buffer);

void antre_tip(Kliyan *kliyan, char *buffer);

void antre_adres(Kliyan *kliyan, char *buffer);

void antre_telefon(Kliyan *kliyan, char *buffer);

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
    if (mayon == NULL) {
        afiche_alet("\tLe client n'existe pas", DANJE);
        textcolor(WHITE);
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    } else {
        // Kliyan egziste
        Kliyan *kliyan = mayon->done;
        snprintf(buffer, 1024, "\tVous allez modifier le client : %s", kliyan->non);
        afiche_alet(buffer, AVETISMAN);
        textcolor(WHITE);


        int chwa_chan_modifikasyon = 0;
        printf("\n\tQue voulez-vous modifier? \n");
        printf("\t1) Nom\n");
        printf("\t2) Type\n");
        printf("\t3) Adresse\n");
        printf("\t4) Telephone\n");
        do {
            printf("\tChoisissez un numero : ");
            gets(buffer);
            chwa_chan_modifikasyon = atoi(buffer);
        } while (chwa_chan_modifikasyon <= 0 || chwa_chan_modifikasyon > 4);



        Kliyan *nouvo_kliyan = malloc(sizeof(Kliyan));
        nouvo_kliyan->adres = malloc(sizeof(Adres));
        //

        switch (chwa_chan_modifikasyon) {
            case 1: // chan non
                antre_non(nouvo_kliyan, buffer);
                snprintf(buffer, 1024, "\tAncien Nom : %s", kliyan->non);
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024, "\tNouveau Nom : %s", nouvo_kliyan->non);
                afiche_alet(buffer, SIKSE);
                break;
            case 2: // chan tip
                antre_tip(nouvo_kliyan, buffer);
                snprintf(buffer, 1024, "\tAncien Type : %s", kliyan->tip == ENTREPRISE? "Entreprise": "Particulier");
                afiche_alet(buffer, DANJE);
                snprintf(buffer, 1024, "\tNouveau Nom : %s", kliyan->tip == ENTREPRISE? "Entreprise": "Particulier");
                afiche_alet(buffer, SIKSE);
                break;
            case 3: // chan adres
                antre_adres(nouvo_kliyan, buffer);
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
            case 4: // chan non
                antre_telefon(nouvo_kliyan, buffer);
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
            switch (chwa_chan_modifikasyon) {
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
        if (chwa_chan_modifikasyon != 3) {
            // Apa adres la yo modifye
            free(nouvo_kliyan->adres);
        }
        free(nouvo_kliyan); //detout fason nap detwi nouvo kliyan paske li tampore
        printf("\n\tAppuyer sur une touche  pour retourner au menu...");
        getch();
    }
    return MM_MENI_KLIYAN;
}

void antre_non(Kliyan *kliyan, char *buffer) {
    printf("\n\tEntrez le nom du client : ");
    gets(buffer);
    strncpy(kliyan->non, buffer, 49);
    kliyan->non[49] = 0;
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
    char buffer[1024]; // lapp kenbe antre itilizate a, nou sipoze ke li pap antre plis ke 1024 karakte
    antre_non(kliyan, buffer);

    antre_tip(kliyan, buffer);

    antre_adres(kliyan, buffer);

    antre_telefon(kliyan, buffer);
}

void antre_telefon(Kliyan *kliyan, char *buffer) {
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

void antre_adres(Kliyan *kliyan, char *buffer) {
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
}


void kreye_paj_kliyan(Page *page) {
    page->id = MM_MENI_KLIYAN;
    page->afiche = afiche_meni_kliyan;
}
