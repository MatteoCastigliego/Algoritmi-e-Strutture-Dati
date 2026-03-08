#include <stdio.h>
#include <stdlib.h>

/*
È dato un vettore V contenente N interi non negativi: il vettore non è ordinato e sono possibili dati ripetuti. Si vogliono generare, come risultato, due vettori (allocati dinamicamente) V1 e V2, in cui suddividere gli interi, in modo tale che, date la somma S1 degli interi in V1 e la somma S2 degli interi in V2, si minimizzi |S2-S1|. La funzione deve poter essere chiamata come segue:

int N1, N2, *V1, *V2;
N1 = bestSplit(V, N, &V1, &V2);
N2 = N-N1;

V1 e V2 sono (puntatori a) vettori di interi che vanno allocati dinamicamente nella bestSplit, N1 è il numero di interi in V1, mentre N2 è il numero di interi in V2. Si riportano una soluzione (parziale) e le domande a cui rispondere.


void bestSolR(int *val, int *sol,

              int *bestSol, int sum,

              int *bestSumP,

              int goal, int n, int start) {

   int i;

   if (checkTerminal(n,start,sum,goal)) {

     checkBestSol(n, sol, bestSol, sum, bestSumP, goal);

     return;

   }

   for (i = <1>; i < n; i++) {

      sol[i] = 1;

      bestSolR(<2>);

      sol[i] = 0;

   }

}




int bestSplit(<3>) {

  int *sol = calloc(N,sizeof(int));

  int *bestSol = calloc(N,sizeof(int));

  int bestSum=0;

  int goal = 0;

  int n1;

  for (int i=0; i<N; i++) goal += V[i];

  goal /= 2;

  // la funzione ricorsiva trova i dati per

  // uno dei due vettori; i dati non selezionati

  // andranno nel secondo vettore.

  bestSolR(0, V, sol, bestSol, 0, &bestSum, goal, N, 0);

  n1 = buildSol(V,N,bestSol,V1p,V2p);

  free(sol);

  free(bestSol);

  return n1;

}


DOMANDA


RISPOSTA

<1> va sostituito con

 start

<2> va sostituito con

 val, sol, bestSol, sum+val[i], bestSumP, goal, n, start

<3> va sostituito con

 int v[], int N, int **V1p, int **V2p

Cosa enumera la bestSolR, in relazione allo spazio delle scelte/soluzioni?

(motivare il modello del calcolo combinatorio indicato)
*/

/*
Scrivere la funzione

checkTerminal
    */

int checkTerminal(int n, int start, int sum, int goal){
    return sum >= goal;
}


/*
Scrivere la funzione

checkBestSol
    */

 void checkBestSol(int n, int *sol, int *bestSol, int sum, int *bestSumP, int goal) {
    if (sum > *bestSumP && sum <= goal){
        *bestSumP = sum;
        for (int i = 0; i < n; i++)
            bestSol[i] = sol[i];
    }

}


/*
Scrivere la funzione

buildSol
	*/

  int buildSol( int V[], int N, int *bestSol, int **V1p, int **V2p) {
    int n1 = 0, n2 = 0, l1 = 0;
    for(int i = 0; i < N; i++){
        if(bestSol[i]) l1++;
    }
    *V1p = malloc(l1*sizeof(int));
    *V2p = malloc((N-l1)*sizeof(int));
    for (int i = 0; i < N; i++){
        if (bestSol[i] == 1){
            (*V1p)[n1++] = V[i];
        }else{
            (*V2p)[n2++] = V[i];
        }            
    }

    return n1;
}
