#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un Grafo non orientato realizzato con liste adiacenza (tipo ADT Graph).  
Il grafo rappresenta delle relazioni di amicizia tra persone. 
Si scriva una funzione GRAPHfriendsOfFriends che, ricevuto come parametro un grafo e un vertice v 
(un intero, indice del vertice corrispondente), calcoli quanti sono gli amici di amici di v che non sono amici di v stesso. 
La funzione, oltre a calcolare il numero, stampi l’elenco delle persone conteggiate.

*/
 
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

typedef struct table *ST;
struct table{
    int n_persone;
    Item *val;
};

typedef struct grafo *Graph;
struct grafo{
    int num_persone;
    LIST *list_friends;
};

int GRAPHfriendsOfFriends (Graph g, int v) {
    // suppongo v come indice del vertice e della tabella di simboli
    link x, p;
    int cnt = 0;
    Item *vett = malloc(g->num_persone*sizeof(Item));

    for(x = g->list_friends[v]->head; x != NULL; x = x->next){
        int index_amico = STgetIndex(x->val);
        for(p = g->list_friends[index_amico]->head; p != NULL; p = p->next){
            if(not_amico(g->list_friends[v], p->val)){
                aggiungi_a_elenco(vett, &cnt, p->val);
            }
        }
    }
    for (int i = 0; i < cnt; i++){
        ITEMprint(&vett[i]);
    }

    return cnt;
}

int not_amico(LIST list, Item val){
    int not_amico = 1;
    for(link x = list->head; x != NULL; x = x->next){
        if(KEYcompare(KEYget(&x->val), val) == 0) not_amico = 0;
    }
    return not_amico;
}

void aggiungi_a_elenco(Item *vett, int *cnt, Item val){
    if(*cnt == 0){
        ITEMstore(vett[*cnt], val);
        (*cnt)++;
    }
    else {
        int presente = 0;
        for (int i = 0; i < *cnt; i++){
            if(KEYcompare(KEYget(&vett[i]), val) == 0) presente = 1;
        }
        if(presente == 0){
            ITEMstore(vett[*cnt], val);
            (*cnt)++;
        }
    }
}

