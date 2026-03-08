#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un BST (tipo ADT BST). 
Si scriva una funzione che duplichi il BST, cioè generi un secondo BST con lo stesso contenuto del primo. 
Si supponga di poter utilizzare una funzione

Item ItemDup(Item i);

per generare un duplicato (una copia) di un dato Item.

*/
typedef Item;
typedef struct bst *BST;
typedef struct node *link;
struct node{
    Item val;
    link left;
    link right;
};
struct bst{
    link root;
};

BST BstDup (BST b) {
    BST new_bst = malloc(sizeof(struct bst));
    new_bst->root = duplica_bst(b->root);
    return new_bst;
}

link duplica_bst(link root){
    if(root == NULL) return NULL;
    link h = NEWnode(ItemDup(root->val));

    h->left = duplica_bst(root->left);
    h->right = duplica_bst(root->right);
    return h;
}

link NEWnode(Item val){
    link x = malloc(sizeof(struct node));
    x->val = val;
    x->left = NULL;
    x->right = NULL;
    return x;
}

 

 




