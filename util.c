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
