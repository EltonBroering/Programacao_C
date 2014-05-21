#include <stdio.h>
#include "thash.h"


THash criaTabela(int capacidade) {
  THash tab;
  int i;
 
  // Aloca memória para a variável THash
  tab = (THash) malloc(sizeof(struct HASH));
 
  tab->capacidade = capacidade;
 
  // inicializa a tabela de dispersão: aloca memória para a tabela
  // e inicializa todas suas posições com um ponteiro NULL.
  tab->tabela = (Lista**)malloc(capacidade * sizeof(Lista*));
  for (i=0; i < capacidade; i++) tab->tabela[i] = NULL;

  return tab;
}


int funcao_hash(THash tab, char * chave) {
  int r = 0;
  int n;
 
  // soma os valores dos códigos ASCII dos caracteres da chave
  for (n=0; chave[n] != 0; n++) r += chave[n];
 
  // calcula o resto da divisão da soma pela capacidade da tabela
  // a capacidade da tabela é a quantidade de índices suportados (vagas na tabela) 
  // Esse cálculo resulta em um número entre 0 e tab->capacidade-1
  r = r % tab->capacidade;
 
  return r;
}



void adicionaItem(THash tabela, char * chave, void * dados){
int i;
//se NULL criaLista

	i=funcao_hash(tabela, chave);
	if(tab->tabela[i]==NULL) criaLista();
	tabela -> tabela[i] =dados;	
}

void * obtemItem(THash tabela, char * chave){

	return tabela->tabela[funcao_hash(tabela, chave)];
}


void mostraTabela(THash tab, FMostra func){




}

void * removeItem(THash tabela, char * chave){

tabela->tabela[funcao_hash(tabela, chave)]=NULL;

}

void destroiTabela(THash tab){

	free(tab);	

}


void destroiTabelaTotalmente(THash tab){

	

}

int tamanho(THash tab){





}


struct Par{
	char *chave;
	void*dado;
};

	
	







