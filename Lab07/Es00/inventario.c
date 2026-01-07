#include "inventario.h"
#include <stdlib.h>
#include <string.h>

oggetto_t *leggi_oggetti(FILE *fin, int num_oggetti){
    char nome[50], tipologia[50];
    int hp, mp, atk, def, mag, spr;

    oggetto_t *oggetti = (oggetto_t*)malloc(num_oggetti*sizeof(oggetto_t));
    if(oggetti == NULL) return NULL;

    for(int i = 0; i < num_oggetti; i++){
        fscanf(fin, "%s %s %d %d %d %d %d %d", nome, tipologia, &hp, &mp, &atk, &def, &mag, &spr);
        oggetti[i].nome = strdup(nome);
        oggetti[i].tipologia = strdup(tipologia);
        oggetti[i].mod.hp = hp;
        oggetti[i].mod.mp = mp;
        oggetti[i].mod.atk = atk;
        oggetti[i].mod.def = def;
        oggetti[i].mod.mag = mag;
        oggetti[i].mod.spr = spr;
    }

    return oggetti;
}


oggetto_t *cerca_oggetto(oggetto_t *oggetti, char *nome, int num_oggetti){
    for(int i = 0; i < num_oggetti; i++){
        if(strcmp(oggetti[i].nome, nome) == 0){
            return &oggetti[i];
        }
    }
    return NULL;
}


void stampa_dettagli_oggetto(oggetto_t *oggetto){
    printf("%s %s %d %d %d %d %d %d\n", oggetto->nome, oggetto->tipologia, oggetto->mod.hp, oggetto->mod.mp, oggetto->mod.atk ,oggetto->mod.def, oggetto->mod.mag, oggetto->mod.spr);
}


void stampa_tutti_gli_oggetti(oggetto_t *oggetti, int num_oggetti){
    for(int i = 0; i < num_oggetti; i++){
        stampa_dettagli_oggetto(&oggetti[i]);
    }
}