#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define filename "corse.txt"
#define filenameO "output.txt"
#define MAX_LEN_STR 30

typedef struct{
    char *codice;
    char *partenza;
    char *destinazione;
    char *data;
    char *ora_partenza;
    char *ora_arrivo;
    int ritardo;
} dizionario;

typedef enum{
    r_video, r_file, r_fine
} comando_e;


comando_e leggi_comando(void);
void stampa_a_video(dizionario *diz, int num_valori);
void stampa_su_file(dizionario *diz, int num_valori);
void ordinamento_per_data(dizionario **diz, int num_valori);
void ordinamento_per_codice_tratta(dizionario **diz, int num_valori);
void ordinamento_per_stazione_di_partenza(dizionario **diz, int num_valori);
void ordinamento_per_stazione_di_arrivo(dizionario **diz, int num_valori);
void ottieni_corsa_da_codice(dizionario *diz, int num_valori);
void ottieni_corsa_da_codice_parziale(dizionario *diz, int num_valori);
int non_presente(int *vet, int num, int dim);
void quickSort(int *A, int l, int r);
int partition(int *A, int l, int r);
void Swap(int *A, int x, int y);
int ottieni_numero_da_codice(char *codice);
int converti_data_in_ore(char *data);
void stampa_riga(dizionario *diz);
void deallocazione(dizionario *diz, int num_valori, int N);


int main(void)
{
    char codice[MAX_LEN_STR], partenza[MAX_LEN_STR], destinazione[MAX_LEN_STR], data[MAX_LEN_STR], ora_partenza[MAX_LEN_STR], ora_arrivo[MAX_LEN_STR];
    dizionario *tratte;
    int N = 1;
    tratte = (dizionario *)malloc(N * sizeof(dizionario));

    FILE *fin;
    int numero_dati;
    comando_e stampa;
    fin = fopen(filename, "r");

    if (fin == NULL)
    {
        printf("Errore nell'apertura del file!");
        return -1;
    }

    fscanf(fin, "%d", &numero_dati);

    /* oppure direttamente
        tratte = (dizionario*)malloc(numero_dati*sizeof(dizionario))
    questo mi evita la realloc nel ciclo for
     */

    for (int i = 0; i < numero_dati; i++)
    {
        if (i == N)
        {
            N = N * 2;
            tratte = realloc(tratte, N * sizeof(dizionario));
            if (tratte == NULL)
            {
                printf("Errore nella realloc!");
                return -1;
            }
        }
        fscanf(fin, "%s %s %s %s %s %s %d",
               codice,
               partenza,
               destinazione,
               data,
               ora_partenza,
               ora_arrivo,
               &tratte[i].ritardo);

        /* Utilizzo la funzione strdup che contiene al suo interno una malloc, della dimensione del parametro passato, e una strcpy */    
        tratte[i].codice = strdup(codice);
        tratte[i].partenza = strdup(partenza);
        tratte[i].destinazione = strdup(destinazione);
        tratte[i].data = strdup(data);
        tratte[i].ora_partenza = strdup(ora_partenza);
        tratte[i].ora_arrivo = strdup(ora_arrivo);
    }

    stampa = leggi_comando();
    switch (stampa)
    {
    case (r_video):
        stampa_a_video(tratte, numero_dati); break;
    case (r_file):
        stampa_su_file(tratte, numero_dati); break;
    }

    dizionario **per_data = malloc(numero_dati*sizeof(dizionario*));
    dizionario **per_codice = malloc(numero_dati*sizeof(dizionario*));
    dizionario **per_stazione_partenza = malloc(numero_dati*sizeof(dizionario*));
    dizionario **per_stazione_arrivo = malloc(numero_dati*sizeof(dizionario*));
    for(int i = 0; i < numero_dati; i++){
        per_data[i] = &tratte[i];
        per_codice[i] = &tratte[i];
        per_stazione_partenza[i] = &tratte[i];
        per_stazione_arrivo[i] = &tratte[i];
    }

    printf("\n");
    printf("Ordinamento dati per data:");
    printf("\n");
    ordinamento_per_data(per_data, numero_dati);
    printf("\n");

    printf("Ordinamento per codice di tratta:");
    printf("\n");
    ordinamento_per_codice_tratta(per_codice, numero_dati);
    printf("\n");

    printf("Ordinamento per stazione di partenza:");
    printf("\n");
    ordinamento_per_stazione_di_partenza(per_stazione_partenza, numero_dati);
    printf("\n");

    printf("Ordinamento per stazione di arrivo:");
    printf("\n");
    ordinamento_per_stazione_di_arrivo(per_stazione_arrivo, numero_dati);
    printf("\n");

    ottieni_corsa_da_codice(tratte, numero_dati);
    printf("\n\n");

    ottieni_corsa_da_codice_parziale(tratte, numero_dati);
    printf("\n");

    free(per_data);
    free(per_codice);
    free(per_stazione_arrivo);
    free(per_stazione_partenza);
    fclose(fin);
    deallocazione(tratte, numero_dati, 0);
    printf("FINE PROGRAMMA!");
    return 0;
}


/* LETTURA DEL COMANDO */
comando_e leggi_comando(void)
{
    comando_e c;
    char comando[20];
    char tabella[r_fine][MAX_LEN_STR] = {
        "video", "file"};
    printf("Dove vuoi stampare i dati (video/file):");
    scanf("%s", comando);
    c = r_video;
    while (c < r_fine && strcmp(comando, tabella[c]) != 0)
    {
        c++;
    }
    return (c);
}


/* STAMPA RIGA A VIDEO O FILE */
void stampa_a_video(dizionario *diz, int num_valori){
    for(int i = 0; i < num_valori; i++){
        stampa_riga(&diz[i]);
    }
}

void stampa_su_file(dizionario *diz, int num_valori){
    FILE *fout;
    fout = fopen(filenameO, "w");

    if(fout == NULL){
        printf("Errore nel file di output!");
        return;
    }
    for(int i = 0; i < num_valori; i++){
        fprintf(fout, "%s %s %s %s %s %s %d \n", diz[i].codice, diz[i].partenza, diz[i].destinazione, diz[i].data, diz[i].ora_partenza, diz[i].ora_arrivo, diz[i].ritardo);
    }
    fclose(fout);
}

void stampa_riga(dizionario *diz)
{
    printf("%s %s %s %s %s %s %d", diz->codice, diz->partenza, diz->destinazione, diz->data, diz->ora_partenza, diz->ora_arrivo, diz->ritardo);
    printf("\n");
}


/* ORDINAMENTO DEI DATI PER DATA O ORA */
void ordinamento_per_data(dizionario **diz, int num_valori)
{
    int *vett, cnt = 0;
    vett = (int*)malloc(num_valori*sizeof(int));

    if(vett == NULL){
        printf("Errore allocazione vettore di appoggio!");
    }


    for(int i = 0; i < num_valori; i++){
        int data_convertita = converti_data_in_ore(diz[i]->data);
        if(non_presente(vett, data_convertita, cnt)){
            vett[cnt] = data_convertita;
            cnt++;
        }
    }

    quickSort(vett, 0, cnt-1);

    for(int i = 0; i < num_valori; i++){
        for(int j = 0; j < num_valori; j++){
            if(converti_data_in_ore(diz[j]->data) == vett[i]){
                stampa_riga(diz[j]);
            }
        }
    }
}


/* ORDINAMENTO DATI PER CODICE DI TRATTA */
void ordinamento_per_codice_tratta(dizionario **diz, int num_valori)
{
    int *vett = (int*)malloc(num_valori*sizeof(int));
    int codice_numerico, cnt = 0;
    if (vett == NULL) printf("Errore di allocazione!");

    for(int i = 0; i < num_valori; i++){
        codice_numerico = ottieni_numero_da_codice(diz[i]->codice);
        if(non_presente(vett, codice_numerico, cnt)){
            vett[cnt] = codice_numerico;
            cnt++;
        }
    }

    quickSort(vett, 0, cnt-1);

    for(int i = 0; i < num_valori; i++){
        for(int j = 0; j < num_valori; j++){
            if(ottieni_numero_da_codice(diz[j]->codice) == vett[i]){
                stampa_riga(diz[j]);
            }
        }
    }
}


/* ORDINAMENTO DATI PER STAZIONE DI PARTENZA */
void ordinamento_per_stazione_di_partenza(dizionario **diz, int num_valori)
{
    for(int i = 0; i < num_valori; i++){
        for(int j = i+1; j < num_valori; j++){
            if(strcmp(diz[i]->partenza, diz[j]->partenza) > 0){/*la seconda viene prima in ordine alfabetico*/
                dizionario *temp = diz[i];
                diz[i] = diz[j];
                diz[j] = temp;
            }
        }
        stampa_riga(diz[i]);
    }
}


/* ORDINAMENTO PER STAZIONE DI ARRIVO */
void ordinamento_per_stazione_di_arrivo(dizionario **diz, int num_valori)
{
    for(int i = 0; i < num_valori; i++){
        for(int j = i+1; j < num_valori; j++){
            if(strcmp(diz[i]->destinazione, diz[j]->destinazione) > 0){
                dizionario *temp = diz[i];
                diz[i] = diz[j];
                diz[j] = temp;
            }
        }
        stampa_riga(diz[i]);
    }
}


/* RICERCA LINEARE PER CODICE */
void ottieni_corsa_da_codice(dizionario *diz, int num_valori)
{
    char codice[MAX_LEN_STR];
    int trovato = 0;
    printf("Inserire codice da ricercare: ");
    scanf("%s", codice);

    for(int i = 0; i < num_valori && trovato == 0; i++){
        if(strcmp(diz[i].codice, codice) == 0){
            stampa_riga(&diz[i]);
            trovato = 1;
        }
    }

    if(trovato == 0){
        printf("Non ci sono corse con il codice %s", codice);
    }
}


/* RICERCA CON CODICE INTERO O PARZIALE */
void ottieni_corsa_da_codice_parziale(dizionario *diz, int num_valori)
{
    char codice[MAX_LEN_STR];
    printf("Inserire stazione da cercare (nome totale o parziale): ");
    scanf("%s", codice);
    
    for(int i = 0; i < num_valori; i++){
        if(strncmp(diz[i].partenza, codice, strlen(codice)) == 0){
            stampa_riga(&diz[i]);
        }
    }
}

int ottieni_numero_da_codice(char *codice){
    int numero;
    sscanf(codice, "%*3s%d", &numero);
    return numero;
}

int non_presente(int *vet, int num, int dim){
    for(int i = 0; i < dim; i++){
        if(vet[i] == num){
            return 0;
        }
    }
    return 1;
}


/* FUNZIONE DI CONVERSIONE DELLA DATA IN ORE */
int converti_data_in_ore(char *data)
{
    int anno, mese, giorno;
    int valore;
    if (sscanf(data, "%d/%d/%d", &anno, &mese, &giorno) != 3)
    {
        printf("Il formato della data è errato!");
        return 0;
    }
    valore = anno * 365 * 24 + mese * 30 * 24 + giorno * 24;
    return valore;
}


/* DEALLOCAZIONE DELLA STRUTTURA DATI */
void deallocazione(dizionario *diz, int num_valori, int N)
{
    if(N == num_valori){
        free(diz);
        return;
    }
    /* Bisogna deallocare ogni singolo campo e solo alla fine la struct intera */
    free(diz[N].codice);
    free(diz[N].partenza);
    free(diz[N].destinazione);
    free(diz[N].ora_arrivo);
    free(diz[N].ora_partenza);
    free(diz[N].data);

    deallocazione(diz, num_valori, N+1);
    return;
}


/* ALGORITMO DI ORDINAMENTO QUICKSORT */
void quickSort(int *A, int l, int r){
    int q;
    if(l >= r) return;
    q = partition(A, l, r);
    quickSort(A, l, q-1);
    quickSort(A, q+1, r);
    return;
}

int partition(int *A, int l, int r){
    int i, j;
    int x = A[r];
    i = l-1;
    j = r;
    for( ; ; ){
        while(A[++i] < x);
        while(A[--j] > x);

        if(i >= j){
            break;
        }
        Swap(A, i, j);
    }
    Swap(A, i, r);
    return i;
}

void Swap(int *A, int x, int y){
    int tmp;
    tmp = A[x];
    A[x] = A[y];
    A[y] = tmp;
    return;
}
