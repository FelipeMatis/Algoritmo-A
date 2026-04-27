#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LINHAS 12
#define COLUNAS 15

int grid[LINHAS][COLUNAS] = {0};
int caminho[LINHAS][COLUNAS] = {0};

typedef struct {
    int g, h, f;
    int paiX, paiY;
    int aberto, fechado;
} No;

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void reconstruir(No nos[LINHAS][COLUNAS], int x, int y) {
    while (!(nos[x][y].paiX == x && nos[x][y].paiY == y)) {
        caminho[x][y] = 1;
        int px = nos[x][y].paiX;
        int py = nos[x][y].paiY;
        x = px; y = py;
    }
}

void aEstrela(int sx, int sy, int gx, int gy) {
    No nos[LINHAS][COLUNAS];
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            nos[i][j].g = nos[i][j].f = INT_MAX;
            nos[i][j].paiX = nos[i][j].paiY = -1;
            nos[i][j].aberto = nos[i][j].fechado = 0;
        }
    }

    nos[sx][sy].g = 0;
    nos[sx][sy].f = nos[sx][sy].h = manhattan(sx, sy, gx, gy);
    nos[sx][sy].paiX = sx; nos[sx][sy].paiY = sy;
    nos[sx][sy].aberto = 1;

    // ORDEM DE EXPLORAÇÃO: Essencial para o desenho da imagem
    int dx[4] = {0, 1, 0, -1}; 
    int dy[4] = {1, 0, -1, 0};

    while (1) {
        int x = -1, y = -1, menorF = INT_MAX;
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                if (nos[i][j].aberto && !nos[i][j].fechado && nos[i][j].f < menorF) {
                    menorF = nos[i][j].f; x = i; y = j;
                }
            }
        }

        if (x == -1 || (x == gx && y == gy)) {
            if (x != -1) reconstruir(nos, gx, gy);
            return;
        }

        nos[x][y].aberto = 0; nos[x][y].fechado = 1;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx>=0 && nx<LINHAS && ny>=0 && ny<COLUNAS && grid[nx][ny]==0 && !nos[nx][ny].fechado) {
                int novoG = nos[x][y].g + 1;
                // O uso do <= permite que ele prefira a última direção explorada (ajuda no zigue-zague)
                if (!nos[nx][ny].aberto || novoG <= nos[nx][ny].g) {
                    nos[nx][ny].g = novoG;
                    nos[nx][ny].f = novoG + manhattan(nx, ny, gx, gy);
                    nos[nx][ny].paiX = x; nos[nx][ny].paiY = y;
                    nos[nx][ny].aberto = 1;
                }
            }
        }
    }
}

void imprimir(int sx, int sy, int gx, int gy) {
    printf("Mapa do armazem:\n\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == sx && j == sy) printf(" S ");
            else if (i == gx && j == gy) printf(" G ");
            else if (grid[i][j] == 1) printf(" # ");
            else if (caminho[i][j] == 1) printf(" * ");
            else printf(" . ");
        }
        printf("\n");
    }
}

int main() {

    // Bloco da esquerda
    grid[1][2] = 1; grid[2][2] = 1; grid[3][2] = 1;
    // Bloco central (dividido para permitir a passagem no meio)
    grid[4][4] = 1; grid[5][4] = 1; grid[6][4] = 1; // Parede esquerda do centro
    grid[3][7] = 1; grid[4][7] = 1; grid[5][7] = 1; // Parede direita do centro
    // Bloco da direita
    grid[7][10] = 1; grid[8][10] = 1; grid[9][10] = 1;

    aEstrela(0, 0, 10, 14);
    imprimir(0, 0, 10, 14);
    return 0;
}
