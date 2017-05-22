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


typedef enum {
    Atibonit,
    Grandans,
    Nip,
    No,
    Nodes,
    Nodwes,
    Sant,
    Sid,
    Sides,
    Wes
} Depatman;

typedef struct {
    int no;
    char ri[50];
    char vil[25];
    Depatman depatman;
} Adres;

typedef struct {
    int id;
    char deskripsyon[100];
    Adres* adres;
    char responsab[50];
    char telefon[9];
} Sikisal;

typedef struct {
    int kod;
    char deskripsyon[101];
    int kantite;
    int pri_revyen_init;
    int pri_vant_inite;
    int stok_sekirite;
    StatiPwodwi stati;
} Pwodwi;

typedef struct {
    int id;
    int  pwodwi;
    int sikisal;
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
    int segond;
    int minit;
    int le;
    int jou;
    int mwa;
    int ane;
} Dat;


typedef struct {
    int id;
    int kliyan;
    int sikisal;
    Dat* dat;
} Vant;

typedef struct {
    int id;
    int vant;
    int pwodwi;
    int kantite_atik;
    int pri_inite;
} DetayVant;

// FEN SPESIFIKASYON

// KOMANSMAN ENTEFAS

typedef enum {
    MM_AKEY,
    MM_MENI_KLIYAN,
    MM_AJOU_KLIYAN,
    MM_MODIF_KLIYAN,
    MM_MENI_SIKISAL,
    MM_AJOU_SIKISAL,
    MM_MODIF_SIKISAL,
    MM_MENI_PWODWI,
    MM_AJOU_PWODWI,
    MM_MODIF_PWODWI,
    MM_AJOU_PWODWI_SIKISAL,
    MM_MODIF_PWODWI_SIKISAL,
    MM_APWOV_SIKISAL,
    MM_MENI_VANT,
    MM_AJOU_VANT,
    MM_RETOU_ATIK,
    MM_MENI_RAPO,
    MM_LIS_KLIYAN_PA_DEPATMAN,
    MM_LIS_VANT_AK_PWODWI,
    MM_LIS_KOMAND,
    MM_LIS_SIKISAL_POU_APWOVIZYONE,
    MM_SOVGAD,
    MM_SORTIE
} TipPaj;

typedef struct {
    int  id;
    int  (*afiche)();
} Paj;

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
    int chanje;
    int nonb;
    int id_swivan;
    Mayon *premye;
    Mayon *denye;
    enum TipLis tip;
} Lis;

#define FICHYE_KLIYAN "clients.dat"
#define FICHYE_SIKISAL "succursales.dat"
#define FICHYE_PWODWI "prod.dat"
#define FICHYE_PWODWI_SIKISAL "prod_succ.dat"
#define FICHYE_VANT "ventes.dat"
#define FICHYE_DETAY_VANT "det_ventes.dat"

#endif //MEN_MAKET_MAKET_H
