#ifndef MEN_MAKET_UTIL_H
#define MEN_MAKET_UTIL_H

#include <time.h>
#include "Maket.h"

typedef enum {
    SIKSE,
    AVETISMAN,
    DANJE,
    NOMAL
} TipAlet;



void afiche_alet(const char *, TipAlet);

char * jwenn_non_depatman(Depatman depatman);

void afiche_kliyan(Kliyan kliyan);
void afiche_sikisal(Sikisal sikisal);
void afiche_pwodwi(Pwodwi pwodwi);

void konveti_dat(const struct tm *dat_c, Dat *dat_nou);
int konpare_dat(Dat dat_a, Dat dat_b);

#endif //MEN_MAKET_UTIL_H
