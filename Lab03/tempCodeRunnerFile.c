#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fileinput "anag1.txt"
#define fileoutput "output.txt"
#define MAX_LEN 50

typedef struct
{
    char *codice;
    char *nome;
    char *cognome;
    char *data_nascita;
    char *via;
    char *citta;
    int CAP;
} Anagrafica;

typedef Anagrafica Item;
typedef struct node *link;

struct node
{
    Item val;
    link next;
};

link newNode(Item val, link h);
link inserisci_in_lista(Item val, link h);
int converti_data(char *data);
void stampa_lista(link h);
void stampa_su_file(link h, FILE *fout);
void free_lista(link h);
void stampa_riga(Item p);
Item crea_copia(Item p);
Item ricerca_per_codice(link h);
Item estrai_e_cancella_elemento(link *h);

int main()
{
    FILE *fin = fopen(fileinput, "r");
    if (fin == NULL)
        printf("Errore nell'apertura del file di input!");

    FILE *fout = fopen(fileoutput, "w");
    if (fout == NULL)
        printf("Errore nella creazione e apertura del file di output!");

    char scelta;
    char codice[5], nome[MAX_LEN], cognome[MAX_LEN], data_nascita[MAX_LEN], via[MAX_LEN], citta[MAX_LEN];
    int CAP;
    Item persona;
    link head = NULL;

    while (1)
    {
        printf("Da dove vuoi inserire i dati, da tastiera o da file? (T/F, Q per uscire): ");
        scanf(" %c", &scelta);

        if (scelta == 'T')
        {
            printf("Inserisci codice (AXXXX): ");
            scanf("%s", codice);
            printf("Inserisci nome: ");
            scanf("%s", nome);
            printf("Inserisci cognome ");
            scanf("%s", cognome);
            printf("Inserisci data di nascita (gg/mm/aaaa): ");
            scanf("%s", data_nascita);
            printf("Inserisci via: ");
            scanf("%s", via);
            printf("Inserisci città: ");
            scanf("%s", citta);
            printf("Inserisci CAP: ");
            scanf("%d", &CAP);

            persona.CAP = CAP;
            persona.citta = strdup(citta);
            persona.codice = strdup(codice);
            persona.cognome = strdup(cognome);
            persona.nome = strdup(nome);
            persona.data_nascita = strdup(data_nascita);
            persona.via = strdup(via);

            head = inserisci_in_lista(persona, head);
        }

        if (scelta == 'F')
        {
            if (fscanf(fin, "%s %s %s %s %s %s %d", codice, nome, cognome, data_nascita, via, citta, &CAP) == 7)
            {
                persona.CAP = CAP;
                persona.citta = strdup(citta);
                persona.codice = strdup(codice);
                persona.cognome = strdup(cognome);
                persona.nome = strdup(nome);
                persona.data_nascita = strdup(data_nascita);
                persona.via = strdup(via);

                head = inserisci_in_lista(persona, head);
            }
            else
            {
                printf("I dati nel file sono finiti! \n");
            }
        }

        if (scelta == 'Q')
            break;
    }
    stampa_lista(head);
    printf("\n");

    stampa_su_file(head, fout);

    persona = ricerca_per_codice(head);
    if (persona.CAP != NULL)
        stampa_riga(persona);
    printf("\n");

    persona = estrai_e_cancella_elemento(&head);
    stampa_riga(persona);
    printf("\n");
    printf("Lista aggiornata: \n");
    stampa_lista(head);
    printf("\n");

    fclose(fin);
    fclose(fout);
    free_lista(head);
}

link newNode(Item val, link next)
{
    link x = malloc(sizeof *x);
    if (x == NULL)
    {
        printf("Errore allocazione nuovo nodo");
        return NULL;
    }
    x->val = val;
    x->next = next;
    return x;
}

link inserisci_in_lista(Item val, link h)
{
    link x, p;
    if (h == NULL || converti_data(val.data_nascita) < converti_data(h->val.data_nascita))
    {
        return newNode(val, h);
    }
    else
    {
        for (x = h->next, p = h; x != NULL; p = x, x = x->next)
        {
            if (converti_data(x->val.data_nascita) > converti_data(val.data_nascita) && converti_data(p->val.data_nascita) < converti_data(val.data_nascita))
            {
                link tmp = newNode(val, x);
                p->next = tmp;
                return h;
            }
        }
        p->next = newNode(val, NULL);
    }
    return h;
}

int converti_data(char *data)
{
    int giorno, mese, anno, val;
    sscanf(data, "%d/%d/%d", &giorno, &mese, &anno);
    val = anno * 10000 + mese * 100 + giorno;
    return val;
}

void stampa_lista(link h)
{
    while (h != NULL)
    {
        printf("%s %s %s %s %s %s %d \n", h->val.codice, h->val.nome, h->val.cognome, h->val.data_nascita, h->val.via, h->val.citta, h->val.CAP);
        h = h->next;
    }
}

void stampa_su_file(link h, FILE *fout)
{
    while (h != NULL)
    {
        fprintf(fout, "%s %s %s %s %s %s %d \n", h->val.codice, h->val.nome, h->val.cognome, h->val.data_nascita, h->val.via, h->val.citta, h->val.CAP);
        h = h->next;
    }
}

void free_lista(link h)
{
    link tmp;
    while (h != NULL)
    {
        tmp = h->next;
        free(h->val.citta);
        free(h->val.codice);
        free(h->val.cognome);
        free(h->val.data_nascita);
        free(h->val.nome);
        free(h->val.via);
        free(h);

        h = tmp;
    }
}

Item crea_copia(Item p)
{
    Item persona;
    persona.CAP = p.CAP;
    persona.nome = strdup(p.nome);
    persona.cognome = strdup(p.cognome);
    persona.citta = strdup(p.citta);
    persona.codice = strdup(p.codice);
    persona.data_nascita = strdup(p.data_nascita);
    persona.via = strdup(p.via);
    return persona;
}

void stampa_riga(Item p)
{
    printf("%s %s %s %s %s %s %d \n", p.codice, p.nome, p.cognome, p.data_nascita, p.via, p.citta, p.CAP);
}

Item ricerca_per_codice(link h)
{
    link x = NULL;
    char codice[5];
    char lettera1, lettera2, trovato = 0;
    int numero1, numero2;
    printf("Inserire codice che si desidera cercare:");
    scanf("%s", codice);

    for (x = h; x != NULL; x = x->next)
    {
        sscanf(x->val.codice, "%c%d", &lettera1, &numero1);
        sscanf(codice, "%c%d", &lettera2, &numero2);
        if (lettera1 == lettera2 && numero1 == numero2)
        {
            trovato = 1;
            return x->val;
        }
    }

    if (trovato == 0)
        printf("Non è stato trovato alcun codice corrispondente! \n");
}

Item estrai_e_cancella_elemento(link *h)
{
    link x, p;
    Item persona;
    char lettera1, lettera2;
    int numero1, numero2;
    persona = ricerca_per_codice(*h);

    sscanf(persona.codice, "%c%d", &lettera1, &numero1);

    for (x = *h, p = NULL; x != NULL; p = x, x = x->next)
    {
        sscanf(x->val.codice, "%c%d", &lettera2, &numero2);
        if (lettera1 == lettera2 && numero1 == numero2)
        {
            if (p == NULL)
                *h = x->next;
            else
                p->next = x->next;
            printf("La riga eliminata è: \n");
            persona = crea_copia(x->val);
            free(x);
            return persona;
        }
    }
}
