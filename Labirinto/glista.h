#ifndef GLISTA_H
#define GLISTA_H

#define push(p,x) adicionaItem(p,x)
 
// A operação pop é o mesmo que remover do início
#define pop(p) removeItem(p, 0)
 
// aqui escreva suas definições de tipos e prototypes das operações da lista
struct Nodo {
  void * dados;
  struct Nodo * proximo; // este é o ponteiro para o próximo nodo da lista.
                         // ele deve ter valor NULL se não houver um próximo nodo.
};
 
struct LISTA {
  struct Nodo * primeiro;
  int comprimento; // aqui se pode armazenar a contagem de nodos da lista
};

typedef struct LISTA Lista;
typedef struct LISTA Fila;
typedef struct LISTA Pilha;


// As operações da lista
Lista * criaLista();
void   limpaLista(Lista * lista);
void   destroiLista(Lista * lista);
int    adicionaItem(Lista * lista, void * dados);
int    adicionaItemNoFim(Lista * lista, void * dados);
int    adicionaItemNaPosicao(Lista * lista, void * dados, unsigned int posicao);
void *  removeItem(Lista * lista, unsigned int posicao);
void *  removeUltimoItem(Lista * lista);
void* obtemItem(Lista * lista, unsigned int posicao);
void * obtemUltimoItem(Lista * lista);
int    comprimentoDaLista (Lista * lista);
void   mostraLista(Lista * lista);

// Funções relacionadas com ordenamento
void insereOrdenado(Lista * lista, void * dados);
void ordena(Lista * lista);

// Funções da fila
Fila * criaFila();
void destroiFila(Fila * fila);
int enfileira(Fila * fila, void * dados);
void * desenfileira(Fila * fila);

// A função compara é usada para o ordenamento. Ela deve ser implementada externamente
// (ex: no código que for usar a lista). Seus resultados devem ser:
// < 0: se x1 < x2
// > 0: se x1 > x2
// == 0: se x1 == x2
extern int compara(void *x1, void * x2);

#endif
