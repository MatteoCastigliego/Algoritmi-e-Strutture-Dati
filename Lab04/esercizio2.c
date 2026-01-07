#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "brani.txt"
#define MAX_LEN 255

typedef struct{
    char **canzoni;
    int num_canzoni;
}lista;

char **assegna_canzoni(int n, FILE *f);
int principio_di_moltiplicazione(int pos, lista *l, char**sol, int n, int cnt);
void libera_memoria(lista *l, int n);

int main(){
    FILE *fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file"); return -1;
    }

    int numero_amici, numero_canz;
    fscanf(fin, "%d", &numero_amici);
    printf("Numero amici: %d\n", numero_amici);

    lista *lista_canzoni = (lista*)malloc(numero_amici*sizeof(lista));
    if(lista_canzoni == NULL){
        printf("Errore nell'allocazione della lista delle canzoni"); return -1;
    }

    for(int i = 0; i < numero_amici; i++){
        fscanf(fin, "%d", &numero_canz);
        lista_canzoni[i].num_canzoni = numero_canz;
        lista_canzoni[i].canzoni = assegna_canzoni(numero_canz, fin);
    }

    for(int i = 0; i < numero_amici; i++){
        printf("Numero canzoni: %d --> ", lista_canzoni[i].num_canzoni);
        for(int j = 0; j < lista_canzoni[i].num_canzoni; j++){
            printf("%s ", lista_canzoni[i].canzoni[j]);
        }
        printf("\n");
    }

    char **sol = (char**)malloc(numero_amici*sizeof(char*));
    if(sol == NULL){
        printf("Errore nell'allocazione del vettore delle soluzioni!"); return -1;
    }
    int num_playlist_totali = principio_di_moltiplicazione(0, lista_canzoni, sol, numero_amici, 0);
    printf("In totale si possono elaborare %d playlist.", num_playlist_totali);

    libera_memoria(lista_canzoni, numero_amici);
    fclose(fin);
}

char **assegna_canzoni(int n, FILE *f)
{
    char **mat, canzone[MAX_LEN];
    mat = (char**)malloc(n*sizeof(char*));
    for(int i = 0; i < n; i++){
        fscanf(f, "%s", canzone);
        mat[i] = strdup(canzone);
    }
    return mat;
}

int principio_di_moltiplicazione(int pos, lista *l, char**sol, int n, int cnt)
{
    if(pos >= n){
        printf("{ ");
        for(int i = 0; i < n; i++){
            printf("%s ", sol[i]);
        }
        printf("}\n");
        return cnt+1;
    }

    for(int i = 0; i < l[pos].num_canzoni; i++){
        sol[pos] = l[pos].canzoni[i];
        cnt = principio_di_moltiplicazione(pos+1, l, sol, n, cnt);
    }
    return cnt;
}

void libera_memoria(lista *l, int n)
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < l[i].num_canzoni; j++){
            free(l[i].canzoni[j]);
        }
        free(l[i].canzoni);
    }
    free(l);
}
