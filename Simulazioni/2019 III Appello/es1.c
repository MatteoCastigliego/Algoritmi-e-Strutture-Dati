#include <stdio.h>
#include <stdlib.h>

/*

Si scriva un programma C che, dato un intero N, generi una matrice quadrata NxN con tutti 0 sulla diagonale principale, 
tutti 1 sulle 2 diagonali immediatamente sopra e sotto, tutti 2 su quelle sopra e sotto le precedenti, etc,
come nel seguente esempio per N=5

0 1 2 3 4
1 0 1 2 3
2 1 0 1 2
3 2 1 0 1
4 3 2 1 0

*/

void genera_matrice(int N){
    int **mat = (int**)malloc(N*sizeof(int*));
    for(int i = 0; i < N; i++){
        mat[i] = malloc(N*sizeof(int)); 
    }

    for(int i = 0; i < N ; i++){
        for(int j = 0; j < N; j++){
            if(i == j){
                for(int k = 0; k < N; k++){
                    if(j+k < N) mat[i][j+k] = k;
                    if(j-k >= 0) mat[i][j-k] = k;
                }
            }
        }
    }
}

// oppure 

void genera_matrice(int N){
    int **mat = (int**)malloc(N*sizeof(int*));
    for(int i = 0; i < N; i++){
        mat[i] = malloc(N*sizeof(int)); 
    }

    for(int i = 0; i < N ; i++){
        for(int j = 0; j < N; j++){
            mat[i][j] = abs(i-j);
        }
    }

    for(int i = 0; i < N ; i++){
        for(int j = 0; j < N; j++){
            printf("%d", mat[i][j]);
        }
    }


}