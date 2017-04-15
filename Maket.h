//
// Created by Hash Skyd on 4/5/2017.
//

#ifndef MEN_MAKET_MAKET_H
#define MEN_MAKET_MAKET_H

#include "lib/conio2.h"

// KOMANSMAN SPESIFIKASYON

typedef enum {
    EN_VENTE,
    EXCLUS,
    NON_DISPO
} StatiPwodwi;

typedef struct {
    int no;
    char* ri;
    char* vil;
    char* depatman;
} Adres;

typedef struct {
    int id;
    char *deskripsyon;
    Adres* adres;
    char* responsab;
    char* telefon;
} Sikisal;

typedef struct {
    int kod;
    char* deskripsyon;
    int kantite;
    int pri_revant_init;
    int pri_vant_inite;
    int stok_sekirite;
    StatiPwodwi stati;
} Pwodwi;

typedef struct {
    int id;
    Pwodwi* pwodwi;
    Sikisal* sikisal;
    int kantite_min;
    int kantite_dispo;
    int kantite_max;
} PwodwiSikisal;

typedef enum {
    PARTICULIER,
    ENTREPRISE
} TipKliyan;

typedef struct {
    int id;
    char non[50];
    TipKliyan tip;
    Adres* adres;
    char telefon[9];
} Kliyan;

typedef struct {
    int jou;
    int mwa;
    int ane;
} Dat;


typedef struct {
    int id;
    Kliyan* kliyan;
    Sikisal* sikisal;
    Dat* dat;
} Vant;

typedef struct {
    int id;
    Vant* vant;
    Pwodwi *pwodwi;
    int kantite_atik;
    int pri_inite;
} DetayVant;

// FEN SPESIFIKASYON

// KOMANSMAN ENTEFAS

typedef enum {
    MM_ACCUEIL,
    MM_TEST_DONNEES,
    MM_SORTIE
} TypePage;

typedef struct {
    int  (*id)();
    int  (*afficher)();
} Page;

// FEN ENTEFAS

// KOMANSMAN DONE

enum TipLis {
    MM_LIS_SIKISAL,
    MM_LIS_PWODWI,
    MM_LIS_PWODWI_SIKISAL,
    MM_LIS_KLIYAN,
    MM_LIS_VANT,
    MM_LIS_DETAY_VANT,
};

typedef struct Mayon {
    void *done;
    struct Mayon *anvan;
    struct Mayon *apre;
} Mayon;

typedef struct {
    int nonb;
    long long id_swivan;
    Mayon *premye;
    Mayon *denye;
    enum TipLis tip;
} Lis;

#define FICHYE_KLIYAN "clients.dat"

#endif //MEN_MAKET_MAKET_H
