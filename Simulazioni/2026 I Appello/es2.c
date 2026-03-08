#include "es2.h"

/*

È dato un tipo BST (ADT di prima classe). Si scriva una funzione che, dato un BST b, e due chiavi k1 e k2,
conti i nodi compresi tra le due chiavi (escluse dal conteggio) verificando anche se le due chiavi siano
presenti. La funzione, avente prototipo

int BSTcountBetween(BST b, Key k1, Key k2);

ritorni come risultato il conteggio, oppure -1 se una o entrambe le chiavi non sono presenti.

Attenzione: è preferibile (se ne terrà conto in fase di valutazione) una soluzione in grado di evitare la visita di
parti dell’albero sicuramente da non conteggiare.

*/

struct nodo{
    Key val;
    link left;
    link right;
};

struct bst{
    link root;
};


int BSTcountBetween(BST b, Key k1, Key k2)
{
    if (!presente(b->root, k1) || !presente(b->root, k2))
        return -1;
    link antenato_comune = trova_antenato_comune(b->root, k1, k2);
    int d1 = calcola_nodi(antenato_comune, k1);
    int d2 = calcola_nodi(antenato_comune, k2);
    return (d1 + d2 - 1); // sottraggo 1 perchè la il nodo comune viene contato 2 volte, prima in d1 e poi d2
}

int presente(link root, Key k)
{
    if (root == NULL)
        return 0;
    if (KEYcmp(KEYget(&root->val), k) > 0)
        return presente(root->left, k);
    else if (KEYcmp(KEYget(&root->val), k) < 0)
        return presente(root->right, k);
    else
        return 1;
}

link trova_antenato_comune(link h, Key k1, Key k2)
{
    if (h == NULL)
        return NULL;
    if (((KEYcmp(KEYget(&h->val), k1) < 0) && KEYcmp(KEYget(&h->val), k2) < 0))
        return trova_antenato_comune(h->right, k1, k2);
    else if (((KEYcmp(KEYget(&h->val), k1) > 0) && KEYcmp(KEYget(&h->val), k2) > 0))
        return trova_antenato_comune(h->left, k1, k2);
    else
        return h;
}

int calcola_nodi(link h, Key k)
{
    /* ometto i controlli perchè h non sarà mai NULL essendo un nodo del BST; k sicuro esiste altrimenti il
    programma non arriverebbe proprio a questo punto*/
    if (KEYcmp(KEYget(&h->val), k) == 0)
        return 0;
    else if (KEYcmp(KEYget(&h->val), k) > 0)
        return calcola_nodi(h->left, k) + 1;
    else
        return calcola_nodi(h->right, k) + 1;
}

int KEYcmp(Key a, Key b){
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

Key KEYget(Key *k){
    return *k;
}


BST BSTinit()
{
    BST b = malloc(sizeof(*b));
    if (b == NULL)
        return NULL;
    b->root = NULL;
    return b;
}

link NEWnode(Key val, link l, link r)
{
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->left = l;
    x->right = r;
    return x;
}

void BSTinsert(BST b, Key k)
{
    b->root = inserisci_in_bst(b->root, k);
}

link inserisci_in_bst(link h, Key k)
{
    if (h == NULL)
        return NEWnode(k, NULL, NULL);

    if (KEYcmp(k, h->val) < 0)
        h->left = inserisci_in_bst(h->left, k);
    else if (KEYcmp(k, h->val) > 0)
        h->right = inserisci_in_bst(h->right, k);
    return h;
}


int main()
{
    BST b = BSTinit();

    int nodi[] = {25, 15, 40, 10, 20, 33, 45, 3, 12, 30, 35, 50, 27, 31};
    int num_nodi = sizeof(nodi) / sizeof(int);

    for (int i = 0; i < num_nodi; i++)
        BSTinsert(b, nodi[i]);

    Key k1 = 10;
    Key k2 = 50;

    int risultato = BSTcountBetween(b, k1, k2);

    if (risultato == -1)
        printf("Una o entrambe le chiavi non sono presenti\n");
    else
        printf("Tra %d e %d ci sono %d nodi\n", k1, k2, risultato);

    return 0;
}
