/*
 * FICHIER : meni.c
 * DATE CREATION : 5/5/2017
 * DESCRIPTION : Li gen yon sel fonksyon ki responsab afichaj meni yo
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "lib/conio2.h"
#include "meni.h"
#include "antre.h"


/*
 * Fonksyon sa afiche meni ak opsyon ki nan tablo meni e retounen chwa itilizate a
 */
int afiche_meni(Meni *meni, int chwa_posib) {
    textcolor(WHITE);
    printf("\n");
    char ** buffer = malloc(sizeof(char *) * chwa_posib);
    for (int i = 0; i < chwa_posib; ++i) {
        buffer[i] = meni[i].non;
    }
    int chwa = antre_chwa("\n", buffer, chwa_posib);
    int ret =  meni[chwa].paj_swivan;
    return ret;
}