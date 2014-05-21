#include <stdio.h>
#include "aeb.h"
#include <string.h>
#include <math.h>
 
int main() {
  Aeb * raiz, *esq, * dir;
  Aeb * arvore;
  double r;
  char s[127];
 
  /*arvore = criaRaiz('*');
  esq = criaFolha(10.0);
  dir = criaFolha(7.0);
  conectaNodos(arvore, esq, dir);
  raiz = criaRaiz('+');
  dir = criaFolha(8.0);
  conectaNodos(raiz, arvore, dir);
 
  printf("Resultado: %g\n", resolveExpressao(raiz));*/
  
  printf("\nExpressão: ");
  scanf("%s",s);
  arvore = criaArvore(s);
  printf("Expressão após conversão: "); 
  mostraArvore(arvore);
  puts("");
  r=resolveExpressao(arvore);
  printf("\nO resultado é= %g\n",r);
}
