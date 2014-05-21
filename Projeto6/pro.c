#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "arvore.h"
 
#define PALAVRA "%16[a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
#define PULAR "%*[^a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
 
int compara_palavras(void * p1, void * p2) {
  char * s1 = p1, * s2 = p2;
 
  return strcasecmp(s1, s2);
}

char * mostra_palavras(void *p1){
	char * s1=p1;
	
	return s1;
}
 
int main(int argc, char ** argv) {
  FILE * f,*f2;
  char palavra[16];
  Tree * arvore = NULL;
  int n = 0,fc=0;
 
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
 
  // Enquanto não chegar ao fim do arquivo ...
  while (!feof(f)) {
    // Lê uma palavra composta pelos caracteres contidos na macro PALAVRA
    if (fscanf(f, PALAVRA, palavra) > 0) {
      if (! arvore) arvore = criaArvore(strdup(palavra));
      else{ 
        adicionaItemArvore(arvore, strdup(palavra), compara_palavras);
	fc++;
	if(fc>1000){
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
 
  printf("Consultou todas as palavras (%d omissas)\n", n);
 
char pal[16];
int i,result;

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

  // fecha o arquivo e termina o programa
  fclose(f);
 
 
  return 0;
}
