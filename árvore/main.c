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
 
int main(int argc, char ** argv) {
  FILE * f;
  char palavra[16];
  Tree * arvore = NULL;
  int n = 0;
 
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
      else adicionaItemArvore(arvore, strdup(palavra), compara_palavras);
    } else {
      // Se não conseguir ler uma palavra,
      // pula todos os caracteres que não aparecem em palavras (espaços e pontuação)
      // A macro PULAR contém todos os caracteres que não estão em PALAVRA.
      fscanf(f, PULAR);
    }
  }
 
  printf("Criou a árvore\n");
 
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
  char pal[30];
  int i;
  for(;;){
	printf("Qual a palavra que deseja verificar\n");
	scanf("%s", pal);
	if(obtemItemArvore(arvore, pal, compara_palavras)==NULL){
		 printf ("A palavra é desconhecida; Deseja adicioná-la? 1-sim, 2-não\n");
		 scanf ("%d", &i);
		 if(i==1) {
		 	adicionaItemArvore(arvore, pal, compara_palavras);
			fprintf(f,"%s\n",pal);
			printf("A palavra foi adicionada\n");
			fclose(f);
			return;
			}
	}
	
	else printf ("A palavra é conhecida\n");
  }	
 
  // fecha o arquivo e termina o programa
  fclose(f);
 
  return 0;
}

