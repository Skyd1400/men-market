//
// Created by Hash Skyd on 4/10/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mem.h>
#include "Maket.h"
#include "data.h"
#include "lib/csv.h"
#include "page.h"
#include "util.h"


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

void inisyalize_lis(Lis *liste, int type) {
    if (liste == NULL) liste = malloc(sizeof(Lis)); // Okazou nou potko janm inisyalize espas memwa pou li
    liste->nonb = 0; // Ya, poko gen eleman :)
    liste->id_swivan = 1; //N'ap komanse ak 1
    liste->chanje = 0; //Lis la gen menm enfomasyon ak fichye a pa defo
    liste->premye = liste->denye = NULL; // Nou pa gen eleman
}

typedef struct {
    int data_type; // tip lis nap trete
    void *temp; //adres done ki pou liyn nap trete a
    int c_ligne; // nimewo liyn nou ye a
    int c_champ; // nimewo kolon nou ye kounya
} DoneAnaliz;

void tretman_chan(void *vale_chan, size_t tay_chan, void *done_analiz) {
    DoneAnaliz *p_data = ((DoneAnaliz *) done_analiz); // yon ti konvesyon
    if (p_data->c_ligne > 0 &&
        p_data->temp != NULL) { // sote premye liyn nan e asire ke espas pou stoke an egziste pou liyn nan
        if (p_data->data_type == MM_LIS_KLIYAN) {
            // Se nan fichye kliyan an nou ye
            Kliyan *client = p_data->temp; // chanjman tip otomatik
            int len_s = strlen(vale_chan);
            switch (p_data->c_champ) {
                case 0: //Champ ID
                    client->id = atoi(vale_chan);
                    break;
                case 1: // Champ Nom
                    strncpy(client->non, vale_chan, 49);
                    break;
                case 2: // Champ type
                    client->tip = ((char *) vale_chan)[0] == 'E' ? ENTREPRISE : PARTICULIER;
                    break;
                case 3: // chan no adress
                    client->adres->no = atoi(vale_chan);
                    break;
                case 4: // chan ri adres
                    strncpy(client->adres->ri, vale_chan, 49);
                    break;
                case 5: // chan vil adres
                    strncpy(client->adres->vil, vale_chan, 24);
                    break;
                case 6: // chan depatman
                    client->adres->depatman = atoi(vale_chan);
                    break;
                case 7: // Champ Telephone
                    strncpy(client->telefon, vale_chan, 8);
                    client->telefon[8] = 0;
                    break;
                default:
                    break;
            }
        } else if (p_data->data_type == MM_LIS_SIKISAL) {
            Sikisal *temp = p_data->temp;
            switch (p_data->c_champ) {
                case 0: //chan Id
                    temp->id = atoi(vale_chan);
                    break;
                case 1: //chan deskripsyon
                    strncpy(temp->deskripsyon, vale_chan, 99);
                    break;
                case 2: // chan no adress
                    temp->adres->no = atoi(vale_chan);
                    break;
                case 3: // chan ri adres
                    strncpy(temp->adres->ri, vale_chan, 49);
                    break;
                case 4: // chan vil adres
                    strncpy(temp->adres->vil, vale_chan, 24);
                    break;
                case 5: // chan depatman
                    temp->adres->depatman = atoi(vale_chan);
                    break;
                case 6: // chan depatman
                    strncpy(temp->responsab, vale_chan, 19);
                    break;
                case 7: // Champ Telephone
                    strncpy(temp->telefon, vale_chan, 8);
                    temp->telefon[8] = 0;
                    break;
            }
        }
    }
    p_data->c_champ++; // lot kolon apre a

}

void tretman_liyn(int c, void *data) {
    DoneAnaliz *p_data = ((DoneAnaliz *) data);
    p_data->c_ligne++;
    if (p_data->c_ligne > 0) // nou sote premye lin nan
    {
        Lis *liste; // li pral stoke adres lis nap trete
        int t; //lap stoke tay yon eleman nan lis la
        switch (p_data->data_type) { // mete vale pou de varyab yo swivan lis nou deside trete a
            case MM_LIS_KLIYAN:
                liste = &liste_clients;
                t = sizeof(Kliyan);
                break;
            case MM_LIS_SIKISAL:
                liste = jwenn_lis(MM_LIS_SIKISAL);
                t = sizeof(Sikisal);
                break;
        }
        if (p_data->temp != NULL) {
            // nou te gentan gen yon eleman nou tap trete deja
            mete_nan_lis(liste, p_data->temp); // nou jis ajoute li nan lis la kom yon lot eleman
        }
        // nou kreye yon nouvo eleman pou nouvo liyn
        void *temp = malloc(t);

        if (p_data->data_type == MM_LIS_KLIYAN || p_data->data_type == MM_LIS_SIKISAL) {
            // N'ap ajoute adres la si se lis kliyan oswa sikisal n'ap trete
            Adres *temp_address = malloc(sizeof(Adres)); // alokasyon memwa pou adres la
            if (p_data->data_type == MM_LIS_KLIYAN) {
                ((Kliyan *) temp)->adres = temp_address;
            } else {
                ((Sikisal *) temp)->adres = temp_address;
            }
        }
        // nou nan fen lin ke nou tap trete a, e nou pral koumanse yon lot, donk nou prepare andwa pou
        // stoke done yo e nou remete nimewo chan nou ye a a zewo
        p_data->temp = temp;
        p_data->c_champ = 0;
    }
}

int charger_fichier(int type_donnees) {
    char *fichier; // sa pral stoke non fichye a
    switch (type_donnees) {
        // n'ap ba varyab la vale swivan ki lis nou deside ouve
        case MM_LIS_KLIYAN:
            fichier = FICHYE_KLIYAN;
            break;
        case MM_LIS_SIKISAL:
            fichier = FICHYE_SIKISAL;
            break;
        default:
            return 1;
    }
    FILE *fp = fopen(fichier, "r");
    if (!fp) {
        // fichye a pa egziste kreye li epi soti paske li pa gen pyes done
        fp = fopen(fichier, "w");
        fclose(fp);
        return 1;
    }
    struct csv_parser p;
    size_t r; // konbyen oktet ki li
    char buf[T_TAMPON]; // lap stoke blok nap trete a
    DoneAnaliz data = {type_donnees, NULL, 0, 0}; // nou inisyalize done nou yo
    csv_init(&p, CSV_APPEND_NULL); // nou inisyalize bibliyotek nou an ak opsyon pou li temine chen yo pa zewo
    while ((r = fread(buf, 1, T_TAMPON, fp)) > 0) { // li yon moso nan fichye toutotan li pa rive nan fen
        if (csv_parse(&p, buf, r, tretman_chan, tretman_liyn, &data) != r) //trete moso ou li a e verifye ke pa gen ere
            return 1; // yon bagay mal pase si li egzekite sa
    }
    csv_fini(&p, tretman_chan, tretman_liyn, &data); //finalize lekti done a
    fclose(fp);
    free(fichier);
    return 0;
}

char * antet_kliyan() {
    return "\"ID_client\",\"nom\",\"type\",\"no\",\"rue\",\"ville\",\"departement\",\"telephone\"";
}

char * liyn_kliyan(void * done) {
    Kliyan * kliyan = done;
    char * buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%s\",\"%c\",\"%d\",\"%s\",\"%s\",\"%d\",\"%s\"",
             kliyan->id, 
             kliyan->non, 
             kliyan->tip == PARTICULIER ? 'P' : 'E', 
             kliyan->adres->no,
             kliyan->adres->ri,
             kliyan->adres->vil,
             kliyan->adres->depatman,
             kliyan->telefon);
    return buffer;
}

int ecrire_fichier(int type_donnees) {
    char *fichier; // sa pral stoke non fichye a
    char * (*antet)(); //fonksyon kap jenere antet fichye a
    char * (*liyn)(void *); //fonksyon kap jenere teks pou chak liyn
    switch (type_donnees) {
        // n'ap ba varyab la vale swivan ki lis nou deside ouve
        case MM_LIS_KLIYAN:
            fichier = FICHYE_KLIYAN;
            antet = antet_kliyan;
            liyn = liyn_kliyan;
            break;
        case MM_LIS_SIKISAL:
            fichier = FICHYE_SIKISAL;
            break;
        default:
            return 1;
    }
    // nap efase sak te la deja yo
    FILE *fp = fopen(fichier, "w");
    fprintf(fp, antet());
    Lis *lis = jwenn_lis(type_donnees);
    Mayon * mayon = lis->premye;
    while (mayon != NULL) {
        if (mayon->done != NULL) {
            char *text = liyn(mayon->done);
            fprintf(fp, text);
            free(text);
        }
        mayon = mayon->apre;
    }
    fclose(fp);
    return 1;
}

void charger_donnees(int type) {
    inisyalize_lis(&liste_clients, MM_LIS_KLIYAN); // nou kreye lis la
    inisyalize_lis(&liste_succursales, MM_LIS_SIKISAL); // nou kreye lis la
    charger_fichier(MM_LIS_KLIYAN); // nou ajoute done ki nan fichye an nan lis lan
    charger_fichier(MM_LIS_SIKISAL); // nou ajoute done ki nan fichye an nan lis lan
}

int afiche_ekran_sovgade(int type, TypePage paj_retou) {
    ScreenClear();
    afficher_en_tete("Sauvegarde");
    textcolor(WHITE);
    Lis * lis = jwenn_lis(type);
    int ekri = lis->chanje;
    if (!ekri) {
        afiche_alet("\n\tLes information n'ont pas ete modifiees", NOMAL);
        textcolor(WHITE);
        printf("\n\tForcer la sauvegarde? [(O)ui\\(N)on]: ");
        char chwa = getch();
        if (chwa == 'O' || chwa == 'o') {
            ekri = 1;
        }
    }
    if (ekri) {
        afiche_alet("\n\tSauvegarde du fichier...", AVETISMAN);
        ecrire_fichier(type);
        afiche_alet("\n\tFichier sauvegarde", SIKSE);
        textcolor(WHITE);
    }
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return paj_retou;
}


