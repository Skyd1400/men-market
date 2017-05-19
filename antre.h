//
// Created by Hash Skyd on 5/18/2017.
//

#ifndef MEN_MAKET_ANTRE_H
#define MEN_MAKET_ANTRE_H

#include "Maket.h"

/*
 * Fonksyon sa antre2
 */
int antre_teks(const char *mesaj, char *chen, size_t limit);
int antre_adres(Adres * adres);
int antre_nimewo_telefon(char * chen);
int antre_chwa(const char *mesaj, char **opsyon, int limit);
int antre_chif(const char * mesaj);

#endif //MEN_MAKET_ANTRE_H
