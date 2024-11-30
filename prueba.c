#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESOS 5
#define TAMANO_MEMORIA 100  

typedef struct {
    int id;
    int tamano;     
    bool en_memoria;  
} Proceso;

Proceso procesos[MAX_PROCESOS];
int memoria_disponible = TAMANO_MEMORIA;

void inicializar_procesos() {
    for (int i = 0; i < MAX_PROCESOS; i++) {
        procesos[i].id = i + 1;
        printf("Introduce el tamanio del proceso %d (en KB): ", i + 1);
        scanf("%d", &procesos[i].tamano);
        procesos[i].en_memoria = false;
    }
}

void mostrar_estado_memoria() {
    printf("\n=== Estado de la memoria ===\n");
    printf("Memoria disponible: %d KB\n", memoria_disponible);
    printf("Procesos en memoria:\n");
    for (int i = 0; i < MAX_PROCESOS; i++) {
        if (procesos[i].en_memoria) {
            printf("  - Proceso %d (%d KB)\n", procesos[i].id, procesos[i].tamano);
        }
    }
    printf("\n");
}

void cargar_proceso(int id) {
    if (procesos[id].tamano <= memoria_disponible) {
        memoria_disponible -= procesos[id].tamano;
        procesos[id].en_memoria = true;
        printf("Proceso %d cargado en memoria.\n", procesos[id].id);
    } else {
        printf("No hay suficiente memoria para el proceso %d. Realizando swapping...\n", procesos[id].id);

        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (procesos[i].en_memoria) {
                printf("Sacando el proceso %d (%d KB) de la memoria.\n", procesos[i].id, procesos[i].tamano);
                memoria_disponible += procesos[i].tamano;
                procesos[i].en_memoria = false;
                break;
            }
        }

        cargar_proceso(id);
    }
}

int main() {
    int opcion, proceso_id;

    inicializar_procesos();

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Mostrar estado de la memoria\n");
        printf("2. Cargar un proceso en memoria\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrar_estado_memoria();
                break;
            case 2:
                printf("Introduce el ID del proceso a cargar (1-%d): ", MAX_PROCESOS);
                scanf("%d", &proceso_id);
                if (proceso_id < 1 || proceso_id > MAX_PROCESOS) {
                    printf("ID de proceso invalido.\n");
                } else {
                    cargar_proceso(proceso_id - 1);
                }
                break;
            case 3:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }

    return 0;
}
