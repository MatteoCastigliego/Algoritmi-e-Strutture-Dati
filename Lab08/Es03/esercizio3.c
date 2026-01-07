#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "F1.txt"

int main(){
    FILE *fin = fopen(filename, "r");
    if (fin == NULL){
        printf("Errore nell'apertura del file %s", filename);
        return;
    }

    
}