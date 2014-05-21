#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "arvore.h"
#include <sys/time.h>
 
#define PALAVRA "%16[a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
#define PULAR "%*[^a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
 
int compara_palavras(void * p1, void * p2) {
  char * s1 = p1, * s2 = p2;
 
  return strcasecmp(s1, s2);
}

double relogio() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

char * mostra_palavras(void *p1){
	char * s1=p1;
	
	return s1;
}
 

Tree * leitura (FILE *f) {
  
  char palavra[16];
  int n = 0, fc=0, result;
  double t1, t2;
  Tree * arvore = NULL;

  t1 = relogio();  

  
 
  // Enquanto não chegar ao fim do arquivo ...
  while (!feof(f)) {
    // Lê uma palavra composta pelos caracteres contidos na macro PALAVRA
    if (fscanf(f, PALAVRA, palavra) > 0) {
      if (! arvore) arvore = criaArvore(strdup(palavra));
      else{ 
        adicionaItemArvore(arvore, strdup(palavra), compara_palavras);
	fc++;
	if(fc>400){
	  arvore=balanceiaArvore(arvore);
	  fc=0;	
	}	   
      } 
    } else {
      // Se não conseguir ler uma palavra,
      // pula todos os caracteres que não aparecem em palavras (espaços e pontuação)
      // A macro PULAR contém todos os caracteres que não estão em PALAVRA.
      fscanf(f, PULAR);
    }
  }
 
  printf("Criou a árvore com altura %d\n", altura(arvore));
 
  // rebobina o arquivo
  rewind(f);
 
  // contador de palavras nao encontradas na arvore
  n = 0;
  while (!feof(f)) {
    // Lê uma palavra composta pelos caracteres contidos na macro PALAVRA
    if (fscanf(f, PALAVRA, palavra) > 0) {
      if (!obtemItemArvore(arvore, palavra, compara_palavras)) n++;
    } else {
      // Se não conseguir ler uma palavra,
      // pula todos os caracteres que não aparecem em palavras (espaços e pontuação)
      // A macro PULAR contém todos os caracteres que não estão em PALAVRA.
      fscanf(f, PULAR);
    }
  }
   t2 = relogio();
  printf("Consultou todas as palavras (%d omissas)\n", n);
  printf("Carregou em %.4g segundos\n", t2-t1);

  return arvore;
} 



int menu (Tree *arvore, FILE *f){

  FILE *f2;  
  char pal[16];
  int  i;
    
  for(;;){
		printf("\nEscreva a palavra a ser verificada!\n(Para sair do programa digite:0)\n");
		scanf("%s",pal);
		if(strcmp("0",pal)==0){
			fclose(f);
			if ((f2 = fopen("arvore.txt", "w")) == NULL){
    				perror("Ao abrir o arquivo");
    				return errno;
 			 }
  			gravaArvore(arvore,mostra_palavras,f2);
  			fclose(f2);
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
					fprintf(f,"%s\n",pal);
				}	
		}	
	}

   return 0;
}

int main(int argc, char **argv){

  FILE *f;
  Tree * arvore;
 // O nome do arquivo deve ser informado na linha de comando
  if (argc < 2) {
    printf("Uso: %s arquivo_de_palavras\n", argv[0]);
    return 0;
  }
 
  // Se não conseguir abrir o arquivo, termina o programa
  if ((f = fopen(argv[1], "r+")) == NULL) {
    perror("Ao abrir o arquivo");
    return errno;
  }

  arvore = leitura (f); 
  menu(arvore,f);


}

