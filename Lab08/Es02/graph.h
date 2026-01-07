#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"

typedef struct{
    char *v;
    char *w;
    int peso;
}edge;

typedef struct graph *GRAPH;
GRAPH GRAPHinit(int V);
GRAPH GRAPHinitdaFile(char *filename);
void GRAPHload(GRAPH G, char *filename);
void GRAPHgenerateADJlist(GRAPH G);
void GRAPHfree(GRAPH G);
void GRAPH_STprint(GRAPH G);
void GRAPHedges(GRAPH G);
void GRAPHprintEdges(GRAPH G);
void GRAPHprintMat(GRAPH G);
void GRAPHadiacence(GRAPH G, char *nome1, char *nome2, char *nome3);
void GRAPHprintlistADJ(GRAPH G);