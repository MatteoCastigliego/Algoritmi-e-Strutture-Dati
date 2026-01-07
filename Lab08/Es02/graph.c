#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct node *link;

struct node{
    int v;
    link next;
};

static link NEW(int v, link next);

struct graph{
    int V;
    int E;
    ST tab;
    int **mat;
    link *list;
};

link NEW(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

GRAPH GRAPHinit(int V){
    GRAPH G;
    G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->tab = STinit(V);
    G->mat = (int**)malloc(V*sizeof(int*));
    for(int i = 0; i < G->V; i++){
        G->mat[i] = calloc(G->V, sizeof(int));
    }
    G->list = malloc(V*sizeof(link));
    return G;
}

GRAPH GRAPHinitdaFile(char *filename){
    FILE *fin = fopen(filename, "r");
    if (fin == NULL){
        printf("Errore nell'apertura del file");
        return NULL;
    }
    ST temp_table = STinit(50);
    int peso;
    char buff1[30], buff2[30];
    while(fscanf(fin, "%s %*s %s %*s %d", buff1, buff2, &peso) == 3){
        STinsert(temp_table, buff1);
        STinsert(temp_table, buff2);
    }
    fclose(fin);
    GRAPH G = GRAPHinit(STcount(temp_table));

    for(int i = 0; i < STcount(temp_table); i++){
        STinsert(G->tab, STgetName(temp_table, i));
    }
    STfree(temp_table);
    return G;
}

void GRAPHload(GRAPH G, char *filename){
    FILE *fin = fopen(filename, "r");
    if (fin == NULL){
        printf("Errore nell'apertura del file");
        return;
    }
    char nome1[30], nome2[30];
    int peso, id1, id2;

    while(fscanf(fin, "%s %*s %s %*s %d", nome1, nome2, &peso) == 3){
        id1 = STgetIndex(G->tab, nome1);
        id2 = STgetIndex(G->tab, nome2);
        G->mat[id1][id2] = peso;
        G->mat[id2][id1] = peso;
        G->E++;
    }
}

void GRAPHgenerateADJlist(GRAPH G){
    for(int i = 0; i < G->V; i++){
        G->list[i] = NULL;
    }
    for(int i = 0; i < G->V; i++){
        for(int j = i+1; j < G->V; j++){
            if(G->mat[i][j] != 0){
                G->list[i] = NEW(j, G->list[i]);
                G->list[j] = NEW(i, G->list[j]);
            }
        }
    }
}

void GRAPHfree(GRAPH G){
    STfree(G->tab);
    for(int i = 0; i < G->V; i++){
        free(G->mat[i]);
        link x = G->list[i], t;
        while(x != NULL){
            t = x->next;
            free(x);
            x = t;
        }
    }
    free(G->mat);
    free(G->list);
    free(G);
}

void GRAPH_STprint(GRAPH G){
    STprint(G->tab);
}

void GRAPHedges(GRAPH G){
    edge *lista_archi = (edge*)malloc(G->V*G->V*sizeof(edge));
    int index = 0;
    char *nome1, *nome2;
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            if(G->mat[i][j] != 0){
                nome1 = STgetName(G->tab, i);
                nome2 = STgetName(G->tab, j);
                lista_archi[index].v = strdup(nome1);
                lista_archi[index].w = strdup(nome2);
                lista_archi[index].peso = G->mat[i][j];
                index++;
            }
        }
    }
}

void GRAPHprintEdges(GRAPH G){
    int num_elements = STcount(G->tab);
    for(int i = 0; i < num_elements; i++){
        printf("%s: ", STgetName(G->tab, i));
        for(int j = 0; j < num_elements; j++){
            //stampo direttamente i vicini perchè la ST è già ordinata in ordine alfabetico
            if(G->mat[i][j] != 0){
                printf("%s ", STgetName(G->tab, j));
            }
        }
        printf("\n");
    }
}

void GRAPHprintMat(GRAPH G){
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            printf("%d ", G->mat[i][j]);
        }
        printf("\n");
    }
}

void GRAPHadiacence(GRAPH G, char *nome1, char *nome2, char *nome3){
    int id1 = STgetIndex(G->tab, nome1);
    int id2 = STgetIndex(G->tab, nome2);
    int id3 = STgetIndex(G->tab, nome3);

    if(id1 == -1){
        printf("Il primo nome non esiste"); return;
    }
    if(id2 == -1){
        printf("Il secondo nome non esiste"); return;
    }
    if(id3 == -1){
        printf("Il terzo nome non esiste"); return;
    }

    int ok = 0;
    if(G->mat[id1][id2] != 0 && G->mat[id1][id3] != 0) ok++;
    if(G->mat[id2][id1] != 0 && G->mat[id2][id3] != 0) ok++;
    if(G->mat[id3][id1] != 0 && G->mat[id3][id2] != 0) ok++;

    if(ok == 3){
        printf("I vertici %s %s %s sono adiacenti a coppie!", nome1, nome2, nome3);
    }else{
        printf("I vertici %s %s %s non sono adiacenti a coppie", nome1, nome2, nome3);
    }
}

void GRAPHprintlistADJ(GRAPH G){
    for(int i = 0; i < G->V; i++){
        printf("%d: ", i);
        link h = G->list[i];
        while(h != NULL){
            printf("%d ", h->v);
            h = h->next;
        }
        printf("\n");
    }
}
