#include <stdio.h>
#include <stdlib.h>
#define filename "input.txt"

int majority(int *A, int N);
int massimo(int *A, int N, int index_start, int len);

int main(){
    FILE *fin = fopen(filename, "r");
    int *vett = NULL, num, num_elementi = 0;

    if (fin == NULL){
        printf("Errore nell'aperura del file %s", filename);
        return -1;
    }

    while(fscanf(fin, "%d", &num) == 1){
        num_elementi++;
        vett = realloc(vett, num_elementi*sizeof(int));
        if (vett == NULL) printf("Errore nella riallocazione");
        vett[num_elementi - 1] = num;
    }

    for(int i = 0; i < num_elementi; i++){
        printf("%d ", vett[i]);
    }
    printf("\n");
    
    int maggioritario = majority(vett, num_elementi);
    if(maggioritario != -1){
        printf("Il maggioritario è: %d", maggioritario);
    }else{
        printf("Non esiste un maggioritario");
    }
}

int majority(int *A, int N)
{
    int max = 0, *vett_occ;
    for(int i = 0; i < N; i++){
        if(A[i] > max){
            max = A[i];
        }
    }

    vett_occ = (int*)calloc(max+1, sizeof(int));
    if(vett_occ == NULL) printf("Errore nell'allocazione del vettore delle occorrenze");

    for(int i = 0; i < N; i++){
        vett_occ[A[i]]++;
    }
    int risultato;
    risultato = massimo(vett_occ, N, 0, max+1);
    
    return risultato;
}

int massimo(int *A, int N, int index_start, int len)
{
    if(index_start >= len){
        return -1;
    }
    if(A[index_start] > N/2){
        return(index_start);
    }
    return massimo(A, N, index_start+1, len);
}
