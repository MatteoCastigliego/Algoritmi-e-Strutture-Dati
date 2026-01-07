#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "very_easy_test_set.txt"

char *disposizioni_semplici(int pos, char *str, char *sol, int *mark, int n, int cnt, int k, int *max, char *result);
char *combinazioni_semplici(int pos, char *str, char *sol, int start, int n, int k, char *result);
int valida(char *s, int len);
void conta_occorrenze(char *collana, int *r, int *s, int *z, int *t);

int main()
{
    FILE *fin = fopen(filename, "r");
    if (fin == NULL){
        printf("Errore nell'apertura del file di input!");
        return -1;
    }

    int num_pietre = 0, num_collane = 0, num_zaffiri = 0, num_topazi = 0, num_rubini = 0, num_smeraldi = 0;
    fscanf(fin, "%d", &num_collane);

    for(int i = 0; i < num_collane; i++){
        fscanf(fin, "%d %d %d %d", &num_zaffiri, &num_rubini, &num_topazi, &num_smeraldi);

        num_pietre = num_zaffiri + num_rubini + num_smeraldi + num_topazi;
        char *stringa = (char *)malloc((num_pietre + 1) * sizeof(char));

        for (int i = 0; i < num_zaffiri; i++){
            stringa[i] = 'z';
        }
        for (int i = num_zaffiri; i < (num_rubini + num_zaffiri); i++){
            stringa[i] = 'r';
        }
        for (int i = (num_rubini + num_zaffiri); i < (num_rubini + num_zaffiri + num_topazi); i++){
            stringa[i] = 't';
        }
        for (int i = (num_rubini + num_zaffiri + num_topazi); i < (num_rubini + num_zaffiri + num_topazi + num_smeraldi); i++){
            stringa[i] = 's';
        }
        stringa[num_pietre] = '\0';

        printf("%s \n", stringa);

        int max = 0;
        char *result = malloc(sizeof(char));
        for (int i = 2; i <= num_pietre; i++){
            char *sol = (char *)malloc((i + 1) * sizeof(char));
            int *mark = calloc(num_pietre, sizeof(int));
            result = disposizioni_semplici(0, stringa, sol, mark, num_pietre, 0, i, &max, result);
        }
        printf("La combinazione valida più lunga è formata da %d pietre \n", max);
        printf("{ %s }", result); printf("\n");

        int r_occ = 0, z_occ = 0, t_occ = 0, s_occ = 0;
        conta_occorrenze(result, &r_occ, &s_occ, &z_occ, &t_occ);
        printf("In questa disposizione sono presenti %d zaffiri, %d topazi, %d smeraldi e %d rubini.", z_occ, t_occ, s_occ, r_occ); printf("\n");
        free(stringa);
        free(result);
    }
    
    fclose(fin);

}


char *disposizioni_semplici(int pos, char *str, char *sol, int *mark, int n, int cnt, int k, int *max, char *result) {
    if (pos >= k) {
        sol[pos] = '\0';
        if (valida(sol, k)) {  // controllo completo solo alla fine
            if (k > *max) {
                *max = k;
                result = realloc(result, (k + 1) * sizeof(char));
                strcpy(result, sol);
            }
        }
        return result;
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            sol[pos] = str[i];

            // PRUNING: controllo parziale solo con l'ultimo inserito
            int valido = 1;
            if (pos > 0) {
                char prev = sol[pos - 1];
                char curr = sol[pos];
                if (prev == 'z' && curr != 'z' && curr != 'r') valido = 0;
                else if (prev == 'r' && curr != 's' && curr != 't') valido = 0;
                else if (prev == 't' && curr != 'z' && curr != 'r') valido = 0;
                else if (prev == 's' && curr != 's' && curr != 't') valido = 0;
            }

            if (!valido) continue; // fermati se violata la regola

            mark[i] = 1;
            result = disposizioni_semplici(pos + 1, str, sol, mark, n, cnt, k, max, result);
            mark[i] = 0;
        }
    }

    return result;
}

int valida(char *s, int len){
    int ok = 1;
    for (int i = 0; i < len && ok == 1; i++){
        if (i != (len - 1)){
            if (s[i] == 'z'){
                if (s[i + 1] != 'z' && s[i + 1] != 'r'){
                    ok = 0;
                }
            }
            else if (s[i] == 'r'){
                if (s[i + 1] != 's' && s[i + 1] != 't'){
                    ok = 0;
                }
            }
            else if (s[i] == 't'){
                if (s[i + 1] != 'z' && s[i + 1] != 'r'){
                    ok = 0;
                }
            }
            else if (s[i] == 's'){
                if (s[i + 1] != 's' && s[i + 1] != 't'){
                    ok = 0;
                }
            }
        }
        else{
            if (s[i] == 'z'){
                if (s[0] != 'z' && s[0] != 'r'){
                    ok = 0;
                }
            }
            else if (s[i] == 'r'){
                if (s[0] != 's' && s[0] != 't'){
                    ok = 0;
                }
            }
            else if (s[i] == 't'){
                if (s[0] != 'z' && s[0] != 'r'){
                    ok = 0;
                }
            }
            else if (s[i] == 's'){
                if (s[0] != 's' && s[0] != 't'){
                    ok = 0;
                }
            }
        }
    }
    return ok;
}

void conta_occorrenze(char *collana, int *r, int *s, int *z, int *t){
    for(int i = 0; i < strlen(collana); i++){
        if(collana[i] == 'r') *r += 1;
        else if(collana[i] == 's') *s += 1;
        else if(collana[i] == 'z') *z += 1;
        else if(collana[i] == 't') *t += 1;
    }
}
