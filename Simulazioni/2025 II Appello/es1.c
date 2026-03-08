/*

È dato un ADT editori_adt,  in grado di rappresentare un elenco di editori (un vettore allocato dinamicamente).
Ogni editore, oltre al nome (una stringa allocata dinamicamente), contiene un vettore di puntatori a libri (tipo struct libro):
i libri sono da considerarsi come esterni alla struttura dati: l’ADT è quindi di tipo “aggregato”, 
per quanto concerne i libri, che non vanno né allocati né deallocati. Sono date le definizioni dei tipi.
Si scrivano due funzioni: una che duplica e una che libera l’ADT.

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char *nome;
    struct libro **libri;
    int n_libri;
} editore_t;

struct editori{
    editore_t *editori;
    int n_editori;
};

typedef struct editori *editori_adt;

editori_adt EditoriDup(editori_adt e);
void EditoriFree(editori_adt e);

// scrivere qui il codice...

editori_adt EditoriDup(editori_adt e){

    editori_adt new_editors = malloc(sizeof(struct editori));
    new_editors->editori = (editore_t *)malloc((e->n_editori) * sizeof(editore_t));
    new_editors->n_editori = e->n_editori;
    for (int i = 0; i < new_editors->n_editori; i++){
        new_editors->editori[i].nome = malloc((strlen(e->editori[i].nome)+1)*sizeof(char));
        strcpy(new_editors->editori[i].nome, e->editori[i].nome);
        new_editors->editori[i].libri = malloc(e->editori[i].n_libri*sizeof(struct libro*));
        for (int j = 0; j < e->editori[i].n_libri; j++){
            new_editors->editori[i].libri[j] = e->editori[i].libri[j];
        }
        new_editors->editori[i].n_libri = e->editori[i].n_libri;
    }

    return new_editors;
}

void EditoriFree(editori_adt e){
    for (int i = 0; i < e->n_editori; i++){
        free(e->editori[i].nome);
        free(e->editori[i].libri);
    }
    free(e->editori);
    free(e);
}