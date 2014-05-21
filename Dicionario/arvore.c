#include <stdlib.h>
#include "arvore.h"
#include <stdio.h>

Tree * criaArvore(void *dados){
Tree* raiz;

	raiz=(Tree*)malloc(sizeof(Tree));
	raiz->dados=dados;
	raiz->pai=NULL;
	raiz->esq=NULL;
	raiz->dir=NULL;

return raiz;
}

Tree* adicionaItemArvore(Tree* arvore, void* dados, FCompara comparador)
{
Tree * folha;
int i=0;
	
for(;;){	
i=comparador(dados,arvore->dados);
		if(i==0) return;		
		if(i<0){
		if(arvore->esq==NULL){		
			folha=criaArvore(dados);
			arvore->esq=folha;
			folha->pai=arvore;
			return;		
		}
		else
		arvore=arvore->esq;
			
	}
	if(i>0){
		if(arvore->dir==NULL){
		folha=criaArvore(dados);
		arvore->dir=folha;
		folha->pai=arvore;
		return;		
		}
		else
		arvore=arvore->dir;		
		
		
	}
}
}


void mostraArvore(Tree * arvore, FMostra conversor){
if(arvore==NULL) return;

printf("%s\n", conversor(arvore->dados));
mostraArvore(arvore->esq, conversor);
mostraArvore(arvore->dir, conversor);
}

void * obtemItemArvore(Tree* arvore, void * dados, FCompara comparador){
int i=0;

	if (arvore == NULL) return NULL;

	i=comparador(arvore->dados,dados);

	if(i==0) return arvore->dados;

	if(i<0)	return obtemItemArvore(arvore->esq,dados,comparador);
	
	if(i>0) return obtemItemArvore(arvore->dir,dados,comparador);
	
}

void gravaArvore(Tree * arvore,FMostra conversor,FILE *f){

  if(f==NULL){
  	printf("\nErro ao abrir o arquivo\n");
	return;
	}  

	if(arvore==NULL){ 
	fprintf(f,"\n");
	return;
	}

	fprintf(f,"%s\n",conversor(arvore->dados));

	
	gravaArvore(arvore->esq,conversor,f);
	gravaArvore(arvore->dir,conversor,f);

}
