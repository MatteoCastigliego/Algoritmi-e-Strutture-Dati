#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un Grafo orientato realizzato con liste adiacenza (tipo ADT Graph). 
Si scriva una funzione GRAPHcheckSimmetry che, ricevuto come parametro un grafo, verifichi se il grafo è simmetrico e non contiene cappi 
(self-loop). Si ricorda che un grafo si dice simmetrico quando per ogni arco v-w esiste anche l’arco inverso w-v.

int GRAPHcheckSimmetry (Graph g);

*/

typedef Item;
typedef struct node *link;
struct node{
    Item val;
    link next;
};

typedef struct lista *LIST;
struct lista{
    link head;
};

typedef struct st *ST;
typedef struct grafo *Graph;
struct grafo{
    int num_vertici;
    LIST *lista_adj;
    ST st;
};


int GRAPHcheckSimmetry (Graph g);

int GRAPHcheckSimmetry (Graph g){
    link x, p;

    for(int i = 0; i < g->num_vertici; i++){
        for(x = g->lista_adj[i]->head; x != NULL; x = x->next){
            int index = STgetindex(g->st, x->val);
            int ok = 0;
            if(index == i) return 0; // cappio

            // simmetria
            for(p = g->lista_adj[index]->head; p != NULL; p = p->next){
                if(KEYcompare(KEYget(&x->val), KEYget(&p->val)) == 0){
                    ok = 1;
                    break;
                }
            }
            if(ok == 0) return 0;
        }
    }
    return 1;
}
