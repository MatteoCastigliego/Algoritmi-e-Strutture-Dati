#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxC 30 
/*

Sia dato un albero binario T, cui si accede tramite il puntatore root alla radice. I nodi dell’albero
hanno come chiavi stringhe di lunghezza massima maxC. Si scriva una funzione C con prototipo

linkL tree2List(linkT root, int visit);

che visiti l'albero secondo la strategia specificata nel parametro visit (1: inorder, 2: preorder, 3:
postorder), memorizzando le chiavi in una lista concatenata, di cui ritorna il puntatore alla testa.

Si definiscano il nodo dell’albero e relativo puntatore (tipo linkT), il nodo della lista e il relativo
puntatore (tipo linkL). Si scriva esplicitamente la funzione di inserzione in lista senza fare uso di
funzioni di libreria.

*/

typedef struct node *linkL;
struct node{
    char stringa[maxC];
    linkL next;
};

typedef struct node2 *linkT;
struct node2{
    char stringa[maxC];
    linkT left;
    linkT right;
};

typedef struct bt *BT;
struct bt{
    linkT root;
};

linkL tree2List(linkT root, int visit);
void visita(BT b, int visit);



linkL tree2List(linkT root, int visit){
    linkL head = NULL;
    if(visit == 1){
        inorder(root, &head);
    }else if(visit == 2){
        preorder(root, &head);
    }else{
        postorder(root, &head);
    }
    return head;
}

void preorder(linkT root, linkL *head){
    if(root == NULL) return;
    inserisci_in_lista(root->stringa, head);
    preorder(root->left, head);
    preorder(root->right, head);
}

void inorder(linkT root, linkL *head){
    if(root == NULL) return;
    inorder(root->left, head);
    inserisci_in_lista(root->stringa, head);
    inorder(root->right, head);
}

void postorder(linkT root, linkL *head){
    if(root == NULL) return;
    postorder(root->left, head);
    postorder(root->right, head);
    inserisci_in_lista(root->stringa, head);
}

void inserisci_in_lista(char str[], linkL *head){
    if(*head == NULL){
        *head = NEWnode(str);
    }else{
        linkL p, h;
        for(h = *head, p = NULL; h != NULL; p = h, h = h->next);
        p->next = NEWnode(str);
        }        
    }
    

linkL NEWnode(char str[]){
    linkL x = malloc(sizeof(*x));
    strcpy(x->stringa, str);
    x->next = NULL;
    return x;
}
