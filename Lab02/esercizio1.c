#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);
int pari(int x);

int main(){
    int a, b, MCD;

    printf("Inserire il primo valore: ");
    scanf("%d", &a);
    printf("Inserire il secondo valore: ");
    scanf("%d", &b);

    if(a == b){
        printf("I due numeri sono uguali!");
        return 0;
    }

    if(a > b){
        MCD = gcd(a, b);
    }else{
        MCD = gcd(b, a);
    }
    
    printf("Il Massimo Comune Divisore dei due numeri è: %d", MCD);
    return 0;

}

int pari(int x){
    return(x % 2 == 0);
}

int gcd(int a, int b){
    if(a == b){
        return a;
    }
    if(pari(a) && pari(b)){
        return 2*gcd(a/2, b/2);
    }
    if(!pari(a) && !pari(b)){
        if(a > b){
            return gcd((a-b)/2, b);
        }else{
            return gcd((b-a)/2, a
        );
        }
    }
    if(!pari(a) && pari(b)){
        return gcd(a, b/2);
    }
    if(pari(a) && !pari(b)){
        return gcd(a/2, b);
    }
}