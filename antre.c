//
// Created by Hash Skyd on 5/18/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include "antre.h"
#include "util.h"
#include "Maket.h"


char buffer[1024];

int antre_adres(Adres *adres) {
    adres->no = antre_chif("\tEntrez l'adresse : \n");

    antre_teks("\t\tEntrez le nom de la rue : ", adres->ri, 49);
    antre_teks("\t\tEntrez le nom de la ville : ", adres->vil, 24);

    char * depatman[10];
    for (int i = 0; i < 10; i++) {
        depatman[i] =  jwenn_non_depatman((Depatman)i);
    }
    adres->depatman = (Depatman)antre_chwa("\t\tEntrez le departement\n", depatman, 10);
}

int antre_teks(const char *mesaj, char *chen, size_t limit) {
    printf(mesaj);
    gets(buffer);
    strncpy(chen, buffer, limit-1);
    chen[limit-1] = 0;
}

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


int poz_pou_retounen(int vale) {
    textcolor(WHITE);
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return vale;
}
