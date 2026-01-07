#include <stdio.h>
#include <stdlib.h>
#define filename "val0.txt"

int solveR(int *val, int *opt, int n, int k);
void solve(int *val, int n);
void solveDP(int *val, int n);
void displaySol(int *opt, int *val, int n);
int maxi(int a, int b);

int main(){
    FILE *fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file di input!"); return -1;
    }

    int num_citta;
    fscanf(fin, "%d", &num_citta);
    
    int *vett_abitanti = calloc(num_citta + 1, sizeof(int));
    if(vett_abitanti == NULL){
        printf("Errore nell'allocazione del vettore abitanti!"); return -1;
    }

    //inizializzo vettore val
    for(int i = 1; i <= num_citta; i++){
        fscanf(fin, "%d", vett_abitanti[i]);
    }

    //soluzione risorsiva
    solve(vett_abitanti, num_citta);

    //soluzione comn programmazione dinamica
    solveDP(vett_abitanti, num_citta);
}


int solveR(int *val, int *opt, int n, int k) {
    if (k==0)
        return 0;
    if (k==1)
        return val[1];
    return maxi(solveR(val,opt,n,k-1), solveR(val,opt,n,k-2) + val[k]);
}


void solve(int *val, int n) {
    int *opt;
    opt = calloc((n+1),sizeof(int));
    printf("Recursive solution: ");
    printf("maximum population covered %d\n", solveR(val, opt, n, n));
}

void solveDP(int *val, int n){
    int i, *opt;
    opt = calloc((n+1),sizeof(int));
    opt[1] = val[1];
    for (i=2; i<=n; i++) {
        if (opt[i-1] > opt[i-2]+val[i])
            opt[i] = opt[i-1];
        else
            opt[i] = opt[i-2] + val[i];
    }
    printf("Dynamic programming solution: ");
    printf("maximum population covered %d\n", opt[n]);
    displaySol(opt, val, n);
}


void displaySol(int *opt, int *val, int n){
    int i, j, *sol;
    sol = calloc((n+1),sizeof(int));
    sol[1]=1;
    i=n;
    while (i>=2) {
        printf("i=%d\n", i);
        if (opt[i] == opt[i-1]){
            sol[i] = 0;
            i--;
        }else if (opt[i] == opt[i-2] + val[i]) {
                    sol[i] = 1;
                    sol[i-1] = 0;
                    i -=2;
                }
    }
    for (i=1; i<=n; i++)
        if (sol[i])
        printf("%d ", val[i]);
    printf("\n");
}

int maxi(int a, int b) {
    return (a > b);
}


