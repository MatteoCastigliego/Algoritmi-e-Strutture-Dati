#include "es2.h"

//E’ dato un BST avente come valori delle stringhe, che fungono anche da chiave di ricerca. 
//Si scriva una funzione che determini la foglia a profonditá massima MAXF (in caso di uguaglianza, si selezioni la foglia con chiave maggiore). 
//La funzione stampi a ritroso (quindi da foglia a radice) le chiavi sul cammino che connette la foglia MAXF alla radice. 
//Il prototipo della funzione deve essere:

void BSTprintDeepest(BST b);

typedef struct node *link;
struct node{
    char *stringa;
    link left;
    link right;
};

struct bst{
    link root;
};

 
//Si richiede, oltre alla funzione, la definizione del tipo BST (ADT di prima classe) e del tipo usato per il nodo.

void BSTprintDeepest(BST b){
    int massima_profondita = -1;
    link nodo_max = NULL;
    trova_massima_profondita(b->root, 0, &massima_profondita, &nodo_max);
    stampa_percorso(b->root, nodo_max);
}

void trova_massima_profondita(link h, int prof, int *max_prof, link *max){
    if(h == NULL) return;
    if(prof > *max_prof){
        *max_prof = prof;
        *max = h;
    }
    if(prof == *max_prof && strcmp(h->stringa, (*max)->stringa) > 0){
        *max = h;
    }
    trova_massima_profondita(h->left, prof+1, max_prof, max);
    trova_massima_profondita(h->right, prof+1, max_prof, max);
}

void stampa_percorso(link root, link h){
    if(strcmp(root->stringa, h->stringa) > 0){
        stampa_percorso(root->left, h);
    }
    if(strcmp(root->stringa, h->stringa) < 0){
        stampa_percorso(root->right, h);
    }
    printf("%s", root->stringa);
    return;
}
