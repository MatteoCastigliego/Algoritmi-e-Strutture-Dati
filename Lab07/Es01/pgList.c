#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pgList.h"

typedef struct node *link;

struct node{
    pg_t personaggio;
    link next;
};

typedef struct pgList_s{
    link head;
    int num_personaggi;
};

link newNode(pg_t personaggio, link next){
    link x = malloc(sizeof(*x));
    x->next = next;
    x->personaggio = personaggio;
    return x; 
}

pgList_t pgList_init(){
    pgList_t list = malloc(sizeof(*list));
    list->head = NULL;
    list->num_personaggi = 0;
    return list;
}

void pgList_free(pgList_t pgList){
    link x = pgList->head, w;
    while(x != NULL){
        w = x->next;
        free(x);
        x = w;
    }
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    if(fp == NULL) return;

    pg_t pers;
    fscanf(fp, "%s %s %s", pers.cod, pers.nome, pers.classe);
    stat_read(fp, &pers.b_stat);
    pers.equip = equipArray_init();
    pgList_insert(pgList, pers);
    
}

void pgList_insert(pgList_t pgList, pg_t pg){
    if(pgList->head == NULL){
        pgList->head = newNode(pg, pgList->head);
    }else{
        link x;
        for(x = pgList->head; x->next != NULL; x = x->next);
        x->next = newNode(pg, NULL);
    }

    pgList->num_personaggi++;

    return;
}

void pgList_remove(pgList_t pgList, char *cod){
    if(pgList->head == NULL){
        printf("La lista è vuota!");
        return;
    }
    link x, p;
    for(x = pgList->head, p = NULL; x != NULL; p = x, x = x->next){
        if(x == pgList->head && strcmp(cod, x->personaggio.cod) == 0){
            pgList->head = pgList->head->next;
            pgList->num_personaggi--;
            free(x);
        }else{
            if(strcmp(cod, x->personaggio.cod) == 0){
                p->next = x->next;
                pgList->num_personaggi--;
                free(x);
            }
        }
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char *cod){
    link x;
    for(x = pgList->head; x != NULL; x = x->next){
        if(strcmp(cod, x->personaggio.cod) == 0){
            return &x->personaggio;
        }
    }
    return NULL;
}
