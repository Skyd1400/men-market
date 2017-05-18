//
// Created by Hash Skyd on 4/5/2017.
//

#include "lib/conio2.h"
#include "Maket.h"
#include "data.h"
#include "page.h"


#define MAX_PAJ 6

/*
 * main nou an
 */
int main(){
    Paj paj[MAX_PAJ];
    int paj_kouran = 0;
    int pwochen_paj = 0;
    int denye_paj = 0;
    int nombre_de_pages = MAX_PAJ;
    int fini = 0; // drapo pou jere soti nan pwogram nan
    inittextinfo();
    //mete informasyon fichye yo nan memwa
    charger_donnees();
    //kreye paj yo
    creer_page_accueil(&paj[0]);
    kreye_paj_sikisal(&paj[5]);
    kreye_paj_kliyan(&paj[1]);
    kreye_paj_vant(&paj[2]);
    kreye_paj_rapo(&paj[3]);
    creer_page_test(&paj[4]);

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