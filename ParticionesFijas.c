#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PARTICIONES 10
#define MAX_PROCESOS 10

typedef struct {
    int tamano;     
    bool ocupado;
    int proceso_id;
} Particion;

typedef struct {
    int id;
    int tamano;   
    int particion_asignada;
} Proceso;

Particion particiones[MAX_PARTICIONES];
Proceso procesos[MAX_PROCESOS];
int num_particiones = 0;
int num_procesos = 0;

void mostrar_memoria() {
    printf("Estado de la memoria:\n");
    for (int i = 0; i < num_particiones; i++) {
        printf("Particion %d: Tamano = %d KB, ", i + 1, particiones[i].tamano);
        if (particiones[i].ocupado)
            printf("Ocupado por Proceso %d\n", particiones[i].proceso_id);
        else
            printf("Libre\n");
    }
}

void definir_particiones() {
    int tamano_total, tamano;
    printf("Define el tamano total de la memoria (en KB): ");
    scanf("%d", &tamano_total);

    printf("Cuantas particiones quieres crear (max %d): ", MAX_PARTICIONES);
    scanf("%d", &num_particiones);

    int suma_tamanos = 0;
    for (int i = 0; i < num_particiones; i++) {
        printf("Tamano de la particion %d (en KB): ", i + 1);
        scanf("%d", &tamano);
        if (suma_tamanos + tamano > tamano_total) {
            printf("No hay suficiente memoria restante. Intenta un tamano menor.\n");
            i--;
            continue;
        }
        particiones[i].tamano = tamano;
        particiones[i].ocupado = false;
        particiones[i].proceso_id = -1;
        suma_tamanos += tamano;
    }
}

void asignar_proceso() {
    int tamano;
    printf("Tamano del nuevo proceso (en KB): ");
    scanf("%d", &tamano);

    for (int i = 0; i < num_particiones; i++) {
        if (!particiones[i].ocupado && particiones[i].tamano >= tamano) {
            procesos[num_procesos].id = num_procesos + 1;
            procesos[num_procesos].tamano = tamano;
            procesos[num_procesos].particion_asignada = i;

            particiones[i].ocupado = true;
            particiones[i].proceso_id = procesos[num_procesos].id;

            printf("Proceso %d asignado a la particion %d\n", procesos[num_procesos].id, i + 1);
            num_procesos++;
            return;
        }
    }
    printf("No hay particiones disponibles para este proceso.\n");
}

void liberar_proceso() {
    int proceso_id;
    printf("ID del proceso a liberar: ");
    scanf("%d", &proceso_id);

    for (int i = 0; i < num_particiones; i++) {
        if (particiones[i].ocupado && particiones[i].proceso_id == proceso_id) {
            particiones[i].ocupado = false;
            particiones[i].proceso_id = -1;
            printf("Proceso %d liberado de la particion %d\n", proceso_id, i + 1);
            return;
        }
    }
    printf("Proceso no encontrado.\n");
}

int main() {
    int opcion;
    definir_particiones();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Asignar proceso\n");
        printf("2. Liberar proceso\n");
        printf("3. Mostrar memoria\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: asignar_proceso(); break;
            case 2: liberar_proceso(); break;
            case 3: mostrar_memoria(); break;
            case 4: return 0;
            default: printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    return 0;
}

