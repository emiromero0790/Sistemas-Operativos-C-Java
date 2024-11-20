#include <stdio.h>

#define FILAS 6
#define COLUMNAS 8

void marcarIsla(int matriz[FILAS][COLUMNAS], int x, int y) {
    if (x < 0 || x >= FILAS || y < 0 || y >= COLUMNAS || matriz[x][y] == 0) {
        return;
    }

    matriz[x][y] = 0;

    marcarIsla(matriz, x - 1, y); 
    marcarIsla(matriz, x + 1, y); 
    marcarIsla(matriz, x, y - 1); 
    marcarIsla(matriz, x, y + 1); 
}

int contarIslas(int matriz[FILAS][COLUMNAS], int x, int y, int islas) {
    if (x >= FILAS) {
        return islas;
    }

    if (y >= COLUMNAS) {
        return contarIslas(matriz, x + 1, 0, islas);
    }

    if (matriz[x][y] == 1) {
        marcarIsla(matriz, x, y); 
        return contarIslas(matriz, x, y + 1, islas + 1); 
    }

    return contarIslas(matriz, x, y + 1, islas);
}

int main() {
    int matriz[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int numeroDeIslas = contarIslas(matriz, 0, 0, 0);

    printf("Numero de islas: %d\n", numeroDeIslas);

    return 0;
}
