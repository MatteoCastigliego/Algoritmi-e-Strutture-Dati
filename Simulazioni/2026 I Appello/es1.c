#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fin "es1.txt"
#define len 30

/*

È dato un tipo struct node (e il relativo puntatore link) adatti a rappresentare nodi e puntatori in lista
concatenata.

typedef struct node {
char *val;
struct node *next;
} *link;

Il campo val punta a una stringa di proprietà del nodo. È data una lista (realizzata con questo tipo di dato) di
stringhe, non ordinata e contenete eventuali dati ripetuti (anche più volte e non necessariamente contigui). Si
consideri quale esempio, la lista seguente

->”Roma”->”Milano”->”Palermo”->”Roma”->”Torino”->”Genova”->”Roma”->”Palermo”

Si realizzi la funzione avente prototipo

link removeDupl(link h);

in grado di rimuovere dalla lista gli elementi duplicati. Di ogni stringa replicata più di una volta va mantenuta
la prima istanza. I dati rimasti debbono conservare l’ordine originale. La lista precedentemente esemplificata,
diventerebbe

->”Roma”->”Milano”->”Palermo”->”Torino”->”Genova”

Attenzione: non va generata una nuova lista ma occorre ritornare il puntatore alla lista modificata.

*/

typedef struct node
{
    char *val;
    struct node *next;
} *link;

link removeDupl(link h)
{
    if (h == NULL)
        return NULL;
    link x, p, k;
    for (x = h; x != NULL; x = x->next)
    {
        for (p = x->next, k = x; p != NULL;)
        {
            if (strcmp(x->val, p->val) == 0)
            {
                link tmp = p;
                k->next = p->next;
                p = p->next;
                free(tmp->val);
                free(tmp);
            }
            else
            {
                k = p;
                p = p->next;
            }
        }
    }
    return h;
}

link NEWnode(char *s, link next)
{
    link n = malloc(sizeof(*n));
    if (n == NULL)
        return NULL;
    n->val = strdup(s);
    n->next = next;
    return n;
}

void stampa_lista(link h)
{
    link x;
    for (x = h; x != NULL; x = x->next)
        printf("-> %s ", x->val);
    printf("\n");
}

void free_lista(link h)
{
    while (h != NULL)
    {
        link tmp = h;
        h = h->next;
        free(tmp->val);
        free(tmp);
    }
}

int main(void)
{

    link h = NULL;
    char citta[len];
    FILE *filein = fopen(fin, "r");

    if (filein == NULL)
        return 0;
    while (fscanf(filein, "%s", citta) == 1)
        h = NEWnode(citta, h);

    printf("Lista originale:\n");
    stampa_lista(h);

    h = removeDupl(h);

    printf("\nLista senza duplicati:\n");
    stampa_lista(h);

    free_lista(h);
    return 0;
}
