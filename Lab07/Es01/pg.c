#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if(fp == NULL) return -1;

    char cod[LEN], nome[LEN], classe[LEN];
    fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_read(fp, &pgp->b_stat);
    pgp->equip = equipArray_init();
    return 0;
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fscanf(fp, "%s %s %s", &pgp->cod, &pgp->nome, &pgp->classe);
    invArray_print(fp, invArray);
}
