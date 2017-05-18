//
// Created by Hash Skyd on 5/18/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include "antre.h"
#include "util.h"


char buffer[1024];

int antre_adres(Adres *adres) {
    printf("\tEntrez l'adresse du client\n");
    do {
        printf("\t\tEntrez le numero : ");
        gets(buffer);
        adres->no = atoi(buffer);
    } while (adres->no <= 0); //fok li se yon chif antye pozitif

    printf("\t\tEntrez le nom de la rue : ");
    gets(buffer);
    strncpy(adres->ri, buffer, 49);
    adres->ri[49] = 0;

    printf("\t\tEntrez le nom de la ville : ");
    gets(buffer);
    strncpy(adres->vil, buffer, 24);
    adres->vil[24] = 0;

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
    adres->depatman = depatman - 1; //
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

int antre_chwa(const char *prompt, char **opsyon, int limit) {
    int chwa = 0;
    printf(prompt);
    for (int i = 0; i < limit; i++) {
        printf("\t%d) %s\n", i + 1, opsyon[i]);
    }
    do {
        printf("\tChoisissez un numero : ");
        gets(buffer);
        chwa = atoi(buffer);
    } while (chwa <= 0 || chwa > 2);
    return chwa - 1;
}
