#include <stdlib.h>
#include "arvore.h"
#include <stdio.h>
#include <string.h>

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

	printf("(");
	mostraArvore(arvore->esq, conversor);
	printf(",%s,", conversor(arvore->dados));	
	mostraArvore(arvore->dir, conversor);
	printf(")");
}


void * obtemItemArvore(Tree* arvore, void * dados, FCompara comparador){
int i=0;

	if (arvore == NULL) return NULL;

	i=comparador(arvore->dados,dados);

	if(i==0) return arvore->dados;

	if(i>0)	return obtemItemArvore(arvore->esq,dados,comparador);
	
	if(i<0) return obtemItemArvore(arvore->dir,dados,comparador);
	
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
Tree * carregaArvore(FILE * f, FParser leitor){
	Tree* raiz;
	char buffer[1024];

	fgets(buffer, 1023,f);
	
	if(!feof(f)) {
		buffer[strlen(buffer)-1]=0; //remove o /n final
		if(buffer[0]==0) return NULL;
		

//se consegue ler mas nao chegou ao fim do arquivo
		raiz=criaArvore(leitor(buffer));


		raiz->esq=carregaArvore(f, leitor);
			if(raiz->esq!=NULL) raiz->esq->pai=raiz;

		raiz->dir=carregaArvore(f,leitor);
			if(raiz->dir!=NULL) raiz->dir->pai=raiz;
}
return raiz;
}



int altura(Tree * arvore){
    int hesq, hdir,i;
    
	
	if(arvore==NULL) return 0;
	
	if((arvore->esq==NULL) && (arvore->dir==NULL)) return 0;

	hesq=altura(arvore->esq);
	hdir=altura(arvore->dir);

	
	if(hdir < hesq) {
	//i=(hesq+1);
	//printf("%d\n", i);
	return (hesq+1);
	}
	
	else {
	//i=(hdir+1);
	//printf("%d\n", i);
	return (hdir+1);
	}
}

int fatorB(Tree * arvore) {
  int hesq=0, hdir=0;

	if(arvore->esq!=NULL) hesq=1+altura(arvore->esq);
		
	if(arvore->dir!=NULL) hdir=1+altura(arvore->dir);

	return hesq-hdir;

}

Tree * balanceiaArvore(Tree * arvore){

  int hesq=0, hdir=0,FB=0,he=0,hd=0;

	if(arvore==NULL) return NULL;
	
	if((arvore->esq==NULL) && (arvore->dir==NULL)) return arvore;

	arvore->esq=balanceiaArvore(arvore->esq);
		
	arvore->dir=balanceiaArvore(arvore->dir);
	
	
	while(fatorB(arvore)<-1){
	he=0,hd=0;
		if(arvore->dir->esq != NULL) he=1+altura(arvore->dir->esq);
		if(arvore->dir->dir != NULL) hd=1+altura(arvore->dir->dir);		
			
		if(he > hd) arvore=rotacao_RL(arvore);
		
		arvore=rotacao_RR(arvore);	
	}
  
		
	while(fatorB(arvore)>1){
	he=0,hd=0;	
		if(arvore->esq->esq != NULL) he=1+altura(arvore->esq->esq);
		if(arvore->esq->dir != NULL) hd=1+altura(arvore->esq->dir);		
			
		if(he < hd) arvore=rotacao_LR(arvore);
		
		arvore=rotacao_LL(arvore);
	}
	
	/*if(hesq > hdir){

		if(arvore->esq->esq != NULL) he=1+altura(arvore->esq->esq);
		if(arvore->esq->dir != NULL) hd=1+altura(arvore->esq->dir);
		
		if(he < hd) rotacao_LR(arvore->esq->dir);
		
		rotacao_LL(arvore->esqrn arvore);
	}

	if(hdir>hesq){
		if(arvore->dir->esq != NULL) he=1+altura(arvore->dir->esq);
		if(arvore->dir->dir != NULL) hd=1+altura(arvore->dir->dir);
		
		if(hd < he) rotacao_RL(arvore->dir->esq);
	
		rotacao_RR(arvore);
	}*/

	return arvore;
}


Tree * rotacao_LL(Tree * arvore){		
  Tree * raiz,*folha;

	raiz=arvore;
	folha=arvore->esq;
	raiz->esq=folha->dir;
	folha->dir=raiz;
	return folha;

}

Tree * rotacao_RL(Tree * arvore){
	
  Tree * raiz, *folha, *ramo;

	raiz=arvore;
	folha=arvore->dir;
	ramo=folha->esq;
	raiz->dir=ramo;
	folha->esq=ramo->dir;
	ramo->dir=folha;
	return raiz;
}

Tree * rotacao_LR(Tree * arvore){

  Tree *raiz, *folha, *ramo;

	raiz=arvore;
	folha=arvore->esq;
	ramo=folha->dir;
	folha->dir=ramo->esq;	
	raiz->esq=ramo;
	ramo->esq=folha;
	return raiz;
}

Tree * rotacao_RR(Tree * arvore) {

  Tree *raiz, *folha, *ramo;

	raiz=arvore;
	folha=arvore->dir;
	raiz->dir=folha->esq;
	folha->esq=raiz;
	return folha;
}	


