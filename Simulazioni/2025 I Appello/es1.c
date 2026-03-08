#include <stdio.h>
#include <stdlib.h>

/*

Sono dati due vettori di interi a, b (non ordinati e contenenti eventualmente dati ripetuti), di dimensione rispettivamente na e nb. 
Si scriva una funzione che verifichi se il primo vettore sia una sotto-sequenza del secondo. 
La funzione deve poter essere chiamata come:

ris = subSeq(a,na,b,nb);

*/

int subSeq(int a[], int na, int b[], int nb);

int subSeq(int a[], int na, int b[], int nb){
    int j = 0;
    for(int i = 0; i < nb; i++){
        if(a[j] == b[i]) j++;
    }
    return (j==na);
}



 








