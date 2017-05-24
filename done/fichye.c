//
// Created by Hash Skyd on 5/18/2017.
//

#include <stddef.h>
#include <stdlib.h>
#include <mem.h>
#include <stdio.h>
#include "fichye.h"
#include "strikti.h"
#include "../lib/csv.h"
#include "../util.h"
#include "../paj.h"
#include "../Maket.h"

typedef struct {
    int data_type; // tip lis nap trete
    void *temp; //adres done ki pou liyn nap trete a
    int c_ligne; // nimewo liyn nou ye a
    int c_champ; // nimewo kolon nou ye kounya
} DoneAnaliz;

void trete_chan_kliyan(const void *vale_chan, const DoneAnaliz *done_tretman) {
    Kliyan *client = done_tretman->temp; // chanjman tip otomatik
    int len_s = strlen(vale_chan);
    switch (done_tretman->c_champ) {
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
}

void trete_chan_sikisal(const void *vale_chan, const DoneAnaliz *done_tretman) {
    Sikisal *temp = done_tretman->temp;
    switch (done_tretman->c_champ) {
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
            strncpy(temp->responsab, vale_chan, 49);
            break;
        case 7: // Champ Telephone
            strncpy(temp->telefon, vale_chan, 8);
            temp->telefon[8] = 0;
            break;
    }
}

void trete_chan_pwodwi(void *vale_chan, DoneAnaliz *done_tretman) {
    Pwodwi *pwodwi = done_tretman->temp;
    switch (done_tretman->c_champ) {
        case 0:
            pwodwi->kod = atoi(vale_chan);
            break;
        case 1:
            strncpy(pwodwi->deskripsyon, vale_chan, 100);
            break;
        case 2:
            pwodwi->kantite = atoi(vale_chan);
            break;
        case 3:
            pwodwi->pri_revyen_init = atoi(vale_chan);
            break;
        case 4:
            pwodwi->pri_vant_inite = atoi(vale_chan);
            break;
        case 5:
            pwodwi->stok_sekirite = atoi(vale_chan);
            break;
        case 6:
            pwodwi->stati = (StatiPwodwi) atoi(vale_chan);
            break;
    }
}

void trete_chan_pwodwi_sikisal(void *vale_chan, DoneAnaliz *done_tretman) {
    PwodwiSikisal *pwodwi_sikisal = done_tretman->temp;
    switch (done_tretman->c_champ) {
        case 0:
            pwodwi_sikisal->pwodwi = atoi(vale_chan);
            break;
        case 1:
            pwodwi_sikisal->sikisal = atoi(vale_chan);
            break;
        case 2:
            pwodwi_sikisal->kantite_min = atoi(vale_chan);
            break;
        case 3:
            pwodwi_sikisal->kantite_dispo = atoi(vale_chan);
            break;
        case 4:
            pwodwi_sikisal->kantite_max = atoi(vale_chan);
            break;
    }
}

void trete_chan_vant(void *vale_chan, DoneAnaliz *data) {
    Vant *vant = data->temp;
    switch (data->c_champ) {
        case 0:
            vant->id = atoi(vale_chan);
            break;
        case 1:
            vant->kliyan = atoi(vale_chan);
            break;
        case 2:
            vant->sikisal = atoi(vale_chan);
            break;
        case 3:
            sscanf(vale_chan, "%d/%d/%d %d:%d:%d",
                   &vant->dat->jou,
                   &vant->dat->mwa,
                   &vant->dat->ane,
                   &vant->dat->le,
                   &vant->dat->minit,
                   &vant->dat->segond);
            break;
    }

}

void trete_chan_detay_vant(void *vale_chan, DoneAnaliz *data) {
    DetayVant *detayVant = data->temp;
    switch (data->c_champ) {
        case 0:
            detayVant->id = atoi(vale_chan);
            break;
        case 1:
            detayVant->vant = atoi(vale_chan);
            break;
        case 2:
            detayVant->pwodwi = atoi(vale_chan);
            break;
        case 3:
            detayVant->kantite_atik = atoi(vale_chan);
            break;
        case 4:
            detayVant->pri_inite = atoi(vale_chan);
            break;
    }
}

void tretman_chan(void *vale_chan, size_t tay_chan, void *done_analiz) {
    DoneAnaliz *p_data = ((DoneAnaliz *) done_analiz); // yon ti konvesyon
    if (p_data->c_ligne > 0 &&
        p_data->temp != NULL) { // sote premye liyn nan e asire ke espas pou stoke an egziste pou liyn nan
        switch (p_data->data_type) {
            case MM_LIS_KLIYAN:
                trete_chan_kliyan(vale_chan, p_data);
                break;
            case MM_LIS_SIKISAL:
                trete_chan_sikisal(vale_chan, p_data);
                break;
            case MM_LIS_PWODWI:
                trete_chan_pwodwi(vale_chan, p_data);
                break;
            case MM_LIS_PWODWI_SIKISAL:
                trete_chan_pwodwi_sikisal(vale_chan, p_data);
                break;
            case MM_LIS_VANT:
                trete_chan_vant(vale_chan, p_data);
                break;
            case MM_LIS_DETAY_VANT:
                trete_chan_detay_vant(vale_chan, p_data);
                break;
        }
    }
    p_data->c_champ++; // lot kolon apre a

}

void tretman_liyn(int c, void *data) {
    DoneAnaliz *p_data = ((DoneAnaliz *) data);
    p_data->c_ligne++;
    if (p_data->c_ligne > 0) // nou sote premye lin nan
    {
        Lis *lis; // li pral stoke adres lis nap trete
        int t; //lap stoke tay yon eleman nan lis la
        switch (p_data->data_type) { // mete vale pou de varyab yo swivan lis nou deside trete a
            case MM_LIS_KLIYAN:
                lis = jwenn_lis(MM_LIS_KLIYAN);
                t = sizeof(Kliyan);
                break;
            case MM_LIS_SIKISAL:
                lis = jwenn_lis(MM_LIS_SIKISAL);
                t = sizeof(Sikisal);
                break;
            case MM_LIS_PWODWI:
                lis = jwenn_lis(MM_LIS_PWODWI);
                t = sizeof(Pwodwi);
                break;
            case MM_LIS_PWODWI_SIKISAL:
                lis = jwenn_lis(MM_LIS_PWODWI_SIKISAL);
                t = sizeof(PwodwiSikisal);
                break;
            case MM_LIS_VANT:
                lis = jwenn_lis(MM_LIS_VANT);
                t = sizeof(Vant);
                break;
            case MM_LIS_DETAY_VANT:
                lis = jwenn_lis(MM_LIS_DETAY_VANT);
                t = sizeof(DetayVant);
                break;
        }
        if (p_data->temp != NULL) {
            // nou te gentan gen yon eleman nou tap trete deja
            mete_nan_lis(lis, p_data->temp); // nou jis ajoute li nan lis la kom yon lot eleman
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
        } else if (p_data->data_type == MM_LIS_VANT) {
            // N'ap ajoute kote pou resevwa dat la si se nan lis vant lan nou ye
            Dat *dat = malloc(sizeof(Dat));
            ((Vant *) temp)->dat = dat;
        }
        // nou nan fen lin ke nou tap trete a, e nou pral koumanse yon lot, donk nou prepare andwa pou
        // stoke done yo e nou remete nimewo chan nou ye a a zewo
        p_data->temp = temp;
        p_data->c_champ = 0;
    }
}

char *jwen_non_fichye(int tip_done) {
    char *fichier;
    switch (tip_done) {
        // n'ap ba varyab la vale swivan ki lis nou deside ouve
        case MM_LIS_KLIYAN:
            fichier = FICHYE_KLIYAN;
            break;
        case MM_LIS_SIKISAL:
            fichier = FICHYE_SIKISAL;
            break;
        case MM_LIS_PWODWI:
            fichier = FICHYE_PWODWI;
            break;
        case MM_LIS_PWODWI_SIKISAL:
            fichier = FICHYE_PWODWI_SIKISAL;
            break;
        case MM_LIS_VANT:
            fichier = FICHYE_VANT;
            break;
        case MM_LIS_DETAY_VANT:
            fichier = FICHYE_DETAY_VANT;
            break;
        default:
            fichier = NULL;
    }
    return fichier;
}

int li_fichye(int tip_done) {
    char *fichier; // sa pral stoke non fichye a
    fichier = jwen_non_fichye(tip_done);
    if (fichier == NULL)
        return 1;
    FILE *fp = fopen(fichier, "r");
    if (!fp) {
        // fichye a pa egziste kreye li epi soti paske li pa gen pyes done
        fp = fopen(fichier, "w");
        fclose(fp);
        return 1;
    }
    struct csv_parser p;
    size_t r; // konbyen oktet ki li
    char buf[1024]; // lap stoke blok nap trete a
    DoneAnaliz data = {tip_done, NULL, 0, 0}; // nou inisyalize done nou yo
    csv_init(&p, CSV_APPEND_NULL); // nou inisyalize bibliyotek nou an ak opsyon pou li temine chen yo pa zewo
    while ((r = fread(buf, 1, 1024, fp)) > 0) { // li yon moso nan fichye toutotan li pa rive nan fen
        if (csv_parse(&p, buf, r, tretman_chan, tretman_liyn, &data) != r) //trete moso ou li a e verifye ke pa gen ere
            return 1; // yon bagay mal pase si li egzekite sa
    }
    csv_fini(&p, tretman_chan, tretman_liyn, &data); //finalize lekti done a
    fclose(fp);
    free(fichier);
    return 0;
}

char *antet_kliyan() {
    return "\"ID_client\",\"nom\",\"type\",\"no\",\"rue\",\"ville\",\"departement\",\"telephone\"";
}

char *liyn_kliyan(void *done) {
    Kliyan *kliyan = done;
    char *buffer = malloc(1024);
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

char *antet_sikisal() {
    return "\"id\",\"description\",\"no\",\"rue\",\"ville\",\"departement\",\"responsable\",\"telephone\"";
}

char *liyn_sikisal(void *done) {
    Sikisal *sikisal = done;
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%s\",\"%d\",\"%s\",\"%s\",\"%d\",\"%s\",\"%s\"",
             sikisal->id,
             sikisal->deskripsyon,
             sikisal->adres->no,
             sikisal->adres->ri,
             sikisal->adres->vil,
             sikisal->adres->depatman,
             sikisal->responsab,
             sikisal->telefon);
    return buffer;
}

char *antet_pwodwi() {
    return "\"cod_prod\",\"desc_prod\",\"quantite\",\"prix_revient_unit\",\"prix_vente_unit\",\"stock_sec\",\"statut\"";
}

char *liyn_pwodwi(void *done) {
    Pwodwi *pwodwi = done;
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%s\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\"",
             pwodwi->kod,
             pwodwi->deskripsyon,
             pwodwi->kantite,
             pwodwi->pri_revyen_init,
             pwodwi->pri_vant_inite,
             pwodwi->stok_sekirite,
             pwodwi->stati);
    return buffer;
}

char *antet_pwodwi_sikisal() {
    return "\"prod_id\",\"succ_id\",\"qte_min\",\"qte_disp\",\"qte_max\"";
}

char *liyn_pwodwi_sikisal(void *done) {
    PwodwiSikisal *pwodwiSikisal = done;
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%d\",\"%d\",\"%d\",\"%d\"",
             pwodwiSikisal->pwodwi,
             pwodwiSikisal->sikisal,
             pwodwiSikisal->kantite_min,
             pwodwiSikisal->kantite_dispo,
             pwodwiSikisal->kantite_max);
    return buffer;
}

char *antet_vant() {
    return "\"id\",\"client_id\",\"succ_id\",\"date\"";
};

char *liyn_vant(void *done) {
    Vant *vant = done;
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%d\",\"%d\",\"%d/%d/%d %d:%d:%d\"",
             vant->id,
             vant->kliyan,
             vant->sikisal,
             vant->dat->jou,
             vant->dat->mwa,
             vant->dat->ane,
             vant->dat->le,
             vant->dat->minit,
             vant->dat->segond);
    return buffer;
};

char *antet_detay_vant() {
    return "\"id\",\"vente_id\",\"code_produit\",\"quantite\",\"prix_unit\"";
}

char *liyn_detay_vant(void *done) {
    DetayVant *detay_vant = done;
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "\n\"%d\",\"%d\",\"%d\",\"%d\",\"%d\"",
             detay_vant->id,
             detay_vant->vant,
             detay_vant->pwodwi,
             detay_vant->kantite_atik,
             detay_vant->pri_inite);
    return buffer;
};

int ekri_fichye(int type_donnees) {
    char *fichier = jwen_non_fichye(type_donnees); // sa pral stoke non fichye a
    char *(*antet)(); //fonksyon kap jenere antet fichye a
    char *(*liyn)(void *); //fonksyon kap jenere teks pou chak liyn
    switch (type_donnees) {
        // n'ap ba varyab la vale swivan ki lis nou deside ouve
        case MM_LIS_KLIYAN:
            antet = antet_kliyan;
            liyn = liyn_kliyan;
            break;
        case MM_LIS_SIKISAL:
            antet = antet_sikisal;
            liyn = liyn_sikisal;
            break;
        case MM_LIS_PWODWI:
            antet = antet_pwodwi;
            liyn = liyn_pwodwi;
            break;
        case MM_LIS_PWODWI_SIKISAL:
            antet = antet_pwodwi_sikisal;
            liyn = liyn_pwodwi_sikisal;
            break;
        case MM_LIS_VANT:
            antet = antet_vant;
            liyn = liyn_vant;
            break;
        case MM_LIS_DETAY_VANT:
            antet = antet_detay_vant;
            liyn = liyn_detay_vant;
            break;
        default:
            return 1;
    }
    // nap efase sak te la deja yo
    FILE *fp = fopen(fichier, "w");
    fprintf(fp, antet());
    Lis *lis = jwenn_lis(type_donnees);
    Mayon *mayon = lis->premye;
    while (mayon != NULL) {
        if (mayon->done != NULL) {
            char *text = liyn(mayon->done);
            fprintf(fp, text);
            free(text); // lew lwe fok ou remet
        }
        mayon = mayon->apre;
    }
    fclose(fp);
    return 1;
}

void chaje_done() {
    inisyalize_lis(jwenn_lis(MM_LIS_KLIYAN)); // nou kreye lis la
    inisyalize_lis(jwenn_lis(MM_LIS_SIKISAL)); // nou kreye lis la
    inisyalize_lis(jwenn_lis(MM_LIS_PWODWI)); // nou kreye lis la
    inisyalize_lis(jwenn_lis(MM_LIS_PWODWI_SIKISAL)); // nou kreye lis la
    inisyalize_lis(jwenn_lis(MM_LIS_VANT)); // nou kreye lis la
    inisyalize_lis(jwenn_lis(MM_LIS_DETAY_VANT)); // nou kreye lis la
    li_fichye(MM_LIS_KLIYAN); // nou ajoute done ki nan fichye an nan lis lan
    li_fichye(MM_LIS_SIKISAL); // nou ajoute done ki nan fichye an nan lis lan
    li_fichye(MM_LIS_PWODWI); // nou ajoute done ki nan fichye an nan lis lan
    li_fichye(MM_LIS_PWODWI_SIKISAL); // nou ajoute done ki nan fichye an nan lis lan
    li_fichye(MM_LIS_VANT); // nou ajoute done ki nan fichye an nan lis lan
    li_fichye(MM_LIS_DETAY_VANT); // nou ajoute done ki nan fichye an nan lis lan
}

int afiche_ekran_sovgade(int *type, int nonb, TipPaj paj_retou) {
    ScreenClear();
    afiche_antet("Sauvegarde");
    textcolor(WHITE);
    afiche_alet("\n\tSauvegarde du(es) fichier(s)...", AVETISMAN);
    for (int i = 0; i < nonb; i++) {
        ekri_fichye(type[i]);
    }
    afiche_alet("\n\tFichier(s) sauvegarde(s)", SIKSE);
    textcolor(WHITE);
    printf("\n\tAppuyer sur une touche  pour retourner au menu...");
    getch();
    return paj_retou;
}