#include <stdio.h>

int resultado(int base, int potencia);
int division(int dividendo, int divisor);
int suma(int base, int potencia);

int main(){
    int opcion;
    printf("¿Qué deseas hacer? Potencia de un número (0) o división (1): ");
    scanf("%d", &opcion);
    
    if(opcion == 0){
        int base;
        int potencia;
        printf("Ingrese la base: ");
        scanf("%d", &base);
        printf("Ingrese la potencia: ");
        scanf("%d", &potencia);
        printf("Resultado: %d\n", suma(base, potencia));
    } else if(opcion == 1){
        int dividendo;
        int divisor;
        printf("Ingresa el dividendo: ");
        scanf("%d", &dividendo);
        printf("Ingresa el divisor: ");
        scanf("%d", &divisor);
        
        if (divisor == 0) {
            printf("Error: No se puede dividir por cero.\n");
        } else {
            printf("Resultado: %d\n", division(dividendo, divisor));
        }
    }
    return 0;
}

int suma(int base, int potencia){
    if(potencia == 0){
        return 1;
    } else{
        return resultado (base, suma(base, potencia - 1));
    }
}

int resultado(int base, int potencia){
    if(potencia == 0){
        return 0; 
    } else if(potencia < 0){
        return resultado(base, potencia + 1) / base; 
    } else{
        return base + resultado(base, potencia - 1);
    }
}

int division(int dividendo, int divisor) {
    if (divisor == 0) {
        printf("Error: No se puede dividir por cero.\n");
        return -1; 
    }
    if (dividendo < divisor) {
        return 0; 
    } else {
        return 1 + division(dividendo - divisor, divisor);
    }
}


