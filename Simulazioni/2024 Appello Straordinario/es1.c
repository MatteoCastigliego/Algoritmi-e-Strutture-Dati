/* 	
* Sia data una matrice di interi NxN.
* Ogni cella della matrice può contenere solo il valore 0 o il valore 1.
* La matrice rappresenta delle relazioni di amicizia tra persone.
* Se in posizione i,j è contenuto il valore 1, le persone i e j sono amiche.
* Scrivere una funzione che individui e stampi tutte le terne di persone in cui ogni persona è amica delle altre due.
* Si noti che una persona puo' appartenere a più terne. Ogni terna va stampata con gli indici delle tre persone.
* Function prototype is 'void f(int **m, int N);'
*/

#include <stdio.h>

/* function prototype is strict, do not change it */
void f(int **m, int N);

/* function prototype is strict, do not change it */
void f(int **m, int N) {
	/* your code goes here */
	int *sol = (int*)malloc(N*sizeof(int));
	int *val = malloc(N*sizeof(int));
	for(int i = 0; i < N; i++) val[i] = i;
	comb_semplici(0, 0, m, sol, 3, val, N);
}


void comb_semplici(int pos, int start, int **m, int *sol, int k, int *val, int N){
	if(pos >= k){
		if(sono_tutti_amici(sol, m)){
			printf("{");
			for(int i = 0; i < 3; i++){
				printf("%d", sol[i]);
			}
			printf("}");
		}
	}
	for(int i = start; i < N; i++){
		sol[pos] = val[i];
		comb_semplici(pos+1, i+1, m, sol, k, val, N);
	}
}

int sono_tutti_amici(int *sol, int **m){
	int sono_amici = 1;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(i != j){
				if(m[sol[i]][sol[j]] != 1) sono_amici = 0;
			}
		}
	}
    return sono_amici;
}

int main(int argc, char **argv) {
	/* you can implement your test case here [NOT NEEDED] */
	return 0;
}