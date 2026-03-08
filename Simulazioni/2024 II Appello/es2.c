#include <stdio.h>
#include <stdlib.h>

/*
Sia dato un HEAP, compatibile con quanto visto a lezione (ADT di prima classe per l'HEAP, con priorità inclusa nell'ITEM).
Si scriva una funzione HEAPtoBT che generi un albero binario (quindi realizzato mediante struct ricorsive allocate dinamicamente) 
equivalente (isomorfo e con contenuto identico) all’HEAP. Il prototipo della funzione sia:

BT HEAPtoBT(HEAP h).

Si scriva poi la funzione avente prototipo

Item BTextractLast(BT bt); 

La funzione cancella dall’albero binario l’ultima foglia (quella che nell’heap era in posizione heapsize-1) e ne ritorna il contenuto.

E' richiesta la definizione dei tipi HEAP e BT (come ATD di prima classe, con wrapper contenente i campi root, puntatore alla radice, e size, dimensione dell’albero), 
oltre che del nodo dell’albero binario.

*/
typedef struct{
    int val;
    int priority;
}Item;

typedef struct node *link;
struct node{
    Item val;
    link left;
    link right;
};

typedef struct heap *HEAP;
struct heap{
    Item *heap_vett;
    int heapsize;
};

typedef struct bt *BT;
struct bt{
    link root;
    int size;
};

BT HEAPtoBT(HEAP h);
Item BTextractLast(BT bt); 

BT HEAPtoBT(HEAP h){
    BT nuovo_albero = malloc(sizeof(struct bt));
    nuovo_albero->root = costruisci_albero(h, 0);
    nuovo_albero->size = h->heapsize;
    return nuovo_albero;
}

Item BTextractLast(BT bt){
    Item max;
    estrai_massimo(bt->root, bt->size, 0, &max);
    bt->size--;
    return max;
}

link costruisci_albero(HEAP h, int index){
    if(index >= h->heapsize) return NULL;
    link nuovo_nodo = NEWnode(h->heap_vett[index]);

    nuovo_nodo->left = costruisci_albero(h, 2*index+1);
    nuovo_nodo->right = costruisci_albero(h, 2*index+2);
    return nuovo_nodo;
}

Item estrai_massimo(link root, int dim, int index, Item *max){
    if(root == NULL) return;
    if(index == (dim-1)){
        *max = root->val;
        free(root);
    }else{
        estrai_massimo(root->left, dim, 2*index+1, max);
        estrai_massimo(root->right, dim, 2*index+2, max);
    }
}

link NEWnode(Item val){
    link x = malloc(sizeof(*x));
    x->val = val;
    x->right = NULL;
    x->left = NULL;
    return x;
}
