#ifndef MAZE_H
#define MAZE_H

#define ACIMA 1
#define ABAIXO 2
#define ESQUERDA 4
#define DIREITA 8

struct POSICAO {
  int x,y;
};

typedef struct POSICAO Posicao;

// retorna:
// 0: se nao pode avancar
// -1: se pode avancar, mas nao chegou ao destino
// 1: se chegou ao destino 
int avanca(int direcao, int apagar);

Posicao obtem_posicao();
Posicao obtem_alvo();
void cria_labirinto(int largura, int altura);

#endif
