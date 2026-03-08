#include <stdio.h>
#include <stdlib.h>

/*

Due stringhe s1 e s2 possono essere concatenate se il prefisso (proprio) di ordine I di s2 coincide col suffisso (proprio) di ordine I di s1. 
Si ricorda che il prefisso (suffisso) di ordine I di una stringa è una sottostringa iniziale (terminale) di I elementi,
che si dice proprio se non coincide con la stringa stessa (I è minore della lunghezza della stringa).
Si scriva una funzione checkConcat che, date due stringhe, verifichi se possono essere concatenate. 
Si scriva poi una funzione che, dato un insieme S di stringhe, trovi la più lunga sequenza di stringhe concatenabili,
appartenenti all’insieme. 
L’insieme S è rappresentato come vettore. 
Non sono ammesse ripetizioni. come lunghezza (da massimizzare) si intende il conteggio delle stringhe nella sequenza.

La funzione abbia prototipo: 

int maxConcatSeq(char **S, int n);

*/

int maxConcatSeq(char **S, int n);
int checkConcat(char *s1, char *s2);

int maxConcatSeq(char **S, int n){
    int *mark = malloc(n*sizeof(int));
    char **sol = malloc(n*sizeof(char*));
    char **best_sol = malloc(n*sizeof(char*));
    int best_sol_len = 0;

    perm_semplici(0, S, n, mark, sol, 0, best_sol, &best_sol_len);
    return best_sol_len;
}

void perm_semplici(int pos, char **S, int n, int *mark, char **sol, int act_sol_len, char **best_sol, int *best_sol_len){
    if(pos >= n){
        if(act_sol_len > *best_sol_len){
            *best_sol_len = act_sol_len;
            for(int i = 0; i < *best_sol_len; i++){
                best_sol[i] = sol[i];
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(mark[i] == 0 && (pos == 0 || checkConcat(sol[pos-1], S[i]))){
            mark[i] = 1;
            sol[pos] = S[i];
            perm_semplici(pos+1, S, n, mark, sol, act_sol_len+1, best_sol, best_sol_len);
            mark[i] = 0;
        }
    }
}

int checkConcat(char *s1, char *s2)
{
    int l1 = strlen(s1), l2 = strlen(s2), min;
    if(l1 < l2) min = l1;
    else min = l2;

    for(int i = 1; i < min; i++){
        int concat = 1;
        for(int k = 0; k < i; k++){
            if(s1[l1-i+k] != s2[k]) concat = 0;
        }
        if(concat) return concat;
    }
    return 0;
}
