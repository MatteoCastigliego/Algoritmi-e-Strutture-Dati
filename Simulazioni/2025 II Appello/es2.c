/*

È dato un BST (o albero binario, il problema è equivalente). 
Si scriva una funzione che verifichi se l’albero è bilanciato: si utilizzi come criterio di bilanciamento quello basato 
sulle dimensioni dei sotto-alberi. La funzione abbia prototipo:

int BSTisBalanced(BST b);

Si richiede, oltre alla funzione, la definizione del tipo BST e del tipo usato per il nodo. 
Si assuma che il nodo dell’albero NON sia stato esteso in modo da contenere la dimensione del relativo sotto-albero.

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct bst *BST;
typedef int Item;
typedef struct node *link;

struct node{
    Item val;
    link left;
    link right;
};

struct bst{
    link root;
};

int BSTisBalanced(BST b){
    int is_balanced = 1;
    verifica_bilanciamento(b->root, &is_balanced);
    return is_balanced;
}

int conta_nodi(link h){
    if (h == NULL)
        return 0;
    return conta_nodi(h->left) + conta_nodi(h->right) + 1;
}

void verifica_bilanciamento(link h, int *is_balanced){
    if (*is_balanced == 0 || h == NULL)
        return;
    int nodi_r = conta_nodi(h->right);
    int nodi_l = conta_nodi(h->left);
    if (abs(nodi_r - nodi_l) > 1){
        *is_balanced = 0;
         return;
    }
        
    verifica_bilanciamento(h->left, is_balanced);
    verifica_bilanciamento(h->right, is_balanced);
}
