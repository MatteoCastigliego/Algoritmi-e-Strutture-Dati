#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* dichiarazione dei puntatori */
typedef struct nodo *link;
typedef int Key;
typedef struct bst *BST;


/* prototipi di funzione utilizzati */
BST BSTinit();
link NEWnode(Key val, link l, link r);
link inserisci_in_bst(link h, Key k);
void BSTinsert(BST b, Key k);
int KEYcmp(Key a, Key b);
Key KEYget(Key *k);

int presente(link root, Key k);
link trova_antenato_comune(link h, Key k1, Key k2);
int calcola_nodi(link h, Key k);
int BSTcountBetween(BST b, Key k1, Key k2);