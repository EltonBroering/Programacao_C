#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "arvore.h"
 
#define VALOR1	"palavra1"
#define VALOR2	"palavra2"
#define VALOR3	"palavra3"
 
double relogio() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

int compara_palavras(void * p1, void * p2) {
  char * s1 = p1, * s2 = p2;
 
  return strcmp(s1, s2);
}
 
char * conversor_string(void * dados) {
  return (char*)dados;
}
 
// Converte uma string lida do arquivo para um dado a ser guardado
// na arvore. Como neste exemplo o dado é também uma string, esta função
// acaba sendo bem simples: ela apenas cria uma duplicata da string.
void * parser(char * buffer) {
  char * s = strdup(buffer);
  return (void*)s;
}
 
int main() {
  Tree * arvore;
  FILE * f;
  double t1,t2;

  // Carrega a arvore do arquivo "arvore.txt"
  t1 = relogio();
  f = fopen("arvore.txt", "r");
  arvore = carregaArvore(f, parser);
  fclose(f);
  t2 = relogio();

  printf("Carregou em %.4g segundos\n", t2-t1);

  printf("Arvore tem %s: %s\n", VALOR1, (char*)obtemItemArvore(arvore, VALOR1, compara_palavras));
  printf("Arvore tem %s: %s\n", VALOR2, (char*)obtemItemArvore(arvore, VALOR2, compara_palavras));
  printf("Arvore tem %s: %s\n", VALOR3, (char*)obtemItemArvore(arvore, VALOR3, compara_palavras));
  printf("Arvore tem %s: %s\n", "oi", conversor_string(obtemItemArvore(arvore, "oi", compara_palavras)));
 
  // Mostra a arvore, para se ter uma ideia de sua estrutura
  printf("Altura=%d\n", altura(arvore));
  arvore = balanceiaArvore(arvore);
  printf("Altura=%d\n", altura(arvore));
  
 
  return 0;
}
