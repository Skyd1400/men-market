//
// Created by Hash Skyd on 4/10/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Maket.h"
#include "data.h"
#include "lib/csv.h"


Liste liste_succursales;
Liste liste_produits;
Liste liste_produits_succursales;
Liste liste_clients;
Liste liste_ventes;
Liste liste_details_ventes;


#define T_TAMPON 1024

Liste *trouver_liste(int type)
{
    switch (type)
    {
        case MM_LISTE_SUCCURSALES:
            return &liste_succursales;
        case MM_LISTE_PRODUITS:
            return &liste_produits;
        case MM_LISTE_PRODUITS_SUCCURSALES:
            return &liste_produits_succursales;
        case MM_LISTE_CLIENTS:
            return &liste_clients;
        case MM_LISTE_VENTES:
            return &liste_ventes;
        case MM_LISTE_DETAILS_VENTES:
            return &liste_details_ventes;
        default:
            return NULL;
    }
}

int get_data_id(int type, void *data)
{
    if (data == NULL) return -1;
    switch (type)
    {
        case MM_LISTE_SUCCURSALES:
            return ((Surcusale *) data)->id;
        case MM_LISTE_PRODUITS:
            return ((Produit *) data)->code;
        case MM_LISTE_PRODUITS_SUCCURSALES:
            return ((ProduitSurcusale *) data)->id;
        case MM_LISTE_CLIENTS:
            return ((Client *) data)->id;
        case MM_LISTE_VENTES:
            return ((Vente *) data)->id;
        case MM_LISTE_DETAILS_VENTES:
            return ((DetailsVente *) data)->id;
        default:
            return -1;
    }
}

int ajouter_a_liste(Liste *liste, void *data)
{
    int result = -1;
    if (liste == NULL || data == NULL) return result;
    // Creer un nouveau noeud
    Noeud *temp = malloc(sizeof(Noeud));
    // Enregistrer la charge utile
    temp->data = data;
    // Il sera toujours place a la fin de la liste
    temp->precedent = liste->dernier; // pour trouver le noeud precedent a partir de ce noeud
    temp->suivant = NULL; // Il n'y a rien apres
    if (temp->precedent != NULL) temp->precedent->suivant = temp; // Pour trouver ce noeud a partir du precedent
    // Le prochain id sera toujours plus grand que le plus grand des donnees enregistrees
    int data_id = get_data_id(liste->type, data);
    if (data_id >= liste->id_suivant) liste->id_suivant = data_id + 1;
    // on peut l'ajouter a la liste maintenant
    liste->dernier = temp;
    //Premier element? ajouter le aussi au debut
    if (liste->nombre == 0) liste->premier = temp;
    liste->nombre++;
    result = 1;
    return result;
}

void *trouver_dans_la_liste(Liste *liste, int id)
{
    // La liste est vide?
    if (liste->nombre == 0) return NULL;
    Noeud *temp = liste->premier;
    do
    {
        // On a trouve?
        if (temp->data != NULL && get_data_id(liste->type, temp->data) == id) return temp->data;
        // Non, prochain element
        temp = temp->suivant;
    } while (temp != NULL);
    // On n'a rien trouve
    return NULL;
}

int retirer_de_la_Liste(Liste *liste, int id, int effacer)
{
    Noeud *a_eff = trouver_dans_la_liste(liste, id);
    if (a_eff != NULL)
    {
        if (a_eff->precedent) a_eff->precedent->suivant = a_eff->suivant;
        if (a_eff->suivant) a_eff->suivant->precedent = a_eff->precedent;
        if (effacer)
        {
            free(a_eff->data);
            free(a_eff);
        }
        liste->nombre--;
        return 1;
    }
    return -1;
}

void init_liste(Liste *liste, int type)
{
    if (liste == NULL) liste = malloc(sizeof(Liste));
    liste->nombre = 0;
    liste->id_suivant = 0;
    liste->premier = liste->dernier = NULL;
}

typedef struct parse_data
{
    int data_type; // tip lis nap trete
    void *temp; //adres done ki pou liyn nap trete a
    int c_ligne; // nimewo liyn nou ye a
    int c_champ; // nimewo kolon nou ye kounya
} parse_data;

void cb1(void *s, size_t len, void *data)
{
    parse_data *p_data = ((parse_data *) data);
    if (p_data->c_ligne > 0 && p_data->temp != NULL)
    { // sote premye liyn nan e asire ke done an egziste pou liyn nan
        if (p_data->data_type == MM_LISTE_CLIENTS)
        {
            // Se nan fichye kliyan an nou ye
            Client *client = p_data->temp; // chanjman tip otomatik
            switch (p_data->c_champ)
            {
                case 0: //Champ ID
                    client->id = atoi(s);
                    break;
            }
        }
    }
    printf("%s\n", s);
    p_data->c_champ++; // stoke nimewo kolon kap swiv

}

void cb2(int c, void *data)
{
    parse_data *p_data = ((parse_data *) data);
    p_data->c_ligne++;
    printf("Nouveau ligne : %d\n", c);
    if (p_data->c_ligne > 0)
    {
        Liste *liste; // li pral stoke adres lis nap trete
        int t; //lap stoke tay yon eleman nan lis la
        switch (p_data->data_type)
        { // mete vale pou de varyab yo swivan lis nou deside trete a
            case MM_LISTE_CLIENTS:
                liste = &liste_clients;
                t = sizeof(Client);
        }
        if (p_data->temp != NULL)
        {
            // nou te gentan gen yon eleman nou tap trete deja
            ajouter_a_liste(liste, p_data->temp);
        }
        // nou kreye yon nouvo eleman pou nouvo liyn
        p_data->temp = malloc(t);

        p_data->c_champ = 0;
    }
}

int charger_fichier(int type_donnees)
{
    char *fichier;
    switch (type_donnees)
    {
        case MM_LISTE_CLIENTS:
            fichier = FICHIER_CLIENTS;
            break;
        default:
            return 1;
    }
    FILE *fp = fopen(fichier, "r");
    if (!fp)
    {
        fp = fopen(fichier, "w");
        fclose(fp);
        return 1;
    }
    struct csv_parser p;
    size_t r;
    char buf[T_TAMPON];
    parse_data data = {type_donnees, NULL, 0, 0};
    csv_init(&p, CSV_APPEND_NULL);
    while ((r = fread(buf, 1, T_TAMPON, fp)) > 0)
    { // li yon moso nan fichye
        if (csv_parse(&p, buf, r, cb1, cb2, &data) != r) //trete moso ou li a e verifye ke pa gen ere
            return 1;
    }
    csv_fini(&p, cb1, cb2, &data); //finalize lekti done a
    return 0;
}

void charger_donnees(int type)
{
    init_liste(&liste_clients, MM_LISTE_CLIENTS);
    charger_fichier(MM_LISTE_CLIENTS);
}


