#include <stdlib.h>
#include <stdio.h>
#define filename "grafo.txt"

int disp_semplici(int pos, int n, int *vet, int *mark, int *sol, int cnt, int k);

int main()
{
    FILE *fin = fopen(filename, "r");
    if (fin == NULL)
    {
        printf("Errore nell'apertura del file di input!");
        return -1;
    }

    int num_archi, num_vertici;
    fscanf(fin, "%d %d", &num_vertici, &num_archi);

    int *vett = (int *)malloc(num_vertici * sizeof(int));
    if (vett == NULL)
    {
        printf("Errore nell'allocazione del vettore!");
        return -1;
    }

    for (int i = 0; i < num_vertici; i++)
    {
        vett[i] = i;
    }

    printf("Vettore:");
    printf("\n");
    for (int i = 0; i < num_vertici; i++)
    {
        printf("%d ", vett[i]);
    }

    int tot_disp = 0;

    for (int i = 2; i <= num_vertici; i++)
    {
        int *mark = calloc(num_vertici, sizeof(int));
        if (mark == NULL)
        {
            printf("Errore nel'allocazione del vettore mark!");
            return -1;
        }

        int *sol = (int *)malloc(i * sizeof(int));
        if (sol == NULL)
        {
            printf("Errore nell'allocazione del vettore sol!");
            return -1;
        }

        printf("Ecco tutte le possibili disposizioni: di lunghezza %d\n", i);

        tot_disp = tot_disp + disp_semplici(0, num_vertici, vett, mark, sol, 0, i);
    }
}

int disp_semplici(int pos, int n, int *vet, int *mark, int *sol, int cnt, int k)
{
    if (pos >= k)
    {
        if (sol[0] == 0)
        {
            printf("{");
            for (int i = 0; i < k; i++)
            {
                printf("%d ", sol[i]);
            }
            printf("}");
            printf("\n");
            return cnt + 1;
        }
    }

    for (int i = 0; i < k; i++)
    {
        if (mark[i] == 0)
        {
            mark[i] = 1;
            sol[pos] = vet[i];
            cnt = disp_semplici(pos + 1, n, vet, mark, sol, cnt, k);
            mark[i] = 0;
        }
    }
    return cnt;
}