//
// Created by Hash Skyd on 4/10/2017.
//

#ifndef MEN_MAKET_DATA_H
#define MEN_MAKET_DATA_H


#include "Maket.h"


// Operations sur les listes
/*
 * Fonksyon sa pemet ou jwenn adres yon lis en fonksyon de tip done ki stoke ladan li
 */
Lis * jwenn_lis(int type);
/*
 * Fonksyon sa pemet ou ajoute yon done nan yon lis
 */
int mete_nan_lis(Lis *lis, void *data);
/*
 * Fonksyon ap chache yon done nan yon lis avek idantifyan done a
 *
 * Lap retounen adres done si paramet done_selman vre, sinon lap retoune mayon nan lis ki gen done a
 * Nan tout ka si li pa jwenn done a, lap retounen NULL
 */
void *jwenn_nan_lis(Lis *liste, int id, int done_selman);
/*
 * Retire yon done nan yon lis
 *
 * siw mete paramet effacer egal a 1, fok ou te sovgade
 */
int retire_nan_lis(Lis *liste, int id, int effacer);
/*
 * Fonksyon sa ap inisyalize done yon lis pou nou
 *
 * Li konseye pou rele li premye fwa ou kreye yon lis. Sa ap pemet ke done ki egziste nan lis la valid
 */
void inisyalize_lis(Lis *liste, int type);
/*
 * Fonksyon sa ap load fichye ki asosye ak lis la e tou ajoute eleman yon nan li
 * a pati de fichye sa
 */
void charger_donnees(int type);

int ecrire_fichier(int type);
int afiche_ekran_sovgade(int type, TypePage paj_retou);

#endif //MEN_MAKET_DATA_H
