#include <stdio.h>
#include "thash.h"
#include <stdlib.h>



struct Par{
	char *chave;
	void *dados;
};


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


void adicionaItemTabela(THash tab, char * chave, void * dados){
int i;
Par *par;
	
	removeItemTabela(tab,chave);
	par=(Par*)malloc(sizeof(Par));
	par->chave=chave;
	par->dados=dados;

	i=funcao_hash(tab, chave);
	if(tab->tabela[i]==NULL) criaLista();	
	adicionaItem(tab->tabela[i], (void*)par);

}
	

void * obtemItemTabela(THash tab, char * chave){
Par *par;
int i,n;


	i=funcao_hash(tab, chave);
	for(n=0;n< comprimentoDaLista(tab->tabela[i]); n++){
		par = (Par*) obtemItem(tab->tabela[i],n);
	  		if(strcmp(chave, par->chave)==0){
				return par->dados;	
			}
	}
	return NULL;
}



void mostraTabela(THash tab, FMostra func){
  int i;

  for (i=0; i < tab->capacidade; i++) {
    printf("tab[%d]=%s\n", i, func(tab->tabela[i]));
  }
}

void * removeItemTabela(THash tab, char * chave){
Par *par;
int i,n;
void *dados;

	i=funcao_hash(tab, chave);
	for(n=0;n< comprimentoDaLista(tab->tabela[i]); n++){
		par = (Par*) obtemItem(tab->tabela[i],n);
	  		if(strcmp(chave, par->chave)==0){
				removeItem(tab->tabela[i],n);
				dados = par->dados;
				free(par);
				return dados;	
			}
	}
	return NULL;
}

void destroiTabela(THash tab){

		free(tab);
			
}



void destroiTabelaTotalmente(THash tab){
int i, n;

	for(i=0; i<tab->capacidade;i++) destroiLista(tab->tabela[i]);
	free(tab);
}


int tamanho(THash tab){





}


	
	







