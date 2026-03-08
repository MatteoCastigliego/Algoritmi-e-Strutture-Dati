#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un Grafo orientato realizzato con liste adiacenza (tipo ADT Graph). 
Si scriva una funzione GRAPHcheckSimmetry che, ricevuto come parametro un grafo, verifichi se il grafo è simmetrico e non contiene cappi 
(self-loop). 
Si ricorda che un grafo si dice simmetrico quando per ogni arco v-w esiste anche l’arco inverso w-v.
*/
 
typedef struct grafo *Graph;
typedef struct symbletable *ST;

typedef Item;
typedef struct node *link;
struct node{
    Item val;
    link next;
};
typedef struct list *LIST;
struct list{
    link head;
};
struct grafo{
    int num_vertici;
    ST table;
    LIST *list_adj;
};

int GRAPHcheckSimmetry (Graph g) {
    link x, p;
    for(int i = 0; i < g->num_vertici; i++){
        Item val = STgetval(g->table,i);
        for(x = g->list_adj[i]->head; x != NULL; x = x->next){
            if(KEYcompare(KEYget(&val), KEYget(&x->val)) == 0) return 0; // presenza di cappi
            int simmetrico = 0;
            // controllo simmetria
            for(p = g->list_adj[STgetindex(g->table, x->val)]->head; p != NULL; p = p->next){
                if(KEYcompare(KEYget(&val), KEYget(&p->val)) == 0 ) simmetrico = 1;
            }
            if(!simmetrico) return simmetrico;
        }
    }
    return 1;
}
