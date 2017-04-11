//
// Created by Hash Skyd on 4/5/2017.
//

#ifndef MEN_MAKET_MAKET_H
#define MEN_MAKET_MAKET_H

#include "lib/conio2.h"

// DEBUT Specification

typedef enum {
    EN_VENTE,
    EXCLUS,
    NON_DISPO
} StatutProduit;

typedef struct {
    int no;
    char* rue;
    char* ville;
    char* departement;
} Adresse;

typedef struct {
    int id;
    char *desc;
    Adresse* adresse;
    char* responsable;
    char* telephone;
} Surcusale;

typedef struct {
    int code;
    char* desc;
    int quantite;
    int prix_revient_unit;
    int prix_vente_unit;
    int stock_securite;
    StatutProduit statut;
} Produit;

typedef struct {
    int id;
    Produit* produit;
    Surcusale* surcusale;
    int quantite_min;
    int quantite_dispo;
    int quantite_max;
} ProduitSurcusale;

typedef enum {
    PARTICULIER,
    ENTREPRISE
} TypeClient;

typedef struct {
    int id;
    char* nom;
    TypeClient type;
    Adresse* adresse;
    char* telephone;
} Client;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;


typedef struct {
    int id;
    Client* client;
    Surcusale* surcusale;
    Date* date;
} Vente;

typedef struct {
    int id;
    Vente* vente;
    Produit *produit;
    int quantite_article;
    int prix_unit;
} DetailsVente;

// FIN SPECIFICATION

// DEBUT INTERFACE

typedef enum {
    MM_ACCUEIL,
    MM_TEST_DONNEES,
    MM_SORTIE
} TypePage;

typedef struct {
    int  (*id)();
    int  (*afficher)();
} Page;

// FIN INTERFACE

// DEBUT DONNEE

enum TypeListe {
    MM_LISTE_SUCCURSALES,
    MM_LISTE_PRODUITS,
    MM_LISTE_PRODUITS_SUCCURSALES,
    MM_LISTE_CLIENTS,
    MM_LISTE_VENTES,
    MM_LISTE_DETAILS_VENTES,
};

typedef struct Noeud {
    void *data;
    struct Noeud *precedent;
    struct Noeud *suivant;
} Noeud;

typedef struct Liste {
    int nombre;
    long long id_suivant;
    Noeud *premier;
    Noeud *dernier;
    enum TypeListe type;
} Liste;

#define FICHIER_CLIENTS "clients.dat"

#endif //MEN_MAKET_MAKET_H
