#include <stdio.h>
#include <stdlib.h>


// Sono dati due vettori di interi ordinati in modo crescente e privi di ripetizioni. 
// Si scriva una funzione che generi un vettore (allocato dinamicamente) contenente gli interi appartenenti 
// al primo vettore e non al secondo. La funzione deve essere chiamata come segue

// c = diffVett(a,na,b,nb,&nc);

 
// a e b sono i due vettori, na e nb il numero di dati che contengono; 
// c è il vettore risultato, allocato dinamicamente nella funzione, nc il numero di interi nel vettore risultato.

// Si richiede di realizzare (SOLO) la funzione diffVett (quindi non del programma chiamante)

int *diffVett(int *a, int na, int *b, int nb, int *nc);

int *diffVett(int *a, int na, int *b, int nb, int *nc){
    int *c = malloc((na+nb)*sizeof(int));
    if(c == NULL){
        printf("Errore allocazione");
        return NULL;
    }
    int non_presente;
    for(int i = 0; i < na; i++){
        non_presente = 1;
        for(int j = 0; j < nb; j++){
            if(a[i] == b[j]) non_presente = 0;
        }
        if(non_presente){
            c[(*nc)] = a[i];
            (*nc)++;
        }
    }
    c = realloc(c, (*nc)*sizeof(int));
    if(c == NULL){
        printf("Errore riallocazione");
        return NULL;
    }
    return c;
}