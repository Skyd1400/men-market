//
// Created by Hash Skyd on 5/21/2017.
//

#include <malloc.h>
#include <stdio.h>
#include <mem.h>
#include "Maket.h"
#include "paj.h"
#include "meni.h"
#include "done/fichye.h"
#include "antre.h"
#include "util.h"
#include "done/strikti.h"

int ajoute_pwodwi() {
    ScreenClear();
    afiche_antet("Ajouter un produit");
    textcolor(WHITE);

    Pwodwi * pwodwi = malloc(sizeof(Pwodwi));

    antre_teks("\n\tEntrez la description de ce produit : ", pwodwi->deskripsyon, 100);
    do {
        pwodwi->kantite = antre_chif("\tEntrez la quantite disponible : ");
    } while (pwodwi->kantite < 0);


    do {
        pwodwi->stok_sekirite = antre_chif("\tEntrez la quantite du stock de securite : ");
    } while (pwodwi->stok_sekirite < 0);


    do {
        pwodwi->pri_revyen_init = antre_chif("\tEntrez le prix de revient du produit : ");
    } while (pwodwi->pri_revyen_init < 0);


    do {
        pwodwi->pri_vant_inite = antre_chif("\tEntrez le prix de vente du produit : ");
    } while (pwodwi->pri_vant_inite < 0);

    char * opsyon_stati[3] = {
            "En vente",
            "Exclus",
            "Non disponible",
    };

    pwodwi->stati = (StatiPwodwi) antre_chwa("\tQuel est le statut de ce produit?\n", opsyon_stati, 3);

    printf("\n");
    afiche_pwodwi(*pwodwi); //afiche enfomasyon sikisal ki antre
    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = (char) getch();
    if (chwa == 'O' || chwa == 'o') {
        Lis *lis_pwodwi = jwenn_lis(MM_LIS_PWODWI);
        pwodwi->kod = lis_pwodwi->id_swivan;
        mete_nan_lis(lis_pwodwi, pwodwi);// Ajoute li nan lis la
        lis_pwodwi->chanje = 1; // gen nouvo enfomasyon ki pa nan fichye
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        printf("\n\tCODE DU PRODUIT -> %d\n", pwodwi->kod);
        textcolor(WHITE);
    } else {
        free(pwodwi);
    }
    return  poz_pou_retounen(MM_MENI_PWODWI);
}

int modifye_pwodwi() {
    ScreenClear();
    afiche_antet("Modifier un produit");
    textcolor(WHITE);

    int kod_pwodwi = antre_chif("\n\tEntrez le code du produit : ");
    if (kod_pwodwi < 1) {
        afiche_alet("\tLe code est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    Pwodwi *pwodwi = jwenn_nan_lis(jwenn_lis(MM_LIS_PWODWI), kod_pwodwi, 1);
    if (pwodwi == NULL) {
        afiche_alet("\tLe produit n'existe pas", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    char * opsyon[6] = {
            "Description",
            "Quantite",
            "Stock de securite",
            "Prix de revient",
            "Prix de vente",
            "Statut",
    };
    int chwa_modifikasyon = antre_chwa("\tQue voulez vous modifier?\n", opsyon, 6);

    Pwodwi nouvo_pw;

    char * opsyon_stati[3] = {
            "En vente",
            "Exclus",
            "Non disponible",
    };

    switch(chwa_modifikasyon) {
        case 0:
            do {
                antre_teks("\tEntrez la nouvelle description : ", nouvo_pw.deskripsyon, 100);
            } while (strlen(nouvo_pw.deskripsyon) > 0);
            break;
        case 1:
            do {
                nouvo_pw.kantite = antre_chif("\tEntrez la quantite : ");
            } while (nouvo_pw.kantite < 0);
            break;
        case 2:
            do {
                nouvo_pw.kantite = antre_chif("\tEntrez le nouveau stock de securite : ");
            } while (nouvo_pw.kantite < 0);
            break;
        case 3:
            do {
                nouvo_pw.pri_revyen_init = antre_chif("\tEntrez le nouveau prix de revient : ");
            } while (nouvo_pw.pri_revyen_init < 0);
            break;
        case 4:
            do {
                nouvo_pw.pri_vant_inite = antre_chif("\tEntrez le nouveau prix de vente : ");
            } while (nouvo_pw.pri_vant_inite < 0);
            break;
        case 5:
            nouvo_pw.stati = (StatiPwodwi) antre_chwa("\tQuel est le statut de ce produit?\n", opsyon_stati, 3);
            break;
    }


    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = (char) getch();
    char buffer[200];
    if (chwa == 'O' || chwa == 'o') {
        switch (chwa_modifikasyon) {
            case 0:
                snprintf(buffer, 200, "\n\tAncien :\n\t%s", pwodwi->deskripsyon);
                afiche_alet(buffer, DANJE);
                strncpy(pwodwi->deskripsyon, nouvo_pw.deskripsyon, 100);
                snprintf(buffer, 200, "\n\tNouveau :\n\t%s", pwodwi->deskripsyon);
                afiche_alet(buffer, SIKSE);
                break;
            case 1:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi->kantite);
                afiche_alet(buffer, DANJE);
                pwodwi->kantite = nouvo_pw.kantite;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi->kantite);
                afiche_alet(buffer, SIKSE);
                break;
            case 2:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi->stok_sekirite);
                afiche_alet(buffer, DANJE);
                pwodwi->stok_sekirite = nouvo_pw.stok_sekirite;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi->stok_sekirite);
                afiche_alet(buffer, SIKSE);
                break;
            case 3:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi->pri_revyen_init);
                afiche_alet(buffer, DANJE);
                pwodwi->pri_revyen_init = nouvo_pw.pri_revyen_init;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi->pri_revyen_init);
                afiche_alet(buffer, SIKSE);
                break;
            case 4:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi->pri_vant_inite);
                afiche_alet(buffer, DANJE);
                pwodwi->pri_vant_inite = nouvo_pw.pri_vant_inite;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi->pri_vant_inite);
                afiche_alet(buffer, SIKSE);
                break;
            case 5:
                snprintf(buffer, 100, "\n\tAncien : %s\t", opsyon_stati[pwodwi->stati]);
                afiche_alet(buffer, DANJE);
                pwodwi->stati = nouvo_pw.stati;
                snprintf(buffer, 100, "Nouveau : %s", opsyon_stati[pwodwi->stati]);
                afiche_alet(buffer, SIKSE);
                break;
        }
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        textcolor(WHITE);
    }
    return poz_pou_retounen(MM_MENI_PWODWI);
    return MM_MENI_PWODWI;
}

int ajoute_pwodwi_sikisal() {
    ScreenClear();
    afiche_antet("Ajouter un produit dans une succursale");
    textcolor(WHITE);

    int kod_pwodwi = antre_chif("\n\tEntrez le code du produit : ");
    if (kod_pwodwi < 1) {
        afiche_alet("\tLe code est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }
    Pwodwi *pwodwi = jwenn_nan_lis(jwenn_lis(MM_LIS_PWODWI), kod_pwodwi, 1);
    if (pwodwi == NULL) {
        afiche_alet("\tLe produit n'existe pas", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    int id_sikisal = antre_chif("\tEntrez l'identifiant de la succursale : ");
    if (id_sikisal < 1) {
        afiche_alet("\tL'identifiant est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);

    }
    Sikisal *sikisal = jwenn_nan_lis(jwenn_lis(MM_LIS_SIKISAL), id_sikisal, 1);
    if (sikisal == NULL) {
        afiche_alet("\tCette succursale n'existe pas", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    PwodwiSikisal * pwodwi_sikisal = malloc(sizeof(PwodwiSikisal));

    pwodwi_sikisal->pwodwi = kod_pwodwi;
    pwodwi_sikisal->sikisal = id_sikisal;


    do {
        pwodwi_sikisal->kantite_min = antre_chif("\tEntrez la qte min que peut contenir la succursale : ");
    } while (pwodwi_sikisal->kantite_min < 0);

    do {
        pwodwi_sikisal->kantite_max = antre_chif("\tEntrez la qte max que peut contenir la succursale : ");
    } while (pwodwi_sikisal->kantite_max < pwodwi_sikisal->kantite_min);

    do {
        pwodwi_sikisal->kantite_dispo = antre_chif("\tEntrez la qte contenue dans la succursale : ");
    } while (pwodwi_sikisal->kantite_dispo > pwodwi_sikisal->kantite_max && pwodwi_sikisal->kantite_dispo < 0);


    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = (char) getch();
    if (chwa == 'O' || chwa == 'o') {
        Lis *lis_pwodwi_sikisal = jwenn_lis(MM_LIS_PWODWI_SIKISAL);
        pwodwi_sikisal->id = lis_pwodwi_sikisal->id_swivan;
        mete_nan_lis(lis_pwodwi_sikisal, pwodwi_sikisal);// Ajoute li nan lis la
        lis_pwodwi_sikisal->chanje = 1; // gen nouvo enfomasyon ki pa nan fichye
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        printf("\n\tID -> %d\n", pwodwi_sikisal->id);
        textcolor(WHITE);
    } else {
        free(pwodwi_sikisal);
    }
    return poz_pou_retounen(MM_MENI_PWODWI);
}

int modifye_pwodwi_sikisal() {
    ScreenClear();
    afiche_antet("Modifier les informations du produit dans la succursale");
    textcolor(WHITE);

    int kod_pwodwi = antre_chif("\n\tEntrez le code du produit : ");
    if (kod_pwodwi < 1) {
        afiche_alet("\tLe code est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    int id_sikisal = antre_chif("\tEntrez l'identifiant de la succursale : ");
    if (id_sikisal < 1) {
        afiche_alet("\tL'identifiant est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    PwodwiSikisal * pwodwi_sikisal = NULL;
    Mayon * mayon_pw = jwenn_lis(MM_LIS_PWODWI_SIKISAL)->premye;
    while (mayon_pw != NULL) {
        PwodwiSikisal * ps = mayon_pw->done;
        if (ps->pwodwi == kod_pwodwi && ps->sikisal == id_sikisal) {
            pwodwi_sikisal = ps;
            break;
        }
        mayon_pw = mayon_pw->apre;
    }

    if (pwodwi_sikisal == NULL) {
        afiche_alet("\tCette succursale ne contient pas ce produit", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    char * opsyon[3] = {
            "Quantite minimum",
            "Quantite disponible",
            "Quantite maximum"
    };
    int chwa_modifikasyon = antre_chwa("\tQue voulez vous modifier?\n", opsyon, 3);

    PwodwiSikisal nouvo_ps;

    switch(chwa_modifikasyon) {
        case 0:
            do {
                nouvo_ps.kantite_min = antre_chif("\tEntrez la qte min que peut contenir la succursale : ");
            } while (nouvo_ps.kantite_min < 0 && nouvo_ps.kantite_min > pwodwi_sikisal->kantite_max);
            break;
        case 1:
            do {
                nouvo_ps.kantite_dispo = antre_chif("\tEntrez la qte contenue dans la succursale : ");
            } while (nouvo_ps.kantite_dispo > pwodwi_sikisal->kantite_max && nouvo_ps.kantite_dispo < 0);
            break;
        case 2:
            do {
                nouvo_ps.kantite_max = antre_chif("\tEntrez la qte max que peut contenir la succursale : ");
            } while (nouvo_ps.kantite_max < pwodwi_sikisal->kantite_min);

    }


    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = (char) getch();
    char buffer[100];
    if (chwa == 'O' || chwa == 'o') {
        switch (chwa_modifikasyon) {
            case 0:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi_sikisal->kantite_min);
                afiche_alet(buffer, DANJE);
                pwodwi_sikisal->kantite_min = nouvo_ps.kantite_min;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi_sikisal->kantite_min);
                afiche_alet(buffer, SIKSE);
                break;
            case 1:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi_sikisal->kantite_dispo);
                afiche_alet(buffer, DANJE);
                pwodwi_sikisal->kantite_dispo = nouvo_ps.kantite_dispo;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi_sikisal->kantite_dispo);
                afiche_alet(buffer, SIKSE);
                break;
            case 2:
                snprintf(buffer, 100, "\n\tAncien : %d\t", pwodwi_sikisal->kantite_max);
                afiche_alet(buffer, DANJE);
                pwodwi_sikisal->kantite_max = nouvo_ps.kantite_max;
                snprintf(buffer, 100, "Nouveau : %d", pwodwi_sikisal->kantite_max);
                afiche_alet(buffer, SIKSE);
                break;
        }
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        textcolor(WHITE);
    }
    return poz_pou_retounen(MM_MENI_PWODWI);
}

int apwovizyone_sikisal() {
    ScreenClear();
    afiche_antet("Approvisionner une succursale");
    textcolor(WHITE);

    int kod_pwodwi = antre_chif("\n\tEntrez le code du produit : ");
    if (kod_pwodwi < 1) {
        afiche_alet("\tLe code est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    Pwodwi *pwodwi = jwenn_nan_lis(jwenn_lis(MM_LIS_PWODWI), kod_pwodwi, 1);
    if (pwodwi == NULL) {
        afiche_alet("\tLe produit n'existe pas", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    int id_sikisal = antre_chif("\tEntrez l'identifiant de la succursale : ");
    if (id_sikisal < 1) {
        afiche_alet("\tL'identifiant est incorrect\n", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    PwodwiSikisal * pwodwi_sikisal = NULL;
    Mayon * mayon_pw = jwenn_lis(MM_LIS_PWODWI_SIKISAL)->premye;
    while (mayon_pw != NULL) {
        PwodwiSikisal * ps = mayon_pw->done;
        if (ps->pwodwi == kod_pwodwi && ps->sikisal == id_sikisal) {
            pwodwi_sikisal = ps;
            break;
        }
        mayon_pw = mayon_pw->apre;
    }

    if (pwodwi_sikisal == NULL) {
        afiche_alet("\tCette succursale ne contient pas ce produit", DANJE);
        return poz_pou_retounen(MM_MENI_PWODWI);
    }

    int kantite_ajoute = pwodwi_sikisal->kantite_max - pwodwi_sikisal->kantite_dispo;
    if (pwodwi->kantite < kantite_ajoute) kantite_ajoute = pwodwi->kantite;
    printf("\tLa succursale va recevoir %d articles\n", kantite_ajoute);

    printf("\n\tEnregistrer les changements [(O)ui|(N)on]: ");
    char chwa = (char) getch();
    char buffer[100];
    if (chwa == 'O' || chwa == 'o') {
        pwodwi->kantite -= kantite_ajoute;
        pwodwi_sikisal->kantite_dispo += kantite_ajoute;
        afiche_alet("\n\tles informations ont ete enregistrees", SIKSE);
        textcolor(WHITE);
    }
    return poz_pou_retounen(MM_MENI_PWODWI);
    return MM_MENI_PWODWI;
}

int afiche_meni_pwodwi() {
    ScreenClear();
    afiche_antet("Module Produits");
    textcolor(WHITE);

    Meni meni[7] = {
            {"Ajouter un produit", MM_AJOU_PWODWI},
            {"Modifier un produit", MM_MODIF_PWODWI},
            {"Ajouter un produit a une succursale", MM_AJOU_PWODWI_SIKISAL},
            {"Modifier les information d'un produit dans une succursale", MM_MODIF_PWODWI_SIKISAL},
            {"Approvisionner une succursale", MM_APWOV_SIKISAL},
            {"Sauvegarder les fichiers", MM_SOVGAD},
            {"Retour", MM_AKEY}
    };
    int ret = afiche_meni(meni, 7);
    int fichye[2] = {MM_LIS_PWODWI, MM_LIS_PWODWI_SIKISAL};
    switch (ret) {
        case MM_AJOU_PWODWI:
            ret = ajoute_pwodwi();
            break;
        case MM_MODIF_PWODWI:
            ret = modifye_pwodwi();
            break;
        case MM_AJOU_PWODWI_SIKISAL:
            ret = ajoute_pwodwi_sikisal();
            break;
        case MM_MODIF_PWODWI_SIKISAL:
            ret = modifye_pwodwi_sikisal();
            break;
        case MM_APWOV_SIKISAL:
            ret = apwovizyone_sikisal();
            break;
        case MM_SOVGAD:
            ret = afiche_ekran_sovgade(fichye, 2, MM_MENI_PWODWI);
            break;
    }
    return ret;
}

void kreye_paj_pwodwi(Paj * paj)  {
    paj->id = MM_MENI_PWODWI;
    paj->afiche = afiche_meni_pwodwi;
}

