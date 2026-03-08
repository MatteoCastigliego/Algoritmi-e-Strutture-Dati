#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un BST (tipo ADT BST). 
Si scriva una funzione che, dato un BST b, e due chiavi k1 e k2, verifichi se le chiavi sono presenti in b. 
Se si, ritorni la distanza tra i nodi che le contengono: la distanza va intesa come lunghezza del cammino fra i due nodi nel BST 
visto come grafo non orientato aciclico. 
Se una o entrambe le chiavi non sono presenti la funzione ritorni -1.

*/

typedef Key;

typedef struct node *link;
struct node{
    Key val;
    link left;
    link right;
};

typedef struct bst *BST;
struct bst{
    link root;
};

int BSTdist(BST b, Key k1, Key k2);

 

int BSTdist(BST b, Key k1, Key k2){
    if(!presente(b->root, k1) || !presente(b->root, k2)) return -1;

    link antenato_comune = trova_antenato_comune(b->root, k1, k2);
    int d1 = 0, d2 = 0;
    calcola_distanza(antenato_comune, k1, &d1);
    calcola_distanza(antenato_comune, k2, &d2);

    return (d1+d2);
}

int presente(link root, Key val){
    if(root == NULL) return 0;
    if(KEYcompare(KEYget(&root->val), val) == 0) return 1;
    if(KEYcompare(KEYget(&root->val), val) > 0){
        return presente(root->left, val);
    }else{
        return presente(root->right, val);
    }
}

link trova_antenato_comune(link root, Key k1, Key k2){
    if(KEYcompare(KEYget(&root->val), k1) > 0 && KEYcompare(KEYget(&root->val), k2) > 0){
        return trova_antenato_comune(root->left, k1, k2);
    }else if(KEYcompare(KEYget(&root->val), k1) < 0 && KEYcompare(KEYget(&root->val), k2) < 0){
        return trova_antenato_comune(root->right, k1, k2);
    }else{
        return root;
    }
}

void calcola_distanza(link h, Key k, int *dist){
    if(KEYcompare(KEYget(&h->val), k) == 0) return;
    (*dist)++;
    if(KEYcompare(KEYget(&h->val), k) > 0){
        calcola_distanza(h->left, k, dist);
    }else{
        calcola_distanza(h->right, k, dist);
    }
}