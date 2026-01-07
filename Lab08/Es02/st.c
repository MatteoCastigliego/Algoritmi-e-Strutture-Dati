#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"


struct symbletable{
    char **nomi;
    int N;
    int maxN;
};

ST STinit(int maxN){
    ST st = malloc(sizeof(*st));
    st->nomi = (char**)malloc(maxN*sizeof(char*));
    st->N = 0;
    st->maxN = maxN;
    return st;
}

int STcount(ST st){
    return st->N;
}

void STinsert(ST st, char *name){
    int id = STgetIndex(st, name);
    if(id != -1) return;

    int i = st->N-1;
    while(i >= 0 && strcmp(st->nomi[i], name) > 0){
        st->nomi[i+1] = st->nomi[i];
        i--;
    }
    st->nomi[i+1] = strdup(name);
    st->N++;
}

int STgetIndex(ST st, char *name){
    for(int i = 0; i < st->N; i++){
        if(strcmp(st->nomi[i], name) == 0){
            return i;
        }
    }
    return -1;
}

char *STgetName(ST st, int index){
    return st->nomi[index];
}

void STfree(ST st){
    for(int i = 0; i < st->N; i++){
        free(st->nomi[i]);
    }
    free(st->nomi);
    free(st);
}

void STprint(ST st){
    for(int i = 0; i < st->N; i++){
        printf("%s\n", st->nomi[i]);
    }
}
