#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define filename "corse.txt"
#define MAX_LEN_STR 30

typedef struct
{
    char codice[MAX_LEN_STR];
    char partenza[MAX_LEN_STR];
    char destinazione[MAX_LEN_STR];
    char data[MAX_LEN_STR];
    char ora_partenza[MAX_LEN_STR];
    char ora_arrivo[MAX_LEN_STR];
    int ritardo;
} dizionario;

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
}comando_e;

comando_e leggi_comando(void);
void ricerca_per_data(dizionario diz[1000], int num_valori);
void ricerca_per_fermata(dizionario diz[1000], int num_valori);
void ricerca_per_capolinea (dizionario diz[1000], int num_valori); 
void ricerca_per_ritardo_in_date(dizionario diz[1000], int num_valori);
void ritardo_totale_per_tratta(dizionario diz[1000], int num_valori);
int converti_data_in_ore(char data[MAX_LEN_STR]);

int main(void)
{

    /*
        SE VOLESSIMO ALLOCARE DINAMICAMENTE POSSO FARE: (GUARDARE RIGHE COMMENTATE)
    dizionario *tratte;
    int N = 1;
    tratte = (dizionario*)malloc(N*sizeof(dizionario));
    
    */
    FILE *fin;
    dizionario tratte[1000];
    int numero_dati;
    comando_e comando;
    fin = fopen(filename, "r");

    if (fin == NULL)
    {
        printf("Errore nell'apertura del file!");
        return -1;
    }

    fscanf(fin, "%d", &numero_dati);

    for (int i = 0; i < numero_dati; i++)
    {
        /*
        if(i == N){
            N = N*2;
            tratte = realloc(tratte, N*sizeof(dizionario));
            if(tratte == NULL){
                printf("Errore nella realloc!");
                return -1;
            }
        }
        */
        fscanf(fin, "%s %s %s %s %s %s %d",
            tratte[i].codice,
            tratte[i].partenza,
            tratte[i].destinazione,
            tratte[i].data,
            tratte[i].ora_partenza,
            tratte[i].ora_arrivo,
            &tratte[i].ritardo);
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
    case (r_date): ricerca_per_data(tratte, numero_dati);
    case (r_capolinea): ricerca_per_capolinea(tratte, numero_dati);
    case (r_partenza): ricerca_per_fermata(tratte, numero_dati);
    case (r_ritardo): ricerca_per_ritardo_in_date(tratte, numero_dati);
    case (r_ritardo_tot): ritardo_totale_per_tratta(tratte, numero_dati);
    }
    
    fclose(fin);
}


comando_e leggi_comando(void){
    comando_e c;
    char comando[20];
    char tabella[r_fine][MAX_LEN_STR] = {
        "date", "partenza", "capolinea", "ritardo", "ritardo_totale"
    };
    printf("Inserire comando (date/partenza/capolinea/ritardo/ritardo_totale):");
    scanf("%s", comando);
    c = r_date;
    while(c < r_fine && strcmp(comando, tabella[c]) != 0){
        c++;
    }
    return (c);
}


/* Elencare tutte le corse partite in un certo intervallo di date */
void ricerca_per_data(dizionario diz[1000], int num_valori){
    char data_inizio[MAX_LEN_STR], data_fine[MAX_LEN_STR];
    int data_inizio_convertita, data_fine_convertita, count = 0;

    printf("Inserire la data di inizio (formato: aaaa/mm/gg): ");
    scanf("%s", data_inizio);
    printf("Inserire la data di fine (formato: aaaa/mm/gg): ");
    scanf("%s", data_fine);

    data_inizio_convertita = converti_data_in_ore(data_inizio);
    data_fine_convertita = converti_data_in_ore(data_fine);

    printf("VISUALIZZIAMO TUTTE LE CORSE CHE SONO PARTITE TRA IL %s e il %s \n\n", data_inizio, data_fine);
    for(int i = 0; i < num_valori; i++){
        int data_inizio_corrente = converti_data_in_ore(diz[i].data);
        if(data_inizio_corrente > data_inizio_convertita && data_inizio_corrente < data_fine_convertita){
            printf("%s %s %s %s %s %s %d \n", diz[i].codice, diz[i].partenza, diz[i].destinazione, diz[i].data, diz[i].ora_partenza, diz[i].ora_arrivo, diz[i].ritardo);
            count++;
        }
    }

    if(count == 0){
        printf("Non ci sono corse che sono partite tra il %s e il %s \n", data_inizio, data_fine);
    }

    exit(0);
}


/* Elencare tutti le corse partite da una certa fermata */
void ricerca_per_fermata(dizionario diz[1000], int num_valori){
    char fermata[MAX_LEN_STR];
    int count = 0;
    printf("Inserire il nome della fermata di interesse: ");
    scanf("%s", fermata);
    printf("\n");

    printf("VISUALIZZIAMO TUTTE LE CORSE CHE SONO PARTITE DA: %s \n", fermata);

    for(int i = 0; i < num_valori; i++){
        if(strcmp(fermata, diz[i].partenza) == 0){
            printf("%s %s %s %s %s %s %d", diz[i].codice, diz[i].partenza, diz[i].destinazione, diz[i].data, diz[i].ora_partenza, diz[i].ora_arrivo, diz[i].ritardo);
            printf("\n");
            count++;
        }
    }

    if (count == 0){
        printf("Non ci sono corse che sono partite da: %s", fermata);
    }
    exit(0);
}


/* Elencare tutti le corse che fanno capolinea in una certa fermata */
void ricerca_per_capolinea(dizionario diz[1000], int num_valori){
    char fermata[MAX_LEN_STR];
    int count = 0;
    printf("Inserire il nome della fermata di interesse: ");
    scanf("%s", fermata);
    printf("\n");

    printf("VISUALIZZIAMO TUTTE LE CORSE CON CAPOLINEA A: %s \n", fermata);

    for(int i = 0; i < num_valori; i++){
        if(strcmp(fermata, diz[i].destinazione) == 0){
            printf("%s %s %s %s %s %s %d", diz[i].codice, diz[i].partenza, diz[i].destinazione, diz[i].data, diz[i].ora_partenza, diz[i].ora_arrivo, diz[i].ritardo);
            printf("\n");
            count++;
        }
    }

    if (count == 0){
        printf("Non ci sono corse che fanno capolinea a: %s", fermata);
    }
    exit(0);
}


/* Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date */
void ricerca_per_ritardo_in_date(dizionario diz[1000], int num_valori){
    char data_inizio[MAX_LEN_STR], data_fine[MAX_LEN_STR];
    int data_inizio_convertita, data_fine_convertita, count = 0;

    printf("Inserire la data di inizio (formato: aaaa/mm/gg): ");
    scanf("%s \n", &data_inizio);
    printf("Inserire la data di fine (formato: aaaa/mm/gg): ");
    scanf("%s \n", &data_fine);

    data_inizio_convertita = converti_data_in_ore(data_inizio);
    data_fine_convertita = converti_data_in_ore(data_fine);

    for(int i = 0; i < num_valori; i++){
        int data_inizio_corrente = converti_data_in_ore(diz[i].data);
        if(data_inizio_corrente > data_inizio_convertita && data_inizio_corrente < data_fine_convertita && diz[i].ritardo > 0){
            printf("%s %s %s %s %s %s %d \n", diz[i].codice, diz[i].partenza, diz[i].destinazione, diz[i].data, diz[i].ora_partenza, diz[i].ora_arrivo, diz[i].ritardo);
            count++;
        }
    }

    if(count == 0){
        printf("Non ci sono corse arrivate in ritardo nelle date %s - %s", data_inizio, data_fine);
    }

    exit(0);
}


/* elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta */
void ritardo_totale_per_tratta(dizionario diz[1000], int num_valori){
    char codice[MAX_LEN_STR];

    int ritardo = 0, count = 0;;
    printf("Inserire il codice della tratta di interesse: ");
    scanf("%s", codice);

    for(int i = 0; i < num_valori; i++){
        if(strcmp(codice, diz[i].codice) == 0){
            ritardo = ritardo + diz[i].ritardo;
            count++;
        }
    }

    if(count == 0){
        printf("Non ci sono corse con il codice: %s", codice);
    }else{
        printf("Il ritardo totale accumulato dalla corsa %s è in totale: %d minuti", codice, ritardo);
    }

    exit(0);
}


int converti_data_in_ore(char data[MAX_LEN_STR]){
    int anno, mese, giorno;
    int valore;
    if(sscanf(data, "%d/%d/%d", &anno, &mese, &giorno) != 3){
        printf("Il formato della data è errato!");
        return 0;
    }
    valore = anno*365*24 + mese*30*24 + giorno*24;
    return valore;
}
