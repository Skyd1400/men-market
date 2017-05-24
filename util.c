//
// Created by Hash Skyd on 5/5/2017.
//

#include <stdio.h>
#include <time.h>
#include "util.h"
#include "lib/conio2.h"
#include "Maket.h"

void afiche_alet(const char * mesaj, TipAlet tipAlet) {
    int color = WHITE;
    switch (tipAlet) {
        case SIKSE:
            color = LIGHTGREEN;
            break;
        case AVETISMAN:
            color = YELLOW;
            break;
        case DANJE:
            color = LIGHTRED;
            break;
        case NOMAL:
            color = LIGHTBLUE;
            break;
    }
    textcolor(color);
    printf(mesaj);
}

char * jwenn_non_depatman(Depatman depatman) {
    switch (depatman) {
        case Atibonit:
            return "Artibonite";
        case Grandans:
            return "Grand-Anse";
        case Nip:
            return "Nippes";
        case No:
            return "Nord";
        case Nodes:
            return "Nord-Est";
        case Nodwes:
            return "Nord-Ouest";
        case Sant:
            return "Centre";
        case Sid:
            return "Sud";
        case Sides:
            return "Sud-est";
        case Wes:
            return "Ouest";
        default:
            return NULL;
    }
}



void konveti_dat(const struct tm *dat_c, Dat *dat_nou) {
    dat_nou->segond = dat_c->tm_sec;
    dat_nou->minit = dat_c->tm_min;
    dat_nou->le = dat_c->tm_hour;
    dat_nou->jou = dat_c->tm_mday;
    dat_nou->mwa = dat_c->tm_mon;
    dat_nou->ane = dat_c->tm_year + 1900;
}

void afiche_kliyan(Kliyan kliyan) {
    printf("\tClient:\n");
    printf("\t\tNom -> %s\n", kliyan.non);
    printf("\t\tAdresse :\n");
    printf("\t\t\tNumero -> %d\n", kliyan.adres->no);
    printf("\t\t\tRue -> %s\n", kliyan.adres->ri);
    printf("\t\t\tVille -> %s\n", kliyan.adres->vil);
    printf("\t\t\tDepartement -> %s\n", jwenn_non_depatman(kliyan.adres->depatman)); // TODO depatman nimewo
    printf("\t\tTelephone -> %s\n", kliyan.telefon);
}

void afiche_sikisal(Sikisal sikisal) {
    printf("\tSuccursale:\n");
    printf("\t\tDescription -> %s\n", sikisal.deskripsyon);
    printf("\t\tResponsable -> %s\n", sikisal.responsab);
    printf("\t\tAdresse :\n");
    printf("\t\t\tNumero -> %d\n", sikisal.adres->no);
    printf("\t\t\tRue -> %s\n", sikisal.adres->ri);
    printf("\t\t\tVille -> %s\n", sikisal.adres->vil);
    printf("\t\t\tDepartement -> %s\n", jwenn_non_depatman(sikisal.adres->depatman)); // TODO depatman nimewo
    printf("\t\tTelephone -> %s\n", sikisal.telefon);
}

void afiche_pwodwi(Pwodwi pwodwi) {
    printf("\tProduit : \n");
    printf("\t\tDescription -> %s\n", pwodwi.deskripsyon);
    printf("\t\tQuantite -> %d\n", pwodwi.kantite);
    printf("\t\tStock de securite -> %d\n", pwodwi.stok_sekirite);
    printf("\t\tPrix de revient -> %d\n", pwodwi.pri_revyen_init);
    printf("\t\tPrix de vente -> %d\n", pwodwi.pri_vant_inite);
    char * stati;
    switch (pwodwi.stati) {
        case EN_VENTE:
            stati = "En vente";
            break;
        case EXCLUS:
            stati = "Exclus";
            break;
        case NON_DISPO:
            stati = "Non disponible";
            break;
    }
    printf("\t\tStatut -> %s\n", stati);
}
