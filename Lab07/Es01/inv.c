#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    int statistiche[6];
    statistiche[0] = statp->hp;
    statistiche[1] = statp->mp;
    statistiche[2] = statp->atk;
    statistiche[3] = statp->def;
    statistiche[4] = statp->mag;
    statistiche[5] = statp->spr;

    for(int i = 0; i < 6; i++){
        if(statistiche[i] < soglia) statistiche[i] = soglia;
    }

    fprintf(fp, "%d %d %d %d %d %d", statistiche[0],statistiche[1], statistiche[2], statistiche[3], statistiche[4], statistiche[5]);
}

void inv_read(FILE *fp, inv_t *invp){
    while(fp != EOF){
        fscanf("%s %s", invp->nome, invp->tipo);
        stat_read(fp, &invp->stat);
    }
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s %d %d %d %d %d %d", invp->nome, invp->tipo, invp->stat.hp, invp->stat.mp, invp->stat.atk, invp->stat.def, invp->stat.mag, invp->stat.spr);
}

stat_t inv_getStat(inv_t *invp)
{
    return invp->stat;
}
