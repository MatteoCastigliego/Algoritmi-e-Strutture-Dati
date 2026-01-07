#include <stdio.h>
#include "inventario.h"
#include <stdlib.h>
#include <string.h>

typedef struct{
    int hp, mp, atk, def, mag, spr;
}statistiche_t;

typedef struct{
    char *codice;
    char *nome;
    char *classe;
    statistiche_t stat;
    int num_equipaggiamenti;
    oggetto_t *equipaggiamento;
}personaggio_t;

typedef struct node *link;

struct node{
    personaggio_t val;
    link next;
};

link newNode(personaggio_t pers, link next);
link leggi_personaggi(FILE *fin);
link inserisci_personaggio(link head, personaggio_t pers);
link elimina_personaggio(link head, char *codice);
personaggio_t *cerca_personaggio(link head, char *codice);
void stampa_tutti_i_personaggi(link head);
void stampa_informazioni_personaggio(personaggio_t *pers);
void aggiungi_equipaggiamento(personaggio_t *pers, oggetto_t *ogg);
void elimina_equipaggiamento(personaggio_t *pers, oggetto_t *ogg);
link aggiungi_personaggio_manualmente(link head);
void calcola_statistiche(personaggio_t *pers);

