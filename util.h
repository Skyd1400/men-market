//
// Created by Hash Skyd on 5/5/2017.
//



#ifndef MEN_MAKET_UTIL_H
#define MEN_MAKET_UTIL_H

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

#endif //MEN_MAKET_UTIL_H
