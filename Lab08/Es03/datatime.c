#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatime.h"

datatime leggi_data_e_ora(FILE *fin){
    datatime temp;
    int anno, mese, giorno, ora, minuti;
    fscanf("%d/%d/%d %d:%d", &anno, &mese, &giorno, &ora, &minuti);
    temp.data.anno = anno;
    temp.data.mese = mese;
    temp.data.giorno = giorno;
    temp.ora.ora = ora;
    temp.ora.minuti = minuti;
    return temp;
}

int confronta_date(data_s d1, data_s d2){
    int data1 = converti_data(d1);
    int data2 = converti_data(d2);

    return data1 - data2;
}

int converti_data(data_s d){
    return d.anno * 10000 + d.mese * 100 + d.giorno;
}
