#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int anno, mese, giorno;
}data_s;

typedef struct{
    int ora, minuti;
}ora_s;

typedef struct{
    data_s data;
    ora_s ora;
}datatime;

datatime leggi_data_e_ora(FILE *fin);
int confronta_date(data_s d1, data_s d2);
int converti_data(data_s d);