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
 
  arvore = criaArvore(VALOR2);
  adicionaItemArvore(arvore, VALOR1, compara_palavras);
  adicionaItemArvore(arvore, VALOR3, compara_palavras);
  adicionaItemArvore(arvore, "oi", compara_palavras);
  adicionaItemArvore(arvore, "elton", compara_palavras);
  adicionaItemArvore(arvore, "alo", compara_palavras);
  // mostra a arvore, para se ter uma ideia de sua estrutura
  mostraArvore(arvore, conversor_string);
 
  // grava a arvoreno arquivo "arvore.txt"
  f = fopen("arvore.txt", "w");
  gravaArvore(arvore, conversor_string,f);
  fclose(f);
 
  return 0;
}
