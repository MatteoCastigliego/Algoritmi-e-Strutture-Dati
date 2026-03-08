#include "es.h"

//TEMA D'ESAME 20222/2023
//es 1
void f(int **M, int r, int c, int k, int ***mf){
    int **M2 = alloca_matrice(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            for(int x = 1; x <= k; x++){
                if((j+x) < c) M2[i][j] += M[i][j+x];
                if((j-x) >= 0) M2[i][j] += M[i][j-x];
                if((i+x) < r) M2[i][j] += M[i+x][j];
                if((i-x) >= 0) M2[i][j] += M[i-x][j];
            }
        }
    }
    *mf = M2;
}

int **alloca_matrice(int r, int c){
    int **m = (int**)malloc(r*sizeof(int*));
    for(int i = 0; i < r; i++){
        m[i] = calloc(c, sizeof(int));
    }
    return m;
}

//es2
//list.c
typedef struct node *link;
struct node{
    char val; 
    link next; 
    link prev;
};
struct list{
    link head;
};

void f(LIST l, int k){
    link x, p, tmp;
    int cnt;
    for(x = l->head, p = NULL; x != NULL; ){
        if(p == NULL){
            cnt = 1;
        } 
        if(p != NULL && x->prev->val != x->val){
            cnt = 1;
        }
        p = x;
        x = x->next;
        if (x->val == x->prev) cnt++;
        if(x->next->val != x->val && cnt >= k){
            while(cnt > 1){
                tmp = p;
                x->prev = p->prev;
                p = p->prev;
                free(tmp);
                cnt--;
            }
        }
    }
}

//es3
char *BESTbestConcat (char **parole, int nparole){
    int best_sol_len = 0;
    char **sol = (char**)malloc(nparole*sizeof(char*));
    char **best_sol = (char**)malloc(nparole*sizeof(char*));
    int *mark = malloc(nparole*sizeof(int));
    int sol_char_len = 0;
    backtrack(parole, nparole, sol, 0, mark, best_sol, &best_sol_len, sol_char_len);
    
    
    char *vett_sol = (char*)malloc((best_sol_len+1)*sizeof(char));
    vett_sol[0] = '\0';
    for(int i =0; i < best_sol_len; i++) strcat(vett_sol, best_sol[i]);
    return vett_sol;
}

void backtrack(char **parole, int nparole, char **sol, int sol_len, int *mark, char **best_sol, int *best_sol_len, int sol_char_len){
        
        for(int i = 0; i < sol_len; i++) sol_char_len += strlen(sol[i]);
        if(sol_char_len > *best_sol_len){
            *best_sol_len = sol_char_len;
            for(int i = 0; i < sol_len; i++){
                best_sol[i] = sol[i];
            }
        }
    
    for(int i = 0; i < nparole; i++){
        if(mark[i] == 0 && check_ok(sol[sol_len-1], parole[i])){
            mark[i] = 1;
            sol[sol_len] = parole[i];
            backtrack(parole, nparole, sol, sol_len+1, mark, best_sol, &best_sol_len, sol_char_len+strlen(parole[i]));
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
