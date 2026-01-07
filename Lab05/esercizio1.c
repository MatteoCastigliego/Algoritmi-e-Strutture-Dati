#include <stdio.h>
#include <stdlib.h>
#define filename "att.txt"

int durata_massima = 0;
int num_soluzioni = 0;

typedef struct{
    int inizio;
    int fine;
}att;

void attSel(int N, att *V);
void comb_semplici(int pos, att *val, att *sol, int n, int k, int start, att *fin);
int non_si_sovrappongono(att *v, int n);
void controlla(att *sol, att *fin, int n);


int main(void){
    FILE *fin = fopen(filename, "r");
    if (fin == NULL){
        printf("Errore nell'apertura del file!");
        return -1;
    }

    int num_attivita;
    fscanf(fin, "%d", &num_attivita);

    att *attivita = (att*)malloc(num_attivita*sizeof(att));
    if(attivita == NULL){
        printf("Errore nell'alocazione del vettore!");
        return -1;
    }

    for(int i = 0; i < num_attivita; i++){
        fscanf(fin, "%d %d", &attivita[i].inizio, &attivita[i].fine);
    }
    for(int i = 0; i < num_attivita; i++){
        printf("%d %d\n", attivita[i].inizio, attivita[i].fine);
    }
    fclose(fin);

    attSel(num_attivita, attivita);
    
}

void attSel(int N, att *V){
    att *sol_fin = malloc(N*sizeof(att));
    for(int i = 1; i <= N; i++){
        att *sol = malloc(i*sizeof(att));
        comb_semplici(0, V, sol, N, i, 0, sol_fin);
        free(sol);
    }

    printf("{");
    for(int i = 0; i < num_soluzioni; i++){
        printf(" (%d,%d) ", sol_fin[i].inizio, sol_fin[i].fine);
    }
    printf("}");
    printf("La somma delle durate è pari a %d", durata_massima);
    free(sol_fin);
}

void comb_semplici(int pos, att *val, att *sol, int n, int k, int start, att *fin)
{
    if(pos >= k){
        controlla(sol, fin, k);
        return;
    }

    for(int i = start; i < n; i++){
        sol[pos] = val[i];
        if(non_si_sovrappongono(sol, pos)){
            comb_semplici(pos+1, val, sol, n, k, i+1, fin);
        }
    }
}

int non_si_sovrappongono(att *v, int n)
{
    int ok = 1;
    for(int i = 0; i < n && ok; i++){
        if(v[i].inizio < v[n].fine && v[i].fine > v[n].inizio) ok = 0;
    }
    return ok;
}

void controlla(att *sol, att *fin, int n){
    int durata = 0;
    for(int i = 0; i < n; i++){
        durata = durata + (sol[i].fine - sol[i].inizio);
    }

    if(durata > durata_massima){
        durata_massima = durata;
        num_soluzioni = n;
        for(int i = 0; i < n; i++){
            fin[i] = sol[i];
        }
    }
}

