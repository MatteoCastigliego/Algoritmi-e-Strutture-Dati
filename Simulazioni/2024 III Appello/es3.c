#include <stdio.h>
#include <stdlib.h>


// Una superficie piana rettangolare viene suddivisa in N righe e M colonne e rappresentata da una matrice NxM di caratteri, 
// in cui si usa in carattere ‘0’ per rappresentare una casella libera (utilizzabile) e il carattere ‘1’ per una casella occupata 
// (non utilizzabile).

// Si vuole realizzare una funzione che, data la matrice e le coordinate di due caselle libere (di coordinate (r0,c0) e (r1,c1)), 
// determini il percorso di lunghezza minima per connetterle: un percorso è dato da una sequenza di caselle libere adiacenti 
// (aventi riga o colonna in comune) a due a due: detto in altri termini, un percorso si ottiene mediante tratti orizzontali o 
// verticali comprendenti solo caselle libere. La lunghezza di un percorso è data dal numero di caselle che lo compongono. 
// Del percorso ottimo va solo calcolata e ritornata come risultato la lunghezza.

 

// Esempio (piccolo): matrice 4x5 in cui si è rappresentato con delle il percorso ottimo (di lunghezza 5) 
// che connette la casella (1,0) alla (2,3)

 
// 01000
// xxx10
// 01xx0
// 00000


int minPath(char **area, int N, int M, int r0, int c0, int r1, int c1);


int minPath(char **area, int N, int M, int r0, int c0, int r1, int c1){
    int minimo = 10000;
    int attuale = 0;
    int **visited = (int**)malloc(N*sizeof(int*));
    for(int i = 0; i < N; i++){
        visited[i] = (int*)malloc(M*sizeof(int));
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(area[i][j] == 1) visited[i][j] = 1;
            else visited[i][j] = 0; 
        }
    }
    trova_minimo_percorso(area, N, M, r0, c0, r1, c1, r0, c0, &minimo, attuale, visited);
    return minimo;
}

void trova_minimo_percorso(char **area, int N, int M, int r0, int c0, int r1, int c1, int r_att, int c_att, int *minimo, int attuale, int **visited){
    if(r_att < 0 || r_att >= N || c_att < 0 || c_att >= M) return;
    if(area[r_att][c_att] == '1' || visited[r_att][c_att] == 1) return;

    if(r_att == r1 && c_att == c1){
        if(attuale+1 < *minimo) *minimo = attuale + 1;
    }

    visited[r_att][c_att] = 1;

    int dr[] = {-1, 1, 0, 0};
    int dl[] = {0, 0, 1, -1};

    for(int i = 0; i < 4; i++){
        trova_minimo_percorso(area, N, M, r0, c0, r1, c1, r_att+dr[i], c_att+dl[i], minimo, attuale+1, visited);
    }

    visited[r_att][c_att] = 0;
}
