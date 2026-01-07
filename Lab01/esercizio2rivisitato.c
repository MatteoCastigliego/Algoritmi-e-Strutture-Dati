/* IN QUESTA SECONDA VERSION HO CERCATO DI ADATTARE IL CODICE UTILIZZANDO STRUTTURE DINAMIHE A ANCHE UN PO' DI RICORSIONE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define filename "corse.txt"
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
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
} comando_e;


comando_e leggi_comando(void);
void ricerca_per_data(dizionario *diz, int num_valori);
void ricerca_per_fermata(dizionario *diz, int num_valori);
void ricerca_per_capolinea(dizionario *diz, int num_valori);
void ricerca_per_ritardo_in_date(dizionario *diz, int num_valori);
void ritardo_totale_per_tratta(dizionario *diz, int num_valori);
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
    comando_e comando;
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


    /* STAMPO IL DIZIONARIO */
    for (int i = 0; i < numero_dati; i++)
    {
        printf("%s %s %s %s %s %s %d \n",
               tratte[i].codice,
               tratte[i].partenza,
               tratte[i].destinazione,
               tratte[i].data,
               tratte[i].ora_partenza,
               tratte[i].ora_arrivo,
               tratte[i].ritardo);
    }

    comando = leggi_comando();
    switch (comando)
    {
    case (r_date):
        ricerca_per_data(tratte, numero_dati); break;
    case (r_capolinea):
        ricerca_per_capolinea(tratte, numero_dati); break;
    case (r_partenza):
        ricerca_per_fermata(tratte, numero_dati); break;
    case (r_ritardo):
        ricerca_per_ritardo_in_date(tratte, numero_dati); break;
    case (r_ritardo_tot):
        ritardo_totale_per_tratta(tratte, numero_dati); break;
    case (r_fine): printf("Comando non valido!\n"); break;
    }

    fclose(fin);
    deallocazione(tratte, numero_dati, 0);
    exit(0);
}


comando_e leggi_comando(void)
{
    comando_e c;
    char comando[20];
    char tabella[r_fine][MAX_LEN_STR] = {
        "date", "partenza", "capolinea", "ritardo", "ritardo_totale"};
    printf("Inserire comando (date/partenza/capolinea/ritardo/ritardo_totale):");
    scanf("%s", comando);
    c = r_date;
    while (c < r_fine && strcmp(comando, tabella[c]) != 0)
    {
        c++;
    }
    return (c);
}


/* Elencare tutte le corse partite in un certo intervallo di date */
void ricerca_per_data(dizionario *diz, int num_valori)
{
    char data_inizio[MAX_LEN_STR], data_fine[MAX_LEN_STR];
    int data_inizio_convertita, data_fine_convertita, count = 0;

    printf("Inserire la data di inizio (formato: aaaa/mm/gg): ");
    scanf("%s", data_inizio);
    printf("Inserire la data di fine (formato: aaaa/mm/gg): ");
    scanf("%s", data_fine);

    data_inizio_convertita = converti_data_in_ore(data_inizio);
    data_fine_convertita = converti_data_in_ore(data_fine);

    printf("\n");
    printf("VISUALIZZIAMO TUTTE LE CORSE CHE SONO PARTITE TRA IL %s e il %s \n\n", data_inizio, data_fine);
    for (int i = 0; i < num_valori; i++)
    {
        int data_inizio_corrente = converti_data_in_ore(diz[i].data);
        if (data_inizio_corrente > data_inizio_convertita && data_inizio_corrente < data_fine_convertita)
        {
            stampa_riga(&diz[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("Non ci sono corse che sono partite tra il %s e il %s \n", data_inizio, data_fine);
    }
}


/* Elencare tutti le corse partite da una certa fermata */
void ricerca_per_fermata(dizionario *diz, int num_valori)
{
    char fermata[MAX_LEN_STR];
    int count = 0;
    printf("Inserire il nome della fermata di interesse: ");
    scanf("%s", fermata);
    printf("\n");

    printf("VISUALIZZIAMO TUTTE LE CORSE CHE SONO PARTITE DA: %s \n", fermata);

    for (int i = 0; i < num_valori; i++)
    {
        if (strcmp(fermata, diz[i].partenza) == 0)
        {
            stampa_riga(&diz[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("Non ci sono corse che sono partite da: %s", fermata);
    }   
}


/* Elencare tutti le corse che fanno capolinea in una certa fermata */
void ricerca_per_capolinea(dizionario *diz, int num_valori)
{
    char fermata[MAX_LEN_STR];
    int count = 0;
    printf("Inserire il nome della fermata di interesse: ");
    scanf("%s", fermata);
    printf("\n");

    printf("VISUALIZZIAMO TUTTE LE CORSE CON CAPOLINEA A: %s \n", fermata);

    for (int i = 0; i < num_valori; i++)
    {
        if (strcmp(fermata, diz[i].destinazione) == 0)
        {
            stampa_riga(&diz[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("Non ci sono corse che fanno capolinea a: %s", fermata);
    }  
}


/* Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date */
void ricerca_per_ritardo_in_date(dizionario *diz, int num_valori)
{
    char data_inizio[MAX_LEN_STR], data_fine[MAX_LEN_STR];
    int data_inizio_convertita, data_fine_convertita, count = 0;

    printf("Inserire la data di inizio (formato: aaaa/mm/gg): ");
    scanf("%s", data_inizio);
    printf("Inserire la data di fine (formato: aaaa/mm/gg): ");
    scanf("%s", data_fine);

    data_inizio_convertita = converti_data_in_ore(data_inizio);
    data_fine_convertita = converti_data_in_ore(data_fine);

    for (int i = 0; i < num_valori; i++)
    {
        int data_inizio_corrente = converti_data_in_ore(diz[i].data);
        if (data_inizio_corrente > data_inizio_convertita && data_inizio_corrente < data_fine_convertita && diz[i].ritardo > 0)
        {
            stampa_riga(&diz[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("Non ci sono corse arrivate in ritardo nelle date %s - %s", data_inizio, data_fine);
    }
}


/* elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta */
void ritardo_totale_per_tratta(dizionario *diz, int num_valori)
{
    char codice[MAX_LEN_STR];

    int ritardo = 0, count = 0;
    ;
    printf("Inserire il codice della tratta di interesse: ");
    scanf("%s", codice);

    for (int i = 0; i < num_valori; i++)
    {
        if (strcmp(codice, diz[i].codice) == 0)
        {
            ritardo = ritardo + diz[i].ritardo;
            count++;
        }
    }

    if (count == 0)
    {
        printf("Non ci sono corse con il codice: %s", codice);
    }
    else
    {
        printf("Il ritardo totale accumulato dalla corsa %s è in totale: %d minuti", codice, ritardo);
    } 
}


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


void stampa_riga(dizionario *diz)
{
    printf("%s %s %s %s %s %s %d", diz->codice, diz->partenza, diz->destinazione, diz->data, diz->ora_partenza, diz->ora_arrivo, diz->ritardo);
    printf("\n");
}


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
}
