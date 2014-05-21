#include <stdlib.h>
#include "arvore.h"

Tree * criaArvore(void* dados) {
	Tree * raiz;
	
	raiz = (Tree*)malloc(sizeof(Tree));
	raiz->dados=dados;
	raiz->pai=NULL;
	raiz->esq==NULL;
	raiz->dir==NULL;

	return raiz;
}

void adicionaItemArvore( Tree* arvore, void* dados, FCompara comparador) {
Tree *folha;
int i;
i=comparador(arvore->dados, dados);

	while(arvore!=NULL){
	if(i==0) return;	
	if(i < 0) { //vai pra esquerda
		folha=arvore->esq;
	}
	 if(i>0) { //vai pra direita
		folha=arvore->dir;
	}
	}

folha=criaArvore(dados);
if(i<0) arvore->esq=folha;
else arvore->dir=folha;
}

void mostraArvore(Tree * arvore) {
	if(arvore == NULL) return;
	mostraArvore(arvore->dir);
	printf(arvore->dados);
	mostraArvore(arvore->esq);
}


