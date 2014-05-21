#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "arvore.h"
#include <errno.h>
 
 
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
 
  return strcasecmp(s1, s2);
}

char * mostra_palavras(void *p1){
	char * s1=p1;
	
	return s1;
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
  char pal[16];
  int i,result;

  // Carrega a arvore do arquivo "arvore.txt"
  t1 = relogio();
  f = fopen("arvore.txt", "r+");
  arvore = carregaArvore(f, parser);
  t2 = relogio();
  rewind(f);

  printf("Carregou em %.4g segundos\n", t2-t1);
  arvore = balanceiaArvore(arvore);
  printf("Altura=%d\n", altura(arvore));

for(;;){
		printf("\nEscreva a palavra a ser verificada!\n(Para sair do programa digite:0)\n");
		scanf("%s",pal);
		if(strcmp("0",pal)==0){
			gravaArvore(arvore,mostra_palavras,f);
			fclose(f);
			return;
		}			
		if(obtemItemArvore(arvore,pal,compara_palavras)!=NULL){
			printf("A palavra existe");
		}
		else{
			printf("\nA palavra não existe no dicionário, quer acrescentala?\nSim=1\nNão=0\n");
			scanf("%d",&i);
				if(i){
					adicionaItemArvore(arvore, strdup(pal), compara_palavras);	
				
				}	
		}	
	}
 
  return 0;
}

