#include <stdio.h>

int main(){
    int a = 4, b = 3;
    int *auxa, **auxaa, ***auxaaa;
    auxa=&a;
    auxaa=&auxa;
    auxaaa = &auxaa;
    printf("Valor de auxaa %p %d \n", auxaaa, ***auxaaa);
    printf("Valor de memoria %p \n", &a);
    printf("Valor de memoria %p", &b);
    return 0;
}