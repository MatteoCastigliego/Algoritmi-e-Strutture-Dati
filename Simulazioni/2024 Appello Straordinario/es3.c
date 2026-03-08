/*
* Si scriva una funzione che date due stringhe, ne trovi la più lunga sottosequenza comune. 
* La funzione ha prototipo: 'char *maxSubs(char *s1, char *s2);'
* Si ricorda che una stringa è una sequenza di caratteri (terminata da '\0'),
* e che una sottosequenza è un sottoinsieme (ordinato) di elementi di una sequenza, non necessariamente contigui.
* Ad esempio, la più lunga sottosequenza comune a "una stringa" e "narrativa" è "nati" ("una stringa" e "narrativa").
* La stringa risultato va allocata dinamicamente.
* Il problema sarebbe risolvibile mediante un approccio basato su programmazione dinamica,
* ma si richiede espressamente che sia risolto sfruttando uno dei modelli combinatori visti a lezione,
* di cui si chiede di fornire anche una breve giustificazione della scelta fatta.
*/

#include <stdio.h>

/* function prototype is strict, do not change it */
char *maxSubs(char *s1, char *s2);

/* function prototype is strict, do not change it */
char *maxSubs(char *s1, char *s2) {
	/* you code goes here */
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int max;
    if(l1 > l2) max = l1;
    else max = l2;
    char *sol = malloc(max*sizeof(char));
    char *best_sol = malloc(max*sizeof(char));
    int best_len = 0;
    for(int i = 1; i <= l1; i++){
        comb_semplici(0, s1, s2, sol, &best_len, best_sol, i, 0);
    }
    
    return best_sol;
}

void comb_semplici(int pos, char *s, char *s2, char *sol, int *best_len, char *best_sol, int act_len, int start){
	if(pos >= act_len){
		if(is_subsequence(sol, s2) && act_len > *best_len){
			*best_len = act_len;
			for(int i = 0; i < act_len; i++){
				best_sol[i] = sol[i];
			}
		}
        return; 
	}

	for(int i = start; s[i] != '\0'; i++){
		sol[pos] = s[i];
		comb_semplici(pos+1, s, s2, sol, best_len, best_sol, act_len, i+1);
	}
}

int is_subsequence(char *s1, char *s2){
    int si = 1, i = 0, j = 0;
    while(s1[i] != '\0' && s2[j] != '\0'){
        if(s1[i] == s2[j]){
            i++;
        }
        j++;
    }
    if((i++) != strlen(s1)) si = 0;
    return si;
}

int main(int argc, char **argv) {
	/* you can implement your test case here [NOT NEEDED] */
	return 0;
}