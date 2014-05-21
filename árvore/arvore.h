#ifndef ARVORE_H
#define ARVORE_H
 
struct TREENODE {
  void * dados; // os dados armazenados
  struct TREENODE * esq, * dir; // os ramos esquerdo e direito
  struct TREENODE * pai; // uma referência ao nodo pai (facilita algumas coisas)
};
 
typedef struct TREENODE Tree;
 
// um tipo de função para comparação de dados
typedef int (*FCompara)(void *, void*);
 
// Cria uma árvore com um dado (não existe árvore vazia ...)
Tree* criaArvore(void * dados);
 
// Adiciona um valor a uma árvore. Deve adicioná-lo de forma ordenada (por isso precisa
// do "comparador").
Tree* adicionaItemArvore(Tree * arvore, void * dados, FCompara comparador);
 
// Busca um valor dentro da árvore. Se não encontrar, retorna NULL.
void * obtemItemArvore(Tree* arvore, void * dados, FCompara comparador);

void mostraArvore(Tree * arvore);
 
#endif
