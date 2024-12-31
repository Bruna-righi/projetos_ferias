#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int cont = 0;

int* le_cartao(){
    int b, *v;
    v = malloc(sizeof(int)*16);
    printf("Número: ");
    char c = 'n';
    while(true){
        c = getchar();
        b = (int) (c - '0');
        if(b >= 0 && b <= 9){
            v[cont] = b;
            cont++;
        }
        else if(c == '\n') return v;
        else{
            printf("INVÁLIDO\n");
            exit(1);
        }
    }
}

bool testa_se_valido(int* a){
    if(cont < 13){
        printf("INVÁLIDO\n");
        return false;
    }
    int sum_i = 0, sum_f = 0;
    if(cont == 16){
        for(int i = cont - 2; i>=0; i = i-2){
            sum_i += 2*a[i]%10 + 2*a[i]/10;
            sum_f += a[i+1];
            //printf("i = %d\t%d, %d\n", i, sum_f, sum_i);
        }
    }
    else {
        for(int i = cont - 1; i>=0; i = i-2){
            sum_i += 2*a[i]%10 + 2*a[i]/10;
            sum_f += a[i+1];
            //printf("i = %d\t%d, %d\n", i, sum_f, sum_i);
        }
    }
    int total = sum_i + sum_f;
    //printf("total = %d\n", total);
    if(total % 10 == 0){
        if(a[0] == 3 && cont == 15){
            printf("AMEX\n");
        }
        else if(a[0] == 4 && (cont == 13 || cont == 16)){
            printf("VISA\n");
        }
        else if(a[0] == 5 && cont == 16){
            printf("MASTERCARD\n");
        }
        return true;
    }
    else {
        printf("INVÁLIDO\n");
        return false;
    }
}

int main(){
    int* a = le_cartao();
    testa_se_valido(a);
    return 0;
}