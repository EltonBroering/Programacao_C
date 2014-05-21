#ifndef ARVORE_H
#define ARVORE_H
 
#include <stdio.h>

struct TREENODE {
  void * dados; // os dados armazenados
  struct TREENODE * esq, * dir; // os ramos esquerdo e direito
  struct TREENODE * pai; // uma referência ao nodo pai (facilita algumas coisas)
};
 
typedef struct TREENODE Tree;
 
// um tipo de função para comparação de dados
typedef int (*FCompara)(void *, void*);

typedef char* (*FMostra)(void *);

typedef void * (*FParser)(char *);
 
// Cria uma árvore com um dado (não existe árvore vazia ...)
Tree* criaArvore(void * dados);
 
// Adiciona um valor a uma árvore. Deve adicioná-lo de forma ordenada (por isso precisa
// do "comparador").
Tree* adicionaItemArvore(Tree * arvore, void * dados, FCompara comparador);

Tree * carregaArvore(FILE * arquivo, FParser leitor);
 
// Busca um valor dentro da árvore. Se não encontrar, retorna NULL.
void * obtemItemArvore(Tree* arvore, void * dados, FCompara comparador);

void mostraArvore(Tree * arvore,FMostra conversor);

void gravaArvore(Tree * arvore,FMostra conversor,FILE *f);

int altura(Tree * arvore);

int menu (Tree *arvore, FILE *f);

Tree * rotacao_LL(Tree * arvore); // esquerda-esquerda
Tree * rotacao_LR(Tree * arvore); // esquerda-direita
Tree * rotacao_RL(Tree * arvore); // direita-esquerda
Tree * rotacao_RR(Tree * arvore); // direita-direita

Tree * balanceiaArvore(Tree * arvore);

Tree * leitura (FILE *f);




#endif
