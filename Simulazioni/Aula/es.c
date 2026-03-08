#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//esercizio 1
int subSeq(int a[], int na, int b[], int nb){
    int i, j;
    for(i = 0, j = 0; i < na && j < nb; j++){
        if(a[i] == b[i]){
            i++;
        }
    }
    if(i == na) return 1;
}


//esercizio 2
typedef struct bst *BST;
typedef struct node *link;
struct node{
    char *str;
    link left, right;
};
struct bst{
    link radice;
};

int BSTprintMax2(BST b){
    link percorso[100];
    int max = altezzaBST(b->radice, percorso);
    print_path(percorso, max);
}

int altezzaBST(link root, link path[]){
    int left, right, this = 0;
    if(root->left == NULL && root->right == NULL) return 0;
    if(root->left != NULL && root ->right != NULL) this = 1;
    left = altezzaBST(root->left, path);
    right = altezzaBST(root->right, path);

    if(left > right) return left + this;
    return right + this;
}

void print_path(link path[], int n){
    for(int i = 0; i < n; i++){
        printf("%s", path[i]->str);
    }
}


//esercizio3
int chackConcat(char *s1, char *s2){
    int I, l1 = strlen(s1), l2 = strlen(s2), concat, min;
    if(l1 < l2){
        min = l1; 
    }else{
        min = l2;
    }

    for(int i = 1; i < min; i++){
        concat = 1;
        for(I = 0; I < i; I++){
            if(s1[l1-i+I] != s2[I]){
                concat = 0;
            }
        }
        if(concat) return 1;
    }
    return 0;
}



