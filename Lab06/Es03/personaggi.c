#include "personaggi.h"
#include <stdlib.h>
#include <string.h>

link newNode(personaggio_t pers, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL) return NULL;

    x->val = pers;
    x->next = next;

    return x;
}


link inserisci_personaggio(link head, personaggio_t pers){
    link x;
    if(head == NULL){
        return newNode(pers, head);
    }else{
        for(x = head; x->next != NULL; x = x->next);
        x->next = newNode(pers, NULL);
    }
    return head;
}


link leggi_personaggi(FILE *fin){
    char codice[7], nome[51], classe[51];
    int hp, mp, atk, def, mag, spr;
    personaggio_t pers;
    link head = NULL;
    
    while(fscanf(fin, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) == 9){
        pers.codice = strdup(codice);
        pers.nome = strdup(nome);
        pers.classe = strdup(classe);
        pers.stat.hp = hp;
        pers.stat.mp = mp;
        pers.stat.atk = atk;
        pers.stat.def = def;
        pers.stat.mag = mag;
        pers.stat.spr = spr;
        pers.num_equipaggiamenti = 0;
        pers.equipaggiamento = (oggetto_t*)malloc(8*sizeof(oggetto_t));

        head = inserisci_personaggio(head, pers);
    }

    return head;
}


personaggio_t *cerca_personaggio(link head, char *codice){
    link x;
    for(x = head; x != NULL; x = x->next){
        if((strcmp(x->val.codice, codice) == 0)){
            return &x->val;
        }
    }
    return NULL;
}


link elimina_personaggio(link head, char *codice){
    link x, p;

    for(x = head, p = NULL; x != NULL; p = x, x = x->next){
        if(strcmp(x->val.codice, codice) == 0){
            if(p == NULL){
                head = x->next;
            }else{
                p->next = x->next;
                free(x->val.nome);
                free(x->val.codice);
                free(x->val.classe);
                free(x->val.equipaggiamento);
                free(x);
                return head;
            }
        }
    }
    printf("Non è stato trovato alcun personaggio con questo codice!");
    return head;
}


void stampa_informazioni_personaggio(personaggio_t *pers){
    printf("%s %s %s %d %d %d %d %d %d", pers->codice, pers->nome, pers->classe, pers->stat.hp, pers->stat.mp, pers->stat.atk, pers->stat.def, pers->stat.mag, pers->stat.spr);
    printf("\n");
    printf("Equipaggiamento: \n");
    if(pers->num_equipaggiamenti > 0){
        for(int i = 0; i < pers->num_equipaggiamenti; i++){
            printf("%s %s %d %d %d %d %d %d\n", pers->equipaggiamento[i].nome, pers->equipaggiamento[i].tipologia, pers->equipaggiamento[i].mod.hp, pers->equipaggiamento[i].mod.mp, pers->equipaggiamento[i].mod.atk, pers->equipaggiamento[i].mod.def, pers->equipaggiamento[i].mod.mag, pers->equipaggiamento[i].mod.spr);
        }
    }else{
        printf("Non ci sono equipaggiamenti per questo personaggio!\n");
    }
    
    return;
}


void stampa_tutti_i_personaggi(link head){
    link x;
    for(x = head; x != NULL; x = x->next){
        stampa_informazioni_personaggio(&x->val);
        calcola_statistiche(&x->val);
    }
    return;     
}


void aggiungi_equipaggiamento(personaggio_t *pers, oggetto_t *ogg){
    if(pers->num_equipaggiamenti >= 8){
        printf("Non è più possibile aggiungere equipaggiamenti per questo personaggio! \n"); return;
    }

    pers->equipaggiamento[pers->num_equipaggiamenti].nome = strdup(ogg->nome);
    pers->equipaggiamento[pers->num_equipaggiamenti].tipologia = strdup(ogg->tipologia);
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.hp = ogg->mod.hp;
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.mp = ogg->mod.mp;
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.atk = ogg->mod.atk;
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.def = ogg->mod.def;
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.mag = ogg->mod.mag;
    pers->equipaggiamento[pers->num_equipaggiamenti].mod.spr = ogg->mod.spr;
    pers->num_equipaggiamenti += 1;

    return;
}


void elimina_equipaggiamento(personaggio_t *pers, oggetto_t *ogg){
    for(int i = 0; i < pers->num_equipaggiamenti; i++){
        if(strcmp(pers->equipaggiamento[i].nome, ogg->nome) == 0){
            free(pers->equipaggiamento[i].nome);
            free(pers->equipaggiamento[i].tipologia);
            for(int j = i; j < pers->num_equipaggiamenti - 1; j++){
                pers->equipaggiamento[j] = pers->equipaggiamento[j+1];
            }
            pers->num_equipaggiamenti -= 1;
        }
    }
}


link aggiungi_personaggio_manualmente(link head){
    personaggio_t pers;
    char codice[7], nome[51], classe[51];
    printf("Inserire codice: "); 
    scanf("%s", codice);
    pers.codice = strdup(codice);
    printf("Inserire nome: "); 
    scanf("%s", nome);
    pers.nome = strdup(nome);
    printf("Inserire classe: "); 
    scanf("%s", classe);
    pers.classe = strdup(classe);
    printf("Inserire valore hp: "); 
    scanf("%d", &pers.stat.hp);
    printf("Inserire valore mp: "); 
    scanf("%d", &pers.stat.mp);
    printf("Inserire valore atk: "); 
    scanf("%d", &pers.stat.atk);
    printf("Inserire valore def: "); 
    scanf("%d", &pers.stat.def);
    printf("Inserire valore mag: "); 
    scanf("%d", &pers.stat.mag);
    printf("Inserire valore spr: "); 
    scanf("%d", &pers.stat.spr);
    pers.num_equipaggiamenti = 0;
    pers.equipaggiamento = (oggetto_t*)malloc(8*sizeof(oggetto_t));

    head = inserisci_personaggio(head, pers);
    return head;
}


void calcola_statistiche(personaggio_t *pers){
    int sum_hp = 0, sum_mp = 0, sum_atk = 0, sum_def = 0, sum_mag = 0, sum_spr = 0;
    for(int i = 0; i < pers->num_equipaggiamenti; i++){
        sum_hp += pers->equipaggiamento[i].mod.hp;
        sum_mp += pers->equipaggiamento[i].mod.mp;
        sum_atk += pers->equipaggiamento[i].mod.atk;
        sum_def += pers->equipaggiamento[i].mod.def;
        sum_mag += pers->equipaggiamento[i].mod.mag;
        sum_spr += pers->equipaggiamento[i].mod.spr;
    }
    sum_hp += pers->stat.hp;
    sum_mp += pers->stat.mp;
    sum_atk += pers->stat.atk;
    sum_def += pers->stat.def;
    sum_mag += pers->stat.mag;
    sum_spr += pers->stat.spr;
    if(sum_hp < 0) sum_hp = 0;
    if(sum_mp < 0) sum_mp = 0;
    if(sum_atk < 0) sum_atk = 0;
    if(sum_def < 0) sum_def = 0;
    if(sum_mag < 0) sum_mag = 0;
    if(sum_spr < 0) sum_spr = 0;

    printf("Statistiche: %d %d %d %d %d %d\n\n", sum_hp, sum_mp, sum_atk, sum_def, sum_mag, sum_spr);
}