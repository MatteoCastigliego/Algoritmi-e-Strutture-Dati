#include <stdio.h>
#include <stdlib.h>


/*

Sia data una matrice A n × m di interi. Si scriva una funzione C che ritorni l’indice di una colonna qualsiasi fra
quelle in cui la massima differenza (in valore assoluto) tra due elementi consecutivi sia minima.
Esempio: data la seguente matrice A di n = 4 righe e m = 3 colonne:

 15 17 7
 6 18 4
 11 4 12 
 13 9 5

La massima differenza tra gli elementi consecutivi della prima colonna è 9 = 15−6; per la seconda colonna è 14 = 18−4; 
per la terza è 8 = |4−12|. Quindi la funzione deve stampare l’indice 2 della terza colonna.
La funzione ha il seguente prototipo:
int minmaxdiff(int **A, int n, int m);

*/

int minmaxdiff(int **A, int n, int m);

int minmaxdiff(int **A, int n, int m){
    int index, min_r = 10000;
    for(int j = 0; j < m; j++){
        int max = 0;
        for(int i = 1; i < n; i++){
            if(abs(A[i-1][j] - A[i][j]) > max){
                max = abs(A[i-1][j] - A[i][j]);
            }
        }
        if(max < min_r){
            min_r = max;
            index = j;
        }
    }
    return index;
}