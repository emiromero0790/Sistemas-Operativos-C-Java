#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _nodo {
    int valor;
    struct _nodo *siguiente;
} nodo;

nodo* genera_proceso() {
    static int contador = 1;
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->valor = contador++;
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertar_final(nodo** cabeza) {
    nodo* nuevoNodo = genera_proceso();

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        nodo* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void imprimir_lista(nodo* cabeza) {
    nodo* temp = cabeza;
    while (temp != NULL) {
        printf("Proceso %d -> ", temp->valor);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}

void atender_proceso(nodo** cabeza) {
    if (*cabeza == NULL) {
        printf("No hay procesos para atender.\n");
        return;
    }

    nodo* temp = *cabeza;
    printf("Atendiendo proceso %d\n", temp->valor);
    *cabeza = temp->siguiente;
    free(temp);
}

int main() {
    srand(time(NULL));
    nodo* cabeza = NULL;
    int op = 0;

    do {
        printf("1. Genera proceso\n");
        printf("2. Atiende proceso\n");
        printf("3. Mostrar Lista de Procesos\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                insertar_final(&cabeza);
                break;
            case 2:
                atender_proceso(&cabeza);
                break;
            case 3:
                imprimir_lista(cabeza);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (op != 4);

    return 0;
}
