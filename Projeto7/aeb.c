#include <stdlib.h>
#include "aeb.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



Aeb * criaFolha(double valor){
  Aeb* folha;

	folha=(Aeb*)malloc(sizeof(Aeb));
	folha->valor=valor;
	folha->operador=0;
	folha->esq=NULL;
	folha->dir=NULL;

  return folha;
}

Aeb * criaRaiz(char operador){
  Aeb* raiz;

	raiz=(Aeb*)malloc(sizeof(Aeb));
	raiz->operador=operador;
	raiz->esq=NULL;
	raiz->dir=NULL;

  return raiz;
}

void conectaNodos(Aeb * raiz, Aeb * esq, Aeb * dir){
  raiz->esq=esq;
  raiz->dir=dir;
}

double resolveExpressao(Aeb * arvore){
  char op;
  double r;
  int i;
	
	if(arvore==NULL) return 0;
	
	if(arvore->esq==NULL && arvore->dir==NULL) return arvore->valor;

	op=arvore->operador;

	switch (op){
	
		case '+' :
			r=resolveExpressao(arvore->esq) + resolveExpressao(arvore->dir);
			break;

		case '-' :
			r=resolveExpressao(arvore->esq) - resolveExpressao(arvore->dir);
			break;
		
		case '*' :
			r=resolveExpressao(arvore->esq) * resolveExpressao(arvore->dir);
			break;

		case '/' :
			r=resolveExpressao(arvore->esq) / resolveExpressao(arvore->dir);
			break;

		case '^' : 
			r=pow(resolveExpressao(arvore->esq),resolveExpressao(arvore->dir));
			break;
	}

	return r;
}

int isoperator(char c) {
  switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
	return 1;
  }
  return 0;
}

Aeb ** trataArvore(char *exp){
 
  static char *aux;
  double x;
  Aeb **end;
  end=(Aeb**)malloc(128*sizeof (Aeb*));
  int n=0;
	
	
	while((*exp!=0) && (n < 127)){	
		x=strtod(exp,&aux);

		if(*aux=='('){
			
			aux++;			
			end[n++]=criaArvore(aux);	
		}	
				
		if (aux == exp){ 
			printf("Nao conseguiu converter um numero\n");
			printf("\nExpressão inválida\n");
			exit(1);
			return NULL;
		}
		//para continuar a partir de onde não conseguiu converter
		exp = aux;	
		//pular se for espaço		
		while(isspace(*exp)){
			exp++;
		} 	
		printf("Numero: %g\n", x);	
		printf("Próximo caractere: %c\n",*exp);
		end[n++]=criaFolha(x);
		
		if(*aux==')'){
			exp++;
			aux=exp;
			end[n]=NULL;
			return end;
		
		}
		
		/*if(*exp=='('){
			static char *c;
			c=exp;			
			criaArvore(c);	
		}	
		if(*exp==')'){
			exp++;			
			return end;
		
		}
		*/
		if(isoperator(*exp)){
			end[n++]=criaRaiz(*exp);	
		} else if (*exp == 0) {
		          end[n] =NULL;
		          return end;
	        }
		exp++;
	}
	return NULL;
}

void agrupa(Aeb ** vetor,char * c){
int n, i;

	if(vetor[1]==NULL) return;

	for(n=1;vetor[n]!=NULL;n++){
	  if((vetor[n]->operador != 0) && strchr(c,vetor[n]->operador)){
		vetor[n]->esq=vetor[n-1];
		vetor[n]->dir=vetor[n+1];
		vetor[n-1]=vetor[n];
		for(i=n;vetor[i+1]!=NULL;i++){
		vetor[i]=vetor[i+2];		
		}
		n--;
	  }	
	}




}

Aeb * criaArvore(char * expr) {
  // faz a análise sintática, que resulta um vetor de tokens (i.e. vetor de arvores)
  Aeb ** tokens = trataArvore(expr);
  Aeb * arvore;
 
  // se a análise sintática falhou, retorna NULL
  if (tokens == NULL) return NULL;
 
  // Agrupa as árvores do vetor, respeitando a precedência dos operadores.
  agrupa(tokens, "^");
  agrupa(tokens, "*/");
  agrupa(tokens, "+-");
 
  // Ao final do processo, a árvore de expressão binária está na 1a posição do vetor
  arvore = tokens[0];
  free(tokens);
 
  return arvore;
}
	
void mostraArvore(Aeb * arvore) {
  if (arvore == NULL) return;
  mostraArvore(arvore->esq);
  if ((arvore->esq == NULL) && (arvore->dir == NULL)) printf("%g", arvore->valor);
  else printf("%c", arvore->operador);
  mostraArvore(arvore->dir);
}

