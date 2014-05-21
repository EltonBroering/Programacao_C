#include <stdio.h>
#include <string.h>
#include "arvore.h"
 
#define VALOR1	"palavra1"
#define VALOR2	"palavra2"
#define VALOR3	"palavra3"
 
int compara_palavras(void * p1, void * p2) {
  char * s1 = p1, * s2 = p2;
 
  return strcmp(s1, s2);
}
 
char * conversor_string(void * dados) {
  return (char*)dados;
}
 
int main() {
  Tree * arvore;
  FILE * f;
 
  arvore = criaArvore(VALOR1);
  adicionaItemArvore(arvore, VALOR2, compara_palavras);
  adicionaItemArvore(arvore, VALOR3, compara_palavras);
  adicionaItemArvore(arvore, "oi", compara_palavras);
  /*adicionaItemArvore(arvore, "flávia", compara_palavras);
  adicionaItemArvore(arvore, "te", compara_palavras);
  adicionaItemArvore(arvore, "amo", compara_palavras);
  adicionaItemArvore(arvore, "palavra21", compara_palavras);*/
 
  // mostra a arvore, para se ter uma ideia de sua estrutura
  mostraArvore(arvore, conversor_string);
 
  // Faz rotacao esquerda-esquerda
  arvore = rotacao_RR(arvore);
  printf("\n");
  // mostra a arvore, para ver como ficou apos a rotacao
  mostraArvore(arvore, conversor_string);
 
  return 0;
}
