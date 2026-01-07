#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"
#define file_Personaggi "pg.txt"
#define file_Oggetti "inventario.txt"

int main(){
    FILE *filePersonaggi = fopen(file_Personaggi, "r");
    if(filePersonaggi == NULL){
        printf("Errore nell'apertura del file dei personaggi!");
        return -1;
    }

    FILE *fileOggetti = fopen(file_Oggetti, "r");
    if(fileOggetti == NULL){
        printf("Errore nell'apertura del file degli oggetti!");
        return -1;
    }

    //inizializzo la lista di personaggi
    printf("\n\nPERSONAGGI\n\n");
    link head = NULL;
    head = leggi_personaggi(filePersonaggi);
    stampa_tutti_i_personaggi(head);
    printf("\n\n");


    //inizializzo vettore dinamico oggetti
    printf("OGGETTI\n\n");
    int num_oggetti;
    fscanf(fileOggetti, "%d", &num_oggetti);
    oggetto_t *oggetti = leggi_oggetti(fileOggetti, num_oggetti);
    stampa_tutti_gli_oggetti(oggetti, num_oggetti);
    printf("\n\n");

    
    //aggiungo due personaggi manualmente
    printf("AGGIUNGIAMO DUE PERSONAGGI MANUALMENTE\n\n");
    head = aggiungi_personaggio_manualmente(head); printf("\n");
    head = aggiungi_personaggio_manualmente(head); printf("\n");
    stampa_tutti_i_personaggi(head);
    printf("\n\n");


    //eliminazione personaggio
    printf("ELIMINIAMO UN PERSONAGGIO\n\n");
    elimina_personaggio(head, "PG0017"); printf("\n");
    stampa_tutti_i_personaggi(head);
    printf("\n\n");


    //aggiungiamo gli equipaggiamenti
    printf("AGGIUNGIAMO GLI EQUIPAGGIAMENTI\n\n");
    personaggio_t *p1 = cerca_personaggio(head, "PG0001");
    personaggio_t *p2 = cerca_personaggio(head, "PG0002");
    personaggio_t *p5 = cerca_personaggio(head, "PG0005");
    personaggio_t *p6 = cerca_personaggio(head, "PG0006");
    personaggio_t *p8 = cerca_personaggio(head, "PG0008");
    personaggio_t *p11 = cerca_personaggio(head, "PG0011");
    oggetto_t *ogg1 = cerca_oggetto(oggetti, "Pendragon", num_oggetti);
    oggetto_t *ogg2 = cerca_oggetto(oggetti, "Ametista", num_oggetti);
    oggetto_t *ogg3 = cerca_oggetto(oggetti, "Tempesta", num_oggetti);
    oggetto_t *ogg4 = cerca_oggetto(oggetti, "AmmazzaDraghi", num_oggetti);
    oggetto_t *ogg5 = cerca_oggetto(oggetti, "Excalibur", num_oggetti);
    oggetto_t *ogg6 = cerca_oggetto(oggetti, "MantoElfico", num_oggetti);
    oggetto_t *ogg7 = cerca_oggetto(oggetti, "TalismanoNero", num_oggetti);

    if(p1 != NULL){
        aggiungi_equipaggiamento(p1, ogg1);
        aggiungi_equipaggiamento(p1, ogg3);
        aggiungi_equipaggiamento(p1, ogg5);
    }else printf("Il personaggio p1 non esiste!");

    if(p2 != NULL){
        aggiungi_equipaggiamento(p2, ogg2);
    }else printf("Il personaggio p2 non esiste!");

    if(p5 != NULL){
        aggiungi_equipaggiamento(p5, ogg1);
        aggiungi_equipaggiamento(p5, ogg3);
        aggiungi_equipaggiamento(p5, ogg4);
        aggiungi_equipaggiamento(p5, ogg6);
        aggiungi_equipaggiamento(p5, ogg7);
    }else printf("Il personaggio p5 non esiste!");

    if(p6 != NULL){
        aggiungi_equipaggiamento(p6, ogg6);
        aggiungi_equipaggiamento(p6, ogg7);
    }else printf("Il personaggio p6 non esiste!");

    stampa_tutti_i_personaggi(head);
    printf("\n\n");
}