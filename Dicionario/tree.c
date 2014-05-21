#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "arvore.h"

Tree * criaArvore(void * dados) {
	Tree * raiz;
	
	raiz = (Tree*)malloc(sizeof(Tree));
	raiz->dados=dados;
	raiz->pai=NULL;
	raiz->esq==NULL;
	raiz->dir==NULL;

	return raiz;
}

Tree* adicionaItemArvore( Tree* arvore, void* dados, FCompara comparador) {
Tree *folha;
int i;

	while(arvore!=NULL){
		i=comparador(arvore->dados, dados);
    		if(i==0) return;   
    		if(i < 0) { //vai pra esquerda
			if(arvore->esq==NULL){
			folha=criaArvore(dados);        		
			arvore->esq=folha;
			folha->pai=arvore;
    			}
			else arvore=arvore->esq;	
     			}
		if(i>0) { //vai pra direita
			if(arvore->dir==NULL){
			folha=criaArvore(dados);
        		arvore->dir=folha;
			folha->pai=arvore;			
    			}
			else arvore=arvore->dir;
		}
	}
}

void * obtemItemArvore(Tree* arvore, void * dados, FCompara comparador){
int i;




	if(arvore==NULL) return NULL;

	i=comparador(arvore->dados, dados);
	
	if(i==0) return arvore->dados;	
	
	if(i < 0) { //vai pra esquerda
		obtemItemArvore(arvore->esq, dados, comparador);
	}
	if(i>0) { //vai pra direita
		obtemItemArvore(arvore->dir, dados, comparador);
	}
}





void mostraArvore(Tree * arvore) {
	if(arvore == NULL) return;
	mostraArvore(arvore->dir);
	printf("%p\n",arvore->dados);
	mostraArvore(arvore->esq);
}


 int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}
 
 
 
int altura(Tree * arvore){
  







