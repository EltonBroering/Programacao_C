#ifndef LISTA_H
#define LISTA_H
 
// aqui escreva suas definições de tipos e prototypes das operações da lista
struct Nodo {
  char nome[32];
  char cpf[12];
  char cidade[32];
  char fone[12];
  unsigned int valor;
  struct Nodo * proximo; // este é o ponteiro para o próximo nodo da lista.
                         // ele deve ter valor NULL se não houver um próximo nodo.
};
 
struct Lista {
  struct Nodo * primeiro;
  int comprimento; // aqui se pode armazenar a contagem de nodos da lista
};
 
// As operações da lista
 
// Cria uma lista
struct Lista * criaLista();
 
// Destroi uma lista: toda memoria usada pela lista eh liberada
// (inclusive a que contém as palavras).
void   destroiLista(struct Lista * lista);
 
// Adiciona um item ao inicio da lista
int    adicionaItem(struct Lista * lista, char * palavra);
 
// Adiciona um item ao final da lista
int    adicionaItemNoFim(struct Lista * lista, char * palavra);
 
// Adiciona um item em uma certa posicao da lista

 
// Remove um item de uma certa posicao da lista
// A memoria usada pela palavra é também liberada

void mostraLista(struct Lista *lista);
 
// Obtem um item em uma certa posicao da lista
char * obtemItem(struct Lista * lista, int posicao);
 
// Obtem o ultimo item da lista
char * obtemUltimoItem(struct Lista * lista);
 
// Retorna o comprimento da lista
int    comprimentoDaLista (struct Lista * lista);

void mostraLista(struct Lista *lista);


int buscaPalavra (struct Lista * lista, char *palavra);

int troca (struct Lista * lista, struct Nodo * atual, struct Nodo*post);

void ordena (struct Lista * lista);

int insereOrdenado (struct Lista * lista, char * palavra);

#endif


