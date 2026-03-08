#include <stdio.h>
#include <stdlib.h>

/*

È dato un BST avente come valori e chiavi delle stringhe. 
Si scriva una funzione che determini il cammino radice-foglia contenente il massimo numero di nodi aventi 2 figli (non nulli/vuoti). 
La funzione stampi il cammino e ne ritorni la lunghezza. Nel caso di più cammini di lunghezza massima la scelta è arbitraria. 
La funzione abbia prototipo:

int BSTprintMax2(BST b); 

Si richiede, oltre alla funzione, la definizione del tipo BST e del tipo usato per il nodo.

*/

typedef struct node *link;
struct node{
    char *stringa;
    link left;
    link right;
};

typedef struct bst *BST;
struct bst{
    link root;
};

int BSTprintMax2(BST b); 

int BSTprintMax2(BST b){
    link nodo = NULL;
    int max_len_camm = 0;
    trova_cammino(b->root, &nodo, &max_len_camm, 0);
    stampa_percorso(b->root, nodo);
    return max_len_camm;
}

void trova_cammino(link root, link *nodo, int *max_len_camm, int act_camm){
    if(root->left == NULL || root->right == NULL) return;
    if(act_camm > *max_len_camm){
        *max_len_camm = act_camm;
        *nodo = root;
    }

    trova_cammino(root->left, nodo, max_len_camm, act_camm+1);
    trova_cammino(root->right, nodo, max_len_camm, act_camm+1);
}

void stampa_percorso(link h, link nodo){
    printf("%s", h->stringa);
    if(KEYcompare(h->stringa, nodo->stringa) > 0){
        stampa_percorso(h->left, nodo);
    }else if(KEYcompare(h->stringa, nodo->stringa) < 0){
        stampa_percorso(h->right, nodo);
    }
    return;
}