#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "equipArray.h"

struct equipArray_s{
    int array_index[EQUIP_SLOT];
    int num_oggetti;
};

equipArray_t equipArray_init(){
    equipArray_t eqArr = malloc(sizeof(equipArray_t));
    eqArr->num_oggetti = 0;
    return eqArr;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->num_oggetti;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for(int i = 0; i < equipArray->num_oggetti; i++){
        invArray_printByIndex(fp, invArray, equipArray->array_index[i]);
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray)
{
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->array_index[index];
}
