/*
* Si scriva una funzione (wrapper) 'char *decode(H h, char *str)' che, ricevuto in input un albero binario h,
* rappresentante la codifica di Huffman associata a un certo set di caratteri,
* e una stringa di caratteri str che contiene una sequenza di 0/1, la decodifichi,
* sulla base della codifica memorizzata nell’albero h, ritornando come risultato una stringa decodificata.
*
* Fornire inoltre la definizione del tipo H (come ADT di prima classe) e del tipo nodo al suo interno (come quasi ADT).

* Non è ammesso l'uso di funzioni di libreria. Attenersi al prototipo dato.
*/

#include <stdio.h>

/* !IMPORTANT: for this exercise provide all the code here, even if by definition of ADT, implementation should be opaque */

/* define node here */
typedef struct node *link;
struct node{
	char carattere;
	link left;
	link right;
};
struct bst{
	link root;
};

/* define H here */
typedef struct bst *H;

/* function prototype is strict, do not change it */
char *decode(H h, char *str);

/* function prototype is strict, do not change it */
char *decode(H h, char *str) {
	/* you code goes here */
	int code_len = strlen(str);
	char *sol = malloc(strlen(str)+1*sizeof(char));
    int index = 0;
	decodifica(h->root, str, code_len, 0, &index, sol, h->root);
	return sol;
}

char *decodifica(link h, char *str, int len, int start, int *index, char *sol, link root){
	if(start >= (len)) return sol;
	if(h->carattere == '\0'){
		if(str[start] == '0') return decodifica(h->left, str, len, start+1, index, sol, root);
		else{
			if(str[start] == '1') return decodifica(h->right, str, len, start+1, index, sol, root);
		}
	}else{
		sol[(*index)++] = h->carattere;
        return decodifica(root, str, len, start+1, index, sol, root);
	}
}

int main(int argc, char **argv) {
	/* you can implement your test case here [NOT NEEDED] */
	return 0;
}