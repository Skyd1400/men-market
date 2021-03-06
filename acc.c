/*
 * FICHIER : acc.c
 * DATE CREATION : 4/5/2017
 * DESCRIPTION : Fichye sa responsab premye paj la (paj akey la)
 *
 */

#include <stdio.h>
#include "lib/conio2.h"
#include "Maket.h"
#include "paj.h"
#include "meni.h"

/*
 * Fonksyon sa afiche premye paj la
 */
int afficher_accueil() {
    ScreenClear();
    afiche_antet("BIENVENUE");

    Meni meni_akey[6] = {
            {"SUCCURSALES", MM_MENI_SIKISAL},
            {"PRODUITS", MM_MENI_PWODWI},
            {"CLIENT", MM_MENI_KLIYAN},
            {"VENTES", MM_MENI_VANT},
            {"RAPPORTS", MM_MENI_RAPO},
            {"Quitter le programme", MM_SORTIE}
    };
    return afiche_meni(meni_akey, 6);
}

/*
 * Fonksyon sa kreye paj byenvini an
 */
void kreye_paj_akey(Paj *page){
    page->id = MM_AKEY;
    page->afiche = afficher_accueil;
}