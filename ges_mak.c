//
// Created by Hash Skyd on 4/5/2017.
//

#include "ges_mak.h"
#include "lib/conio2.h"
#include "Maket.h"
#include "acc.h"
#include "test.h"
#include "data.h"
#include "ges_cli.h"
#include "rapp.h"


#define MAX_PAGES 4

Page paj[MAX_PAGES];
int paj_kouran;
int pwochen_paj;
int denye_paj;
int nombre_de_pages;


/*
 * main nou an
 */
int main(){
    int fini = 0; // drapo pou jere soti nan pwogram nan
    inittextinfo();
    //mete informasyon fichye yo nan memwa
    charger_donnees(MM_LIS_KLIYAN);
    //kreye paj yo
    creer_page_accueil(&paj[0]);
    kreye_paj_kliyan(&paj[1]);
    kreye_paj_rapo(&paj[2]);
    creer_page_test(&paj[3]);
    paj_kouran = 0; // nap komanse nan paj akey la
    nombre_de_pages = MAX_PAGES;

    while (!fini) {
        // nap soti le varyab fini an chanje
        pwochen_paj = paj[paj_kouran].afiche();
        if (pwochen_paj != paj_kouran) {
            // Nou soti nan paj nou te ye anvan an
            for (int i = 0; i < nombre_de_pages; i++){
                if (pwochen_paj == MM_SORTIE) {
                    // Kondisyon pou nou soti rive
                    fini = 1;
                } else if (paj[i].id == pwochen_paj) {
                    // nou jwenn lot paj la, nap chanje
                    denye_paj = paj_kouran; // pa vreman enpotan
                    paj_kouran = i;
                    break;
                }
            }
        }
    }
    return 0;
}