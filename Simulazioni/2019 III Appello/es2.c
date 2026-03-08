#include <stdio.h>
#include <stdlib.h>

/*

Una lista linkata, accessibile mediante il puntatore head1 alla testa, contiene una sequenza di caratteri alfanumerici. 
Si definisca il tipo link/nodo utilizzati e scriva una funzione C che generi una seconda lista, 
accessibile mediante il puntatore head2 alla testa, in cui sono state eliminate le eventuali sottosequenze di elementi delimitati 
da coppie di parentesi tonde (aperta all’inizio della sequenza, chiusa alla fine della sequenza), 
sostituendole con un solo elemento asterisco “*”. 
Si assuma che la lista sia corretta, cioè che non possa contenere coppie di parentesi che si “intersecano” e che per ogni parentesi aperta
esista una parentesi chiusa. Il prototipo della funzione sia:

link purgeList(link head1);

Esempio: data la lista
ab ( a c g ) b e ( ) a ( x x ) f
la lista di output sarà:
a b ( * ) b e ( * ) a ( * ) f

*/

typedef struct node *link;
struct node{
    char val;
    link next;
};

link purgeList(link head1);

link purgeList(link head1){
    link head2 = NULL, x;

    for(x = head1; x != NULL; x = x->next){
        if(x->val != '('){
            head2 = inserisci_in_lista(x->val, head2);
        }else{
            head2 = inserisci_in_lista(x->val, head2);
            while(x->val != ')'){
                x = x->next;
            }
            head2 = inserisci_in_lista('*', head2);
            head2 = inserisci_in_lista(x->val, head2);
        }
    }
    return head2;
}

link NEWnode(char val){
    link x = malloc(sizeof(*x));
    if(x == NULL) return NULL;
    x->val = val;
    x->next = NULL;
    return x;
}

link inserisci_in_lista(char val, link h){
    if(h == NULL){
        return NEWnode(val);
    }
    link x;
    for(x = h; x->next != NULL; x = x->next);
    x->next = NEWnode(val);
    return h;
}