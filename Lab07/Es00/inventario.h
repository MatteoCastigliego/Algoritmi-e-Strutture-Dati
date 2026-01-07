#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int hp, mp, atk, def, mag, spr;
}modificatori_t;

typedef struct{
    char *nome;
    char *tipologia;
    modificatori_t mod;
}oggetto_t;

oggetto_t *leggi_oggetti(FILE *fin, int num_oggetti);
oggetto_t *cerca_oggetto(oggetto_t *oggetti, char *nome, int num_oggetti);
void stampa_dettagli_oggetto(oggetto_t *oggetto);
void stampa_tutti_gli_oggetti(oggetto_t *oggetti, int num_oggetti);