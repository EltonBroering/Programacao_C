/* 
 * File:   main.c
 * Author: aluno
 *
 * Created on 8 de Abril de 2013, 10:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
#define PALAVRA "%16[a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
#define PULAR "%*[^a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
/*
 * 
 */



int main(int argc, char ** argv) {
  FILE * f;
	char palavra[16];
	int i; 
	struct Lista *lista;
    
		lista=criaLista();

	

  // O nome do arquivo deve ser informado na linha de comando
  if (argc < 2) {
    printf("Uso: %s arquivo_de_palavras\n", argv[0]);
    return 0;
  }
 
  // Se não conseguir abrir o arquivo, termina o programa
  if ((f = fopen(argv[1], "r")) == NULL) {
    perror("Ao abrir o arquivo");
    return errno;
  }
 
  // Enquanto não chegar ao fim do arquivo ...
while (!feof(f)) {
// Lê uma palavra composta pelos caracteres contidos na macro PALAVRA
	if (fscanf(f, PALAVRA, palavra) > 0) {
		if(buscaPalavra(lista,palavra)==1){ 
			printf("Falha!Item existente!\n");
		}
		else{
			if(executa(palavra,"arquivo.gpg","pronto.pdf")){
				printf ("A chave é:%s\n",palavra);
				return;
			}
			else{
				adicionaItem(lista,palavra);
				printf("Falhou! Item adicionado: %s\n",palavra);
			}
		} 
	}
	else {
      // Se não conseguir ler uma palavra,
      // pula todos os caracteres que não aparecem em palavras (espaços e pontuação)
      // A macro PULAR contém todos os caracteres que não estão em PALAVRA.
		fscanf(f, PULAR);
	}
			
			
}
  // fecha o arquivo e termina o programa
  fclose(f);
}
