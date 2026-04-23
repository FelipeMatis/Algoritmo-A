#include <stdio.h>
#include <stdlib.h>

#define LINHAS 12
#define COLUNAS 15

typedef struct {
    int x;
    int y;
    int g;
    int h;
    int f;
    int parentX;
    int parentY;
} Node;

int grid[LINHAS][COLUNAS] = {0};

int heuristica(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int dentroMapa(int x, int y){
    return (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS);
}

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

void reconstruirCaminho(Node nodes[LINHAS][COLUNAS], int caminho[LINHAS][COLUNAS], int x, int y){

    while(nodes[x][y].parentX != -1){

        caminho[x][y] = 1;

        int px = nodes[x][y].parentX;
        int py = nodes[x][y].parentY;

        x = px;
        y = py;
    }
}

void aEstrela(int inicioX, int inicioY, int objetivoX, int objetivoY){

    int fechado[LINHAS][COLUNAS] = {0};
    int caminho[LINHAS][COLUNAS] = {0};

    Node nodes[LINHAS][COLUNAS];

    for(int i=0;i<LINHAS;i++){
        for(int j=0;j<COLUNAS;j++){

            nodes[i][j].x = i;
            nodes[i][j].y = j;
            nodes[i][j].g = 999999;
            nodes[i][j].h = 0;
            nodes[i][j].f = 999999;
            nodes[i][j].parentX = -1;
            nodes[i][j].parentY = -1;
        }
    }

    nodes[inicioX][inicioY].g = 0;
    nodes[inicioX][inicioY].h = heuristica(inicioX,inicioY,objetivoX,objetivoY);
    nodes[inicioX][inicioY].f = nodes[inicioX][inicioY].h;

    int aberto = 1;

    int movimentos[4][2] = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };

    while(aberto){

        int menorF = 999999;
        int atualX = -1;
        int atualY = -1;

        for(int i=0;i<LINHAS;i++){
            for(int j=0;j<COLUNAS;j++){

                if(!fechado[i][j] && nodes[i][j].f < menorF){

                    menorF = nodes[i][j].f;
                    atualX = i;
                    atualY = j;
                }
            }
        }

        if(atualX == -1)
            break;

        if(atualX == objetivoX && atualY == objetivoY){

            reconstruirCaminho(nodes,caminho,objetivoX,objetivoY);

            imprimirMapa(caminho,inicioX,inicioY,objetivoX,objetivoY);

            printf("\nCaminho encontrado!\n");

            return;
        }

        fechado[atualX][atualY] = 1;

        for(int i=0;i<4;i++){

            int nx = atualX + movimentos[i][0];
            int ny = atualY + movimentos[i][1];

            if(!dentroMapa(nx,ny))
                continue;

            if(grid[nx][ny] == 1)
                continue;

            if(fechado[nx][ny])
                continue;

            int novoG = nodes[atualX][atualY].g + 1;

            if(novoG < nodes[nx][ny].g){

                nodes[nx][ny].g = novoG;

                nodes[nx][ny].h = heuristica(nx,ny,objetivoX,objetivoY);

                nodes[nx][ny].f = nodes[nx][ny].g + nodes[nx][ny].h;

                nodes[nx][ny].parentX = atualX;
                nodes[nx][ny].parentY = atualY;
            }
        }
    }

    printf("Nenhum caminho encontrado.\n");
}

int main(){

    int inicioX = 0;
    int inicioY = 0;

    int objetivoX = 10;
    int objetivoY = 14;

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

    printf("Algoritmo A* - Planejamento de Caminho em Armazem\n");

    aEstrela(inicioX,inicioY,objetivoX,objetivoY);

    return 0;
}