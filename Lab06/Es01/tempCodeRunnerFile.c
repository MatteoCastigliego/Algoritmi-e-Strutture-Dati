#include <stdio.h>
#include <stdlib.h>
#define filein "att.txt"


typedef struct{
    int inizio;
    int fine;
}activities;


int num_attivita;
activities *leggi_file(char *filename);
void stampa_attivita(activities *att);
void quickSort(activities *A, int l, int r);
int partition(activities *A, int l, int r);
void Swap(activities *A, int x, int y);
void trova_soluzione_ottima(activities *att);
int non_si_sovrappongono(activities v, activities x);


int main(){

    activities *attivita = leggi_file(filein);
    stampa_attivita(attivita);

    quickSort(attivita, 0, num_attivita-1);

    trova_soluzione_ottima(attivita);

}


activities *leggi_file(char *filename){
    FILE *fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file di input!");
        exit(0);
    }

    fscanf(fin, "%d", &num_attivita);
    activities *att = (activities*)malloc(num_attivita*sizeof(activities));
    if(att == NULL){
        printf("Errore nell'allocazione del vettore di attivita!");
        exit(0);
    }

    for(int i = 0; i < num_attivita; i++){
        fscanf(fin, "%d %d", &att[i].inizio, &att[i].fine);
    }

    return att;
}


void stampa_attivita(activities *att){
    for(int i = 0; i < num_attivita; i++){
        printf("%d %d\n", att[i].inizio, att[i].fine);
    }
}


/* ALGORITMO DI ORDINAMENTO QUICKSORT */
void quickSort(activities *A, int l, int r){
    int q;
    if(l >= r) return;
    q = partition(A, l, r);
    quickSort(A, l, q-1);
    quickSort(A, q+1, r);
    return;
}

int partition(activities *A, int l, int r){
    int i, j;
    int x = A[r].fine;
    i = l-1;
    j = r;
    for( ; ; ){
        while(A[++i].fine < x);
        while(A[--j].fine > x);

        if(i >= j){
            break;
        }
        Swap(A, i, j);
    }
    Swap(A, i, r);
    return i;
}

void Swap(activities *A, int x, int y){
    activities tmp = A[x];
    A[x] = A[y];
    A[y] = tmp;
    return;
}


void trova_soluzione_ottima(activities *att){
    int flag;
    int durata = 0;
    int *val_presi = calloc(num_attivita, sizeof(int));
    int *soluzione_ottima = calloc(num_attivita, sizeof(int));
    if(soluzione_ottima == NULL) return;

    soluzione_ottima[0] = att[0].fine - att[0].inizio;

    for(int i = 1 ; i < num_attivita; i++){
        soluzione_ottima[i] = soluzione_ottima[i - 1];
        for(int j = i - 1; j >= 0; j--){
            if(non_si_sovrappongono(att[j], att[i])){
                if(soluzione_ottima[j] + (att[i].fine - att[i].inizio) > soluzione_ottima[i]){
                    soluzione_ottima[i] = soluzione_ottima[j] + (att[i].fine - att[i].inizio);
                    val_presi[i] = 1;
                }
            }
        }
    }
    printf("La soluzione ottima è: %d\n", soluzione_ottima[num_attivita - 1]);
    printf("I valori presi sono: { ");
    for(int i = 0; i < num_attivita; i++){
        if(val_presi[i] == 1){
            printf("(%d, %d) ", att[i].inizio, att[i].fine);
        }
    }
    printf("}");
}


int non_si_sovrappongono(activities v, activities x){
    int ok = 1;
    if(v.inizio < x.fine && v.fine > x.inizio) ok = 0;

    return ok;
}
