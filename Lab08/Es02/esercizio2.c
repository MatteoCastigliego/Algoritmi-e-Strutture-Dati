#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define filename "grafo.txt"

int main(){
    GRAPH G = GRAPHinitdaFile(filename);
    GRAPHload(G, filename);
    
    printf("STAMPA DI TUTTI I NOMI PRESENTI NEL FILE\n");
    GRAPH_STprint(G);
    printf("\n");

    printf("STAMPA LA COPPIA VERTICI->ARCHI\n");
    GRAPHprintEdges(G);
    printf("\n");

    printf("MATRICE DELLE ADIACENZE\n");
    GRAPHprintMat(G);
    printf("\n");

    GRAPHadiacence(G, "Alderaan", "Shiva", "Igni");
    printf("\n\n");

    printf("LISTA DELLE ADIACENZE\n");
    GRAPHgenerateADJlist(G);
    GRAPHprintlistADJ(G);
    printf("\n");
}