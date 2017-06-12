/*
 * FICHIER : antre.c
 * DATE CREATION : 5/18/2017
 * DESCRIPTION : Fichye sa enplemante fonksyon pou pran done nan itilizate a
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include "antre.h"
#include "util.h"
#include "Maket.h"


char buffer[1024];
/*
 * Fonksyon sa antre enfomasyan nan strikti adres
 */
int antre_adres(Adres *adres) {
    printf("\tEntrez l'adresse :\n");
    adres->no = antre_chif("\t\tEntrez le numero : ");

    antre_teks("\t\tEntrez le nom de la rue : ", adres->ri, 49);
    antre_teks("\t\tEntrez le nom de la ville : ", adres->vil, 24);

    char * depatman[10];
    for (int i = 0; i < 10; i++) {
        depatman[i] =  jwenn_non_depatman((Depatman)i);
    }
    adres->depatman = (Depatman)antre_chwa("\t\tEntrez le departement\n", depatman, 10);
}

/*
 * Fonksyon sa pran yon teks nan men itilizate a mete nan paramet chèn
 *
 */
int antre_teks(const char *mesaj, char *chen, size_t limit) {
    printf(mesaj);
    gets(buffer);
    strncpy(chen, buffer, limit-1);
    chen[limit-1] = 0;
}

/*
 * Fonksyon sa pran yon nimewo telefon nan foma XXXXXXXX e anrejistre li nan chen
 */
int antre_nimewo_telefon(char *chen) {
    int correct;
    do {
        correct = 1;//nou asime ke itilizate ap byen antre enformasyon
        printf("\tEntrez le numero de telephone (XXXXXXXX): ");
        gets(buffer);
        buffer[8] = 0; //limit 8 character
        for (int i = 0; i < 8; i++) {
            if (!isdigit(buffer[i])) correct = 0; // nou gen youn ki pa chif nan pami an
        }
    } while (!correct);
    strncpy(chen, buffer, 8);
    chen[8] = 0; //kloz chen nan
}

/*
 * Fonksyon sa afiche lis w ki nan tablo opsyon an pou li chwazzi
 */
int antre_chwa(const char *mesaj, char **opsyon, int limit) {
    int chwa = 0;
    printf(mesaj);
    for (int i = 0; i < limit; i++) {
        printf("\t%d) %s\n", i + 1, opsyon[i]);
    }
    do {
        printf("\tChoisissez un numero : ");
        gets(buffer);
        chwa = atoi(buffer);
    } while (chwa <= 0 || chwa > limit);
    return chwa - 1;
}

/*
 * Fonksyon sa pemet itilizate a antre chif
 */
int antre_chif(const char *mesaj) {
    int ret;
    int valid = 0;
    do {
        printf(mesaj);
        gets(buffer);
        valid = sscanf(buffer, "%d", &ret);
    } while (valid != 1);
    return ret;
}

/*
 * Fonksyon sa pran yon ti poz
 */
int poz_pou_retounen(int vale) {
    textcolor(WHITE);
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return vale;
}

/*
 * Fonksyon sa valide yon dat
 */
int valide_dat(Dat dat) {
    if (dat.mwa > 12) return 0;
    if (dat.jou > (dat.mwa == 1) ? 29 : 31) return 0;
    else if (dat.le > 23) return 0;
    else if (dat.minit > 59) return 0;
    else if (dat.segond > 59) return 0;
    return 1;
}

/*
 * Fonksyon sa pemet nou antre yon dat nan foma jou/mwa/ane
 */
int antre_dat(char *mesaj, Dat *dat, int komansman) {
    textcolor(WHITE);
    int valid = 0;
    do {
        printf(mesaj);
        gets(buffer);
        valid = sscanf(buffer, "%d/%d/%d", &dat->jou, &dat->mwa, &dat->ane);
        dat->le = komansman ? 0 : 23;
        dat->minit = komansman ? 0 : 59;
        dat->segond = komansman ? 0 : 59;
    } while (valid != 3 && !valide_dat(*dat));
    return 0;
}
