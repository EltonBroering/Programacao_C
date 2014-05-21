#include <stdio.h>
#include "arvore.h"
 
#define VALOR1	"palavra1"
#define VALOR2	"palavra2"
#define VALOR3	"palavra3"
 
int compara_palavras(void * p1, void * p2) {
  char * s1 = p1, * s2 = p2;
 
  return strcmp(s1, s2);
}
 
int main() {
  Tree * arvore;
 
  arvore = criaArvore(VALOR1);
  adicionaItemArvore(arvore, VALOR2, compara_palavras);
  adicionaItemArvore(arvore, VALOR3, compara_palavras);
 
  printf("Arvore tem %s: %s\n", VALOR1, (char*)obtemItemArvore(arvore, VALOR1, compara_palavras));
  printf("Arvore tem %s: %s\n", VALOR2, (char*)obtemItemArvore(arvore, VALOR2, compara_palavras));
  printf("Arvore tem %s: %s\n", VALOR3, (char*)obtemItemArvore(arvore, VALOR3, compara_palavras));
  printf("Arvore tem %s: %p\n", "xyzabc", obtemItemArvore(arvore, "xyzabc", compara_palavras));
 
  return 0;
}
