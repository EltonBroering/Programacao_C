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
  for (i=0; i < capacidade; i++) tab->tabela[i] = criaLista();

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
	adicionaItem(tab->tabela[i],par);
	
}
	

void * obtemItemTabela(THash tab, char * chave){
	Par *par;
	int i,n;
	void *dados;

	i=funcao_hash(tab, chave);
	for(n=0;n<comprimentoDaLista(tab->tabela[i]); n++){
		par = (Par*) obtemItem(tab->tabela[i],n);
	  		if(strcmp(chave, par->chave)==0){
				dados=par->dados;
				return dados;	
			}
	}
	return NULL;
}



void mostraTabela(THash tab, FMostra func){

	int i,n;

	if(tab==NULL) return;
  

	if(tamanho(tab)==0) return;
  
	for(i=0;i < tab->capacidade;i++){
	printf("%d\n", i);
	  	if (func==NULL){
			if(tab->tabela[i]!=NULL)
				printf("Tabela na posicao [%d] dados ->> %p \n",i,tab->tabela[i]);
			}
	  	else {
                   if(tab->tabela[i]!=NULL){
		     for (n=0; n < comprimentoDaLista(tab->tabela[i]); n++) {
		     Par * par = obtemItem(tab->tabela[i], n);
        	     printf("chave %s: %s tabela -> %d posição -> %d\n", par->chave, func(par->dados),i,n);
			}
 		}
  	}
  }
}	

void * removeItemTabela(THash tab, char * chave){

	Par *par;
	int i,n;
	void *dados;

	i=funcao_hash(tab, chave);
	for(n=0;n<comprimentoDaLista(tab->tabela[i]); n++){
		par = (Par*) obtemItem(tab->tabela[i],n);
	  		if(strcmp(chave, par->chave)==0){
				dados = par->dados;				
				removeItem(tab->tabela[i],n);
				free(par);
				return dados;	
			}
	
	else return;
}
}

void destroiTabela(THash tab){

	int i;
	int n;
	Par *par;

	for(i=0; i<tab->capacidade;i++){
		for(n=0;n<comprimentoDaLista(tab->tabela[i]);n++){
			par=(Par*) removePrimeiroItem(tab->tabela[i]);			
			free(par->chave);
			}
		free(tab->tabela[i]);
		free(tab);
	}
}



void destroiTabelaTotalmente(THash tab){

	int i, n;
	Par *par;
	
	for(i=0; i<tab->capacidade;i++){
		for(n=0;n<comprimentoDaLista(tab->tabela[i]);n++){
			par=(Par*) removePrimeiroItem(tab->tabela[i]);			
			free(par->chave);
			free(par->dados);
			}
		free(tab->tabela[i]);
		free(tab);
	}
}


int tamanho(THash tab){ 
	int i , n;

	for(i=0,n=0;i < tab->capacidade;i++) {
		if (tab->tabela[i]!=NULL)
		n++;
	}

		return n;
}




	
	







