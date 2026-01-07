#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"


struct invArray_s{
    inv_t *vettEl;
    int num;
};


invArray_t invArray_init(){
    invArray_t arr = malloc(sizeof(invArray_t));
    arr->num = 0;
    return arr;
}

void invArray_free(invArray_t invArray){
    free(invArray->vettEl);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    int num_oggetti;
    if(fp != NULL){
        fscanf(fp, "%d", &num_oggetti);
        invArray->vettEl = malloc(num_oggetti*sizeof(invArray));
        invArray->num = num_oggetti;
    }
    for(int i = 0; i < num_oggetti; i++){
        inv_read(fp, &invArray->vettEl[i]);
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    for(int i = 0; i < invArray->num; i++){
        inv_print(fp, &invArray->vettEl[i]);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray_getByIndex(invArray, index));
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vettEl[index];
}

int invArray_searchByName(invArray_t invArray, char *name){
    for(int i = 0; i < invArray->num; i++){
        if(strcmp(name, invArray->vettEl[i].nome) == 0){
            return i;
        }
    }
    return -1;
}
