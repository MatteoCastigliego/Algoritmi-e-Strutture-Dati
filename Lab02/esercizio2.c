#include <stdio.h>
#include <stdlib.h>
#define filename "mat.txt"

int **malloc2dR(int n_righe, int n_colonne);
void malloc2dP(int ***mp, int n_righe, int n_colonne);
void freeMat(int **mat, int n_righe);
void separa(int **mat, int n_righe, int n_colonne, int *v_neri, int *v_bianchi, int *cB, int *cN);

int main(){

    FILE *fin;
    int num_righe, num_colonne, x;
    int **m1, **m2;
    int *vet_neri, *vet_bianchi;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nell'apertura nel file!");
    }

    fscanf(fin, "%d %d", &num_righe, &num_colonne);

    m1 = malloc2dR(num_righe, num_colonne);

    malloc2dP(&m2, num_righe, num_colonne);

    for(int i = 0; i < num_righe; i++){
        for(int j = 0; j < num_colonne; j++){
            fscanf(fin, "%d", &x);
            m1[i][j] = x;
            m2[i][j] = x;
        }
    }

    printf("Allocazione matrice con primo metodo (**malloc2dR):\n");
    for(int i = 0; i < num_righe; i++){
        for(int j = 0; j < num_colonne; j++){
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }

    printf("Allocazione matrice con secondo metodo (malloc2dP):\n");
    for(int i = 0; i < num_righe; i++){
        for(int j = 0; j < num_colonne; j++){
            printf("%d ", m2[i][j]);
        }
        printf("\n");
    }

    int lunghezza_max = num_colonne*num_righe, cntB, cntN;
    vet_neri = (int*)malloc(lunghezza_max*sizeof(int));
    vet_bianchi = (int*)malloc(lunghezza_max*sizeof(int));

    separa(m1, num_righe, num_colonne, vet_neri, vet_bianchi, &cntB, &cntN);

    printf("Vettore di elementi neri: \n");
    for(int i = 0; i < cntN; i++){
        printf("%d ", vet_neri[i]);
    }
    printf("\n");

    printf("Vettore di elementi bianchi: \n");
    for(int i = 0; i < cntB; i++){
        printf("%d ", vet_bianchi[i]);
    }


    freeMat(m1, num_righe);
    freeMat(m2, num_colonne);
}

int **malloc2dR(int n_righe, int n_colonne)
{
    int **m;
    m = (int**)malloc(n_righe*sizeof(int*));
    for(int i = 0; i < n_colonne; i++){
        m[i] = (int*)malloc(n_colonne*sizeof(int));
    }
    return m;
}

void malloc2dP(int ***mp, int n_righe, int n_colonne)
{
    int **m;
    m = (int**)malloc(n_righe*sizeof(int*));
    for(int i = 0; i < n_colonne; i++){
        m[i] = (int*)malloc(n_colonne*sizeof(int));
    }
    *mp = m;
}

void freeMat(int **mat, int n_righe)
{
    for(int i = 0; i < n_righe; i++){
        free(mat[i]);
    }
    free(mat);
}

void separa(int **mat, int n_righe, int n_colonne, int *v_neri, int *v_bianchi, int *cB, int *cN)
{
    *cB = 0;
    *cN = 0;
    int nero;

    for(int i = 0; i < n_righe; i++){
        if(i % 2 == 0){
            nero = 1;
        }else{
            nero = 0;
        }
        for(int j = 0; j < n_colonne; j++){
            if(nero == 1){
                v_neri[(*cN)] = mat[i][j];
                (*cN)++;
                nero = 0;
            }else{
                v_bianchi[(*cB)] = mat[i][j];
                (*cB)++;
                nero = 1;
            }
        }
    }
}
