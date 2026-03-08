#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 30

int strContains(char *s1, char *s2);
int verifica_uguaglianza(int pos, int dim, char *s1, char *s2, int cnt, char *sol, int *mark);

int strContains(char *s1, char *s2)
{
    int l1 = strlen(s1), l2 = strlen(s2);
    int caratteri_da_rimuovere = l1 - l2;
    int cnt = 0, dim_soluzione = l1 - caratteri_da_rimuovere;
    char *sol = (char *)malloc((dim_soluzione+1) * sizeof(char));
    sol[dim_soluzione] = '\0';
    int *mark = calloc(l1,sizeof(int));
    int risultato = verifica_uguaglianza(0, dim_soluzione, s1, s2, cnt, sol, mark);
    free(sol);
    free(mark);
    return risultato;
}

int verifica_uguaglianza(int pos, int dim, char *s1, char *s2, int cnt, char *sol, int *mark)
{
    if (pos >= dim)
        return (strcmp(s2, sol) == 0);
    
    for (int i = 0; i < strlen(s1); i++)
    {
        if (mark[i] == 0)
        {
            mark[i] = 1; 
            sol[pos] = s1[i];
            if(verifica_uguaglianza(pos + 1, dim, s1, s2, cnt + 1, sol, mark)) return 1;
            mark[i] = 0;
        }
        
    }
    return 0;
}

int main()
{
    char s1[len], s2[len];

    printf("Inserisci la stringa s1: ");
    scanf("%s", s1);

    printf("Inserisci la stringa s2: ");
    scanf("%s", s2);

    int risultato = strContains(s1, s2);

    if (risultato)
        printf("Si, è possibile ottenere la stringa s2 da s1\n");
    else
        printf("No, non è possibile ottenere la stringa s2 da s1\n");

    return 0;
}