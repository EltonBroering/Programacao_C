#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <sys/time.h>
#include "maze.h"

#define DOUBLE_SPACE 0
 
#if DOUBLE_SPACE
#	define SPC "　"
#else
#	define SPC " "
#endif
 
static wchar_t glyph[] = L""SPC"│││─┘┐┤─└┌├─┴┬┼"SPC"┆┆┆┄╯╮ ┄╰╭ ┄";
 
typedef unsigned char byte;
enum { N = 1, S = 2, W = 4, E = 8, V = 16 };
 
static  byte **cell;
static  int w, h, avail;
static int x=1,y=1;
#define each(i, x, y) for (i = x; i <= y; i++)
 
int irand(int n)
{
	int r, rmax = n * (RAND_MAX / n);
	while ((r = rand()) >= rmax);
	return r / (RAND_MAX/n);
}
 
void show()
{
	int i, j, c;
	//each(c,0,31) {
	//  printf("%d: %lc\n", c, glyph[c]);
	//}
	//return;
	each(i, 0, 2 * h) {
		each(j, 0, 2 * w) {
			c = cell[i][j];
			if (c == 127) {
				printf("\033[31m");
				printf("x");
			//printf("%02X ", c);
				printf("\033[m");
			} else  printf("%lc", glyph[c]);

/*			if (c > V) printf("\033[31m");
			printf("%lc", glyph[c]);
			//printf("%02X ", c);
			if (c > V) printf("\033[m");
*/
		}
		putchar('\n');
	}
}
 
inline int max(int a, int b) { return a >= b ? a : b; }
inline int min(int a, int b) { return b >= a ? a : b; }
 
static int dirs[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
void walk(int x, int y)
{
	int i, t, x1, y1, d[4] = { 0, 1, 2, 3 };
 
	cell[y][x] |= V;
	avail--;
 
	for (x1 = 3; x1; x1--)
		if (x1 != (y1 = irand(x1 + 1)))
			i = d[x1], d[x1] = d[y1], d[y1] = i;
 
	for (i = 0; avail && i < 4; i++) {
		x1 = x + dirs[ d[i] ][0], y1 = y + dirs[ d[i] ][1];
 
		if (cell[y1][x1] & V) continue;
 
		/* break walls */
		if (x1 == x) {
			t = (y + y1) / 2;
			cell[t][x+1] &= ~W, cell[t][x] &= ~(E|W), cell[t][x-1] &= ~E;
		} else if (y1 == y) {
			t = (x + x1)/2;
			cell[y-1][t] &= ~S, cell[y][t] &= ~(N|S), cell[y+1][t] &= ~N;
		}
		walk(x1, y1);
	}
}
 
// x, y: posição inicial
//tox, toy: posição alvo (saída)
int solve(int x, int y, int tox, int toy)
{
	int i, t, x1, y1;
 
	cell[y][x] |= V;
	if (x == tox && y == toy) return 1; // chegou ao destino !
 
	// para cada uma das possíveis direções ...
        // tenta encontrar uma direção em que possa prosseguir
	each(i, 0, 3) {
		x1 = x + dirs[i][0], y1 = y + dirs[i][1];
		if (cell[y1][x1]) continue; // ignora se posição já foi visitada ou for parede
 
		/* mark path */
		if (x1 == x) {// se avançando na vertical ...
			t = (y + y1)/2; // localiza o meio do caminho até o alvo
			// ignora se célula já visitada ou não conseguir prosseguir por ali
			if (cell[t][x] || !solve(x1, y1, tox, toy)) continue;
 
			cell[t-1][x] |= S, cell[t][x] |= V|N|S, cell[t+1][x] |= N;
		} else if (y1 == y) { // se avançando na horizontal ...
			t = (x + x1)/2;// localiza o meio do caminho até o alvo
			// ignora se célula já visitada ou não conseguir prosseguir por ali
			if (cell[y][t] || !solve(x1, y1, tox, toy)) continue;
 
			cell[y][t-1] |= E, cell[y][t] |= V|E|W, cell[y][t+1] |= W;
		}
		return 1;
	}
 
	// se não foi possível prosseguir, marca a posição como visitada e retrocede
	/* backtrack */
	cell[y][x] &= ~V;
	return 0;
}
 
void initrand() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);
}

void make_maze()
{
	int i, j;
	int h2 = 2 * h + 2, w2 = 2 * w + 2;
	byte **p;
 
	initrand();

	p = calloc(sizeof(byte*) * (h2 + 2) + w2 * h2 + 1, 1);
 
	p[1] = (byte*)(p + h2 + 2) + 1;
	each(i, 2, h2) p[i] = p[i-1] + w2;
	p[0] = p[h2];
	cell = &p[1];
 
	each(i, -1, 2 * h + 1) cell[i][-1] = cell[i][w2 - 1] = V;
	each(j, 0, 2 * w) cell[-1][j] = cell[h2 - 1][j] = V;
	each(i, 0, h) each(j, 0, 2 * w) cell[2*i][j] |= E|W;
	each(i, 0, 2 * h) each(j, 0, w) cell[i][2*j] |= N|S;
	each(j, 0, 2 * w) cell[0][j] &= ~N, cell[2*h][j] &= ~S;
	each(i, 0, 2 * h) cell[i][0] &= ~W, cell[i][2*w] &= ~E;
 
	avail = w * h;
	walk(irand(2) * 2 + 1, irand(h) * 2 + 1);
 
	/* reset visited marker (it's also used by path finder) */
	each(i, 0, 2 * h) each(j, 0, 2 * w) cell[i][j] &= ~V;
	//solve(1, 1, 2 * w - 1, 2 * h - 1);
 
	//show();
}
 
void cria_labirinto(int largura, int altura) {
  w = largura;
  h = altura;
  setlocale(LC_ALL, "");
  make_maze();
  show();
}

int chegou() {
  Posicao pos = obtem_alvo();

  if ((x == pos.x) && (y == pos.y)) return 1;
  return -1;
}

// retorna:
// 0: se nao pode avancar
// -1: se pode avancar, mas nao chegou ao destino
// 1: se chegou ao destino 
int avanca(int direcao, int volta) {
  int status = 0;
  int casa = 127;
  
  //if (volta) casa = 0;

  //printf("dir=%d, x=%d, y=%d\n", direcao, x, y);
  switch (direcao) {
    case ACIMA: // acima
      if ((y > 1) && ((cell[y-1][x] == 0) || (cell[y-1][x] == 127))) {
	if (volta) cell[y][x] = 0;
        y-=1;
	cell[y][x] = casa;
        status = chegou();
      }
      break;
    case ABAIXO: // abaixo
      if ((y < 2*h) && ((cell[y+1][x] == 0) || (cell[y+1][x] == 127))) {
	if (volta) cell[y][x] = 0;
        y+=1;
	cell[y][x] = casa;
        status = chegou();
      }
      break;
    case ESQUERDA: // esquerda
      if ((x > 1) && ((cell[y][x-1] == 0) || (cell[y][x-1] == 127))) {
	if (volta) cell[y][x] = 0;
        x-=1;
	cell[y][x] = casa;
        status = chegou();
      }
      break;
    case DIREITA: // direita
      if ((x < 2*w) && ((cell[y][x+1] == 0) || (cell[y][x+1] == 127))) {
	if (volta) cell[y][x] = 0;
        x+=1;
	cell[y][x] = casa;
        status = chegou();
      }
      break;
  }
  show();
  return status;
}

Posicao obtem_posicao() {
  Posicao pos = {x,y};

  return pos;
}

Posicao obtem_alvo() {
  Posicao pos = {2*w-1,2*h-1};

  return pos;
}

