# include "es.h"


//es1
typedef struct {
    char name[16];
    int val;
} Item;

typedef struct node *link;
struct node{
    Item val;
    link next;
};

struct slist{
    link head;
};


SLIST SLISTmerge(SLIST a, SLIST b){
    SLIST new_lista = ITEMsetNULL();
    link x, p;

    //ciclo su prima lista
    for(x = a->head; x != NULL; x = x->next){
        if(non_presente(x, new_lista)){
            Item new_val;
            strcpy(new_val.name, x->val.name);
            new_val.val = 0;
            for(p = x->next; p != NULL; p = p->next){
                if(strcmp(x->val.name, p->val.name) == 0) new_val.val += p->val.val;
            }
            for(p = b->head; p != NULL; p = p->next){
                if(strcmp(x->val.name, p->val.name) == 0) new_val.val += p->val.val;
            }
            new_lista->head = SLISTinsert(new_val, new_lista);
        }
    }
    //ciclo su seconda lista
    for(x = b->head; x != NULL; x = x->next){
        if(non_presente(x, new_lista)){
            Item new_val;
            strcpy(new_val.val, x->val.name);
            new_val.val = 0;
            for(p = x->next; p != NULL; p = p->next){
                if(strcmp(x->val.name, p->val.name) == 0) new_val.val += p->val.val;
            }
            for(p = a->head; p != NULL; p = p->next){
                if(strcmp(x->val.name, p->val.name) == 0) new_val.val += p->val.val;
            }
            new_lista->head = SLISTinsert(new_val, new_lista);
        }
    }
    return new_lista;
}

int non_presente(link x, SLIST list){
    int non_presente = 1;
    for(link p = list->head; p != NULL; p = p->next){
        if(strcmp(x->val.name, p->val.name) == 0) non_presente = 0;
    } 
    return non_presente;
}

link SLISTinsert(Item x, SLIST lista){
    if(lista->head == NULL || strcmp(x.name, lista->head->val.name) < 0) return newNode(x, lista->head);
    link y, p, h;
    for(y = lista->head->next, p = lista->head; y != NULL; p = y, y = y->next){
        if(strcmp(x.name, y->val.name) < 0){
            h = newNode(x, y);
            p->next = h;
            return h;
        }
    }
    p->next = newNode(x, NULL);
    return p->next;
}


//es2
typedef struct n *l;
struct n{
    link2 val;
    l next;
};
typedef struct node2 *link2;
struct node2{
    int val;
    link2 left;
    link2 right;
};

struct bst{
    link2 root;
};

int conta_nodi(BST b){
    return conta(b->root);
}

int conta(link2 h){
    if(h == NULL) return 0;
    return conta(h->left) + conta(h->right) + 1;
}

int *BSTlevelizedNodes (BST b, int *n){
    *n = conta_nodi(b);
    link2 *vett = (link2*)malloc((*n)*sizeof(link2));
    l *vett_liste = calloc(*n, sizeof(l));

    riempi_lista(b->root, vett_liste, 0);
    int cnt = 0;
    for(int i = 0; i < (*n); i++){
        for(l x = vett_liste[i]; x != NULL; x = x->next){
            vett[cnt++] = x->val;
        }
    }
    return vett;
}

void riempi_lista(link2 h, l *lista, int prof){
    if(h == NULL) return;
    riempi_lista(h->left, lista, prof+1);
    riempi_lista(h->right, lista, prof+1);

    inserisci_in_lista(&lista[prof], h);
}

void inserisci_in_lista(l *lista, link2 val){
    if(*lista == NULL){
        *lista = newNode(val, NULL);
        return;
    }
    l x, p;
    for(x = *lista, p = NULL; x != NULL; p = x, x = x->next){
        if(x == *lista && val->val < x->val->val){
            *lista = newNode(val, x);
            return;
        }
        if(val->val < x->val->val){
            p->next = newNode(val, x);
            return;
        }
    }
}


//es3
char *bestConcat (char **parole, int nparole) {
    int *mark = calloc(nparole, sizeof(int));
    char **sol = malloc(nparole*sizeof(char*));
    char **best_sol = malloc(nparole*sizeof(char*));
    int best_char_sol = 0;
    for(int i = 0; i < nparole; i++){
        disp_semplici(0, parole, nparole, i, sol, 0, best_sol, &best_char_sol, 0, mark);
    }
    char *result = (char*)malloc(best_char_sol*sizeof(char));
    result[0] = '\0';
    for(int i = 0; i < nparole && best_sol[i] != NULL; i++) strcat(result, best_sol[i]);
    return result;
}

void disp_semplici(int pos, char **parole, int nparole, int k, char **sol, int act_sol, char **best_sol, int *best_char_sol, int num_parole, int *mark){
    if(pos >= k){
        if(act_sol > *best_char_sol){
            *best_char_sol = act_sol;
            for(int i = 0; i < num_parole; i++){
                best_sol[i] = sol[i];
            }
        }
    }

    for(int i = 0; i < k ; i++){
        if(mark[i] == 0 && check_ok(sol[act_sol], parole[i])){
            mark[i] = 1;
            sol[pos] = parole[i];
            disp_semplici(pos+1, parole, nparole, k, sol, act_sol + strlen(parole[i]), best_sol, best_char_sol, num_parole+1, mark);
            mark[i] = 0;
        }
    }
}

int check_ok(char *sol, char *parola){
    int ok = 0;
    if((sol[strlen(sol)-1] == 'A' || sol[strlen(sol)-1] == 'E' || sol[strlen(sol)-1] == 'I' || sol[strlen(sol)-1] == 'O' || sol[strlen(sol)-1] == 'U')
    && (parola[0] != 'A' && parola[0] != 'E' && parola[0] != 'I' && parola[0] != 'O' && parola[0] != 'U')) ok = 1;

    if((sol[strlen(sol)-1] != 'A' && sol[strlen(sol)-1] != 'E' && sol[strlen(sol)-1] != 'I' && sol[strlen(sol)-1] != 'O' && sol[strlen(sol)-1] != 'U')
    && (parola[0] == 'A' || parola[0] == 'E' || parola[0] == 'I' || parola[0] == 'O' || parola[0] == 'U')) ok = 1;
    return ok;
}
