#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ARCHIVOS 5
#define TAMANO_BLOQUE 512  

typedef struct {
    char nombre[50];
    int bloques_inicio;  
    int tamano;        
} Archivo;

Archivo disco_virtual[MAX_ARCHIVOS];
int num_archivos = 0;

void leer_disco(int bloque_inicio, int tamano) {
    printf("Leyendo %d bytes desde el bloque %d del disco...\n", tamano, bloque_inicio);
    printf("Simulacion: Los datos se han cargado en memoria.\n");
}

void registrar_archivo(const char *nombre, int bloques_inicio, int tamano) {
    if (num_archivos >= MAX_ARCHIVOS) {
        printf("El disco virtual esta lleno. No se pueden registrar mas archivos.\n");
        return;
    }
    strncpy(disco_virtual[num_archivos].nombre, nombre, sizeof(disco_virtual[num_archivos].nombre) - 1);
    disco_virtual[num_archivos].bloques_inicio = bloques_inicio;
    disco_virtual[num_archivos].tamano = tamano;
    num_archivos++;
    printf("Archivo '%s' registrado. Inicio en bloque %d, Tamano %d bytes.\n", nombre, bloques_inicio, tamano);
}


void leer_archivo(const char *nombre) {
    for (int i = 0; i < num_archivos; i++) {
        if (strcmp(disco_virtual[i].nombre, nombre) == 0) {
            printf("Archivo encontrado: '%s'. Localizando en disco...\n", nombre);
            leer_disco(disco_virtual[i].bloques_inicio, disco_virtual[i].tamano);
            return;
        }
    }
    printf("Archivo '%s' no encontrado en el disco.\n", nombre);
}

int main() {
    registrar_archivo("archivo1.txt", 10, 2048);
    registrar_archivo("archivo2.dat", 20, 1024);
    registrar_archivo("imagen.png", 30, 5120);

    printf("\nIntentando leer 'archivo1.txt':\n");
    leer_archivo("archivo1.txt");

    printf("\nIntentando leer 'imagen.png':\n");
    leer_archivo("imagen.png");

    printf("\nIntentando leer 'archivo_no_existente.txt':\n");
    leer_archivo("archivo_no_existente.txt");

    return 0;
}
