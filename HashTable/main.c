#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glista.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "thash.h"

struct Registro {
  char nome[32];
  char cpf[12];
  int compras;
  char cidade[32];
  char telefone[10];
};


void NovoCadastro(THash tab, FILE *f){
  struct Registro*aux;
  aux= (struct Registro*)malloc(sizeof(struct Registro));

	printf("\nNome:\n");
	scanf(" %[^\n]s",aux->nome);
	

	printf("\nCPF:\n");
	scanf("%s",aux->cpf);

	printf("\nValor das compras:\n");
	scanf("%d",&aux->compras);

	printf("\nCidade:\n");
	scanf(" %[^\n]s",aux->cidade);

	printf("\nTelefone:\n");
	scanf("%s",aux->telefone);

	adicionaItemTabela(tab,aux->cpf,aux);
	fprintf(f, " %s, %s, R$ %d, %s, %s", aux->nome, aux->cpf, aux->compras, aux->cidade, aux->telefone); 
}

void ProcuraCadastro(THash tab){
  char chave[15];
  struct Registro*aux;

 	printf("\nCPF:\n");
	scanf("%s", chave);
	aux=obtemItemTabela(tab, chave);
	if(aux==NULL) {
		printf("\nCadastro não encontrado\n");
		return;
	}
	printf("\nNome: %s\nCPF: %s\nValor: %d\nCidade: %s\nTelefone: %s\n",aux->nome, aux->cpf, aux->compras, aux->cidade, aux->telefone);
	
}
  

void RemoveCadastro(THash tab){
  char chave[15];
  struct Registro*aux;

 	printf("\nCPF:\n");
	scanf("%s", chave);
	aux=obtemItemTabela(tab, chave);
	if(aux==NULL){
		 printf("\nCadastro não encontrado\n");
		 return;
	}
	removeItemTabela(tab,chave);
	printf("Você apagou este usuário:\nNome: %s\nCPF: %s\nValor: %d\nCidade: %s\nTelefone: %s\n",aux->nome, aux->cpf, aux->compras, aux->cidade, aux->telefone);
}



char * func(void * dado) {
   struct Registro * aux = dado;
   static char palavra[256];

   snprintf(palavra, 256, "%s, %s,(( %u)), %s, %s \n",aux->nome, aux->cpf, aux->compras,aux->cidade,aux->telefone);

   return palavra;
}


int main(int argc, char ** argv) {
  struct Registro * dados;
  THash tab;
  int capacidade=10;
  FILE *f;

    // Se não conseguir abrir o arquivo, termina o programa
  if ((f = fopen(argv[1], "r+")) == NULL) {
    perror("Ao abrir o arquivo");
    return errno;
  }
  	tab = criaTabela(capacidade);	
 

  while (!feof(f)) {
    // aloca memória para guardar um registro
    dados = (struct Registro*)malloc(sizeof(struct Registro));
 
    // Lê uma linha do arquivo, extrai os valores e guarda-os nos campos do registro
    if (fscanf(f, "%[^,],%*[ \t]%[0-9],%*[ \t]R$%*[ \t]%u,%*[ \t]%[^,],%*[ \t]%[0-9-]\n", 
            dados->nome, dados->cpf, &dados->compras, dados->cidade, dados->telefone) < 5) {
      printf("Erro ao ler um registro ... pulando pra próxima linha");
      fscanf(f, "%*[^\n]%*[\n]"); // joga tudo fora até o fim da linha, incluindo a quebra de linha
    } else {
		

	adicionaItemTabela(tab,dados->cpf,dados);
	
	
    }
  }
   for(;;){
	int i;
	
	printf("\nO que você deseja fazer?");
	printf("\nPara acrescentar novos cadastros,digite: 0");
	printf("\nPara remover cadastros antigos, digite: 1");
	printf("\nPara consultar dados no cadastro, digite: 2");
	printf("\nPara ver todos os registros digite: 3");
	printf("\nPara sair do programa, digite: 4\n");
	printf("\nOpção: ");
	scanf("%d",&i);

	switch(i){
		case 0:
		NovoCadastro(tab, f);
		break;
		
		case 1:
		RemoveCadastro(tab);
		break;

		case 2:
		ProcuraCadastro(tab);
		break;

		case 3:
		mostraTabela(tab,func);
		break;

		case 4:
		fclose(f);
		return;
		break;


	}
   }
}
