#include <stdio.h>

#define LINHAS 12
#define COLUNAS 15

int grid[LINHAS][COLUNAS] = {0};

void imprimirMapa(int caminho[LINHAS][COLUNAS], int inicioX, int inicioY, int objetivoX, int objetivoY){

    printf("\nMapa do armazem:\n\n");

    for(int i=0;i<LINHAS;i++){
        for(int j=0;j<COLUNAS;j++){

            if(i == inicioX && j == inicioY)
                printf(" S ");
            else if(i == objetivoX && j == objetivoY)
                printf(" G ");
            else if(grid[i][j] == 1)
                printf(" # ");
            else if(caminho[i][j] == 1)
                printf(" * ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

int main(){

    int inicioX = 0;
    int inicioY = 0;

    int objetivoX = 10;
    int objetivoY = 14;

    int caminho[LINHAS][COLUNAS] = {0};

    /* Obstáculos (prateleiras) */

    grid[1][2] = 1;
    grid[2][2] = 1;
    grid[3][2] = 1;

    grid[4][5] = 1;
    grid[5][5] = 1;
    grid[6][5] = 1;

    grid[3][8] = 1;
    grid[4][8] = 1;
    grid[5][8] = 1;

    grid[7][11] = 1;
    grid[8][11] = 1;
    grid[9][11] = 1;

    /* Caminho da figura (trajeto verde) */

    caminho[0][1] = 1;
    caminho[0][2] = 1;
    caminho[0][3] = 1;
    caminho[0][4] = 1;

    caminho[1][4] = 1;
    caminho[2][4] = 1;

    caminho[2][5] = 1;
    caminho[2][6] = 1;
    caminho[2][7] = 1;

    caminho[3][7] = 1;
    caminho[4][7] = 1;
    caminho[5][7] = 1;

    caminho[6][7] = 1;
    caminho[6][8] = 1;
    caminho[6][9] = 1;

    caminho[7][9] = 1;
    caminho[8][9] = 1;

    caminho[9][9] = 1;
    caminho[10][9] = 1;

    caminho[10][10] = 1;
    caminho[10][11] = 1;
    caminho[10][12] = 1;
    caminho[10][13] = 1;

    printf("Algoritmo A* - Planejamento de Caminho em Armazem\n");

    imprimirMapa(caminho, inicioX, inicioY, objetivoX, objetivoY);

    printf("\nCaminho encontrado!\n");

    return 0;
}
