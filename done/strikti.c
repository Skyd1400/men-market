//
// Created by Hash Skyd on 4/10/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mem.h>
#include "../Maket.h"
#include "strikti.h"
#include "../lib/csv.h"
#include "../page.h"
#include "../util.h"


Lis liste_succursales;
Lis liste_produits;
Lis liste_produits_succursales;
Lis liste_clients;
Lis liste_ventes;
Lis liste_details_ventes;


#define T_TAMPON 1024

Lis *jwenn_lis(int type) {
    switch (type) {
        case MM_LIS_SIKISAL:
            return &liste_succursales;
        case MM_LIS_PWODWI:
            return &liste_produits;
        case MM_LIS_PWODWI_SIKISAL:
            return &liste_produits_succursales;
        case MM_LIS_KLIYAN:
            return &liste_clients;
        case MM_LIS_VANT:
            return &liste_ventes;
        case MM_LIS_DETAY_VANT:
            return &liste_details_ventes;
        default:
            return NULL;
    }
}

int jwenn_id_done(int type, void *data) {
    if (data == NULL) return -1;
    switch (type) {
        case MM_LIS_SIKISAL:
            return ((Sikisal *) data)->id;
        case MM_LIS_PWODWI:
            return ((Pwodwi *) data)->kod;
        case MM_LIS_PWODWI_SIKISAL:
            return ((PwodwiSikisal *) data)->id;
        case MM_LIS_KLIYAN:
            return ((Kliyan *) data)->id;
        case MM_LIS_VANT:
            return ((Vant *) data)->id;
        case MM_LIS_DETAY_VANT:
            return ((DetayVant *) data)->id;
        default:
            return -1;
    }
}

int mete_nan_lis(Lis *lis, void *data) {
    int result = 0;
    if (lis != NULL && data != NULL) {
        // Kreye espas pou mayon an
        Mayon *temp = malloc(sizeof(Mayon));
        // Anrejistre done a andedan mayon an
        temp->done = data;
        // Nou toujou mete li nan fen lis la
        temp->anvan = lis->denye; // Nou mete denye nan lis lan anvan mayon sa
        temp->apre = NULL; // Pa gen anyen apre mayon sa
        if (temp->anvan != NULL) temp->anvan->apre = temp; //Nou mete mayon sa apre denye nan lis la si li egziste
        // Nou gade si id done nap mete pi gran ke premye a
        //si wi nou enkremante id_swivan nan lis la
        int data_id = jwenn_id_done(lis->tip, data);
        if (data_id >= lis->id_swivan) lis->id_swivan = data_id + 1;
        // nou mete mayon sa kom denye eleman nan lis la
        lis->denye = temp;
        //Si se premye mayon nou mete, li anvan nan lis la tou
        if (lis->nonb == 0) lis->premye = temp;
        lis->nonb++;
        result = 1;
    }
    return result;
}

void *jwenn_nan_lis(Lis *liste, int id, int done_selman) {
    if (liste->nonb == 0) return NULL; // lis la vid
    Mayon *temp = liste->premye; // pran adres premye eleman
    do {
        if (temp->done != NULL && jwenn_id_done(liste->tip, temp->done) == id) {
            // nou jwenn li, retounen done a oubyen mayon an an fonksyon de done_selman
            return done_selman ? temp->done : temp;
        }
        // Sorry, nou pa jwenn li, pran mayon apre a
        temp = temp->apre;
    } while (temp != NULL);
    // Resorry, nou pa jwenn anyen menm
    return NULL;
}

int retire_nan_lis(Lis *liste, int id, int effacer) {
    Mayon *a_eff = jwenn_nan_lis(liste, id, 0);
    if (a_eff != NULL) {
        if (a_eff->anvan) a_eff->anvan->apre = a_eff->apre;
        if (a_eff->apre) a_eff->apre->anvan = a_eff->anvan;
        void *temp = a_eff->done;
        if (effacer) {
            switch (liste->tip) {
                case MM_LIS_KLIYAN:
                    free(((Kliyan *) temp)->adres);
                    break;
                    //TODO add the rest
                case MM_LIS_SIKISAL:
                    break;
                case MM_LIS_PWODWI:
                    break;
                case MM_LIS_PWODWI_SIKISAL:
                    break;
                case MM_LIS_VANT:
                    break;
                case MM_LIS_DETAY_VANT:
                    break;
            }
            free(temp); // Yo mande pou nou efase done a
        }
        free(a_eff); // nou toujou efase mayon an
        liste->nonb--;
        return 1;
    }
    return 0;
}

void inisyalize_lis(Lis *lis) {
    if (lis == NULL) lis = malloc(sizeof(Lis)); // Okazou nou potko janm inisyalize espas memwa pou li
    lis->nonb = 0; // Ya, poko gen eleman :)
    lis->id_swivan = 1; //N'ap komanse ak 1
    lis->chanje = 0; //Lis la gen menm enfomasyon ak fichye a pa defo
    lis->premye = lis->denye = NULL; // Nou pa gen eleman
}




