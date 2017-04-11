//
// Created by Hash Skyd on 4/10/2017.
//

#ifndef MEN_MAKET_DATA_H
#define MEN_MAKET_DATA_H


#include "Maket.h"

// Operations sur les listes
Liste * trouver_liste(int type);
int ajouter_a_liste(Liste *liste, void *data);
void *trouver_dans_la_liste(Liste *liste, int id);
int retirer_de_la_Liste(Liste *liste, int id, int effacer);
void init_liste(Liste *liste, int type);
void charger_donnees(int type);

#endif //MEN_MAKET_DATA_H
