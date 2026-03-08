#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

È dato un ADT List,  in grado di rappresentare una lista (non ordinata) di stringhe (allocate dinamicamente).
Si completi la funzione listDeleteLonger che, data la lista e una lunghezza (un valore intero lmax),
elimini dalla lista le stringhe (e i relativi nodi) di lunghezza superiore a lmax.
La funzione ritorna un risultato intero, che rappresenta il numero di cancellazioni effettuate.
Completare il codice parziale utilizzando la numerazione riportata


typedef struct node {
  char *val;
  struct node *next;
} link;
...
int listDeleteLonger (List l, int lmax) {
    link x, p;
    int cnt=0;
    for(x=l->head, p=NULL; x!=NULL; <1> ) {
        if (strlen(<2>)) {
            <3> // bypass
            <4> // free
            <5> // other
    }else {
    <6>
        }
    }
return  cnt ;
}

<1> NULL

<2> (x->val) > lmax

<3> link tmp = x;
    if(p == NULL){
        l->head = x->next;
        x = x->next;
    }else{
        p->next = x->next;
        x = x->next;
    }

<4> free(tmp)

<5> cnt++;

<6> p = x;
    x = x->next;

*/

