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
int antre_dat(char *mesaj, Dat *dat, int komansman);


int poz_pou_retounen(int vale);

#endif //MEN_MAKET_ANTRE_H
