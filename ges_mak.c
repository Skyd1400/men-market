/*
 * FICHIER : ges_mak.c
 * DATE CREATION : 4/5/2017
 * DESCRIPTION : Fichye sa inisyalize aplikasyon an
 *
 */

#include "Maket.h"
#include "done/fichye.h"
#include "paj.h"


#define MAX_PAJ 6

/*
 * main nou an
 */
int main(){
    Paj paj[MAX_PAJ];
    int paj_kouran = 0;
    int pwochen_paj = 0;
    int nombre_de_pages = MAX_PAJ;
    inittextinfo();
    //mete informasyon fichye yo nan memwa
    chaje_done();
    //kreye paj yo
    kreye_paj_akey(&paj[0]);
    kreye_paj_sikisal(&paj[1]);
    kreye_paj_pwodwi(&paj[2]);
    kreye_paj_kliyan(&paj[3]);
    kreye_paj_vant(&paj[4]);
    kreye_paj_rapo(&paj[5]);

    while (1) {
        pwochen_paj = paj[paj_kouran].afiche();
        if (pwochen_paj == MM_SORTIE) {
            // Kondisyon pou nou soti rive
            break;
        }
        if (pwochen_paj != paj_kouran) {
            // Nou soti nan paj nou te ye anvan an
            for (int i = 0; i < nombre_de_pages; i++){
                if (paj[i].id == pwochen_paj) {
                    // nou jwenn lot paj la, nap chanje
                    paj_kouran = i;
                    break;
                }
            }
        }
    }
    return 0;
}