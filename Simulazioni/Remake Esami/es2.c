#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un BST (tipo ADT BST). 
Si scriva una funzione che duplichi il BST, cioè generi un secondo BST con lo stesso contenuto del primo. 
Si supponga di poter utilizzare una funzione

Item ItemDup(Item i);

per generare un duplicato (una copia) di un dato Item.

BST BstDup (BST b);

*/

typedef Item;

typedef struct node *link;
struct node{
    Item val;
    link left;
    link right;
};

typedef struct bst *BST;
struct bst{
    link root;
};

Item ItemDup(Item i);
BST BstDup (BST b);

BST BstDup (BST b){
    BST new_bst = malloc(sizeof(struct bst));
    new_bst->root = duplica_bst(b->root);
    return new_bst;
}

link duplica_bst(link root){
    if(root == NULL) return NULL;
    link x = NEWnode(ItemDup(root->val));

    x->left = duplica_bst(root->left);
    x->right = duplica_bst(root->right);
    return x;
}

link NEWnode(Item val){
    link x = malloc(sizeof(*x));
    if(x == NULL) return NULL;
    x->val = val;
    x->left = NULL;
    x->right = NULL;
    return x;
}