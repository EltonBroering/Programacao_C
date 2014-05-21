#include <stdio.h>
#include <stdlib.h>
#include "glista.h"
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
 *
 * 
 */


Fila * criaFila(){
 return criaLista();
}

  Lista *criaLista() {
    Lista * lista;

    lista = (Lista*) malloc(sizeof ( Lista));
 
    lista->primeiro = NULL;
    lista->comprimento = 0;
 
    return lista;
}

struct Nodo *  criaNodo (void *dados) {
    struct Nodo * nodo;

    nodo = (struct Nodo *) malloc (sizeof (struct Nodo));

    if(nodo == NULL) return NULL;

    nodo->dados=dados;
    nodo->proximo = NULL;
    return nodo;
}


 int    adicionaItem(Lista * lista, void *dados) {
  struct Nodo * nodo;
 
  
  if (lista == NULL) return 0;
 
  nodo  = criaNodo(dados);
  if (nodo == NULL) return 0;
 
	if(lista->comprimento==0){
		lista->primeiro=nodo;
		lista->comprimento++;
		nodo->proximo=NULL;
		return 1;
	}  

  nodo->proximo = lista->primeiro;
  lista->primeiro = nodo;
 
  lista->comprimento++;
 
  return 1;
}


int adicionaItemNoFim(Lista * lista,void *dados){

	struct Nodo * nodo;
	struct Nodo * fim;
	
	if (lista->comprimento == 0){
		nodo  = criaNodo(dados);
		if (nodo == NULL) return 0;
		lista->primeiro=nodo;
		lista->comprimento++;
		nodo->proximo=NULL;
		return 1;
	}

	nodo= criaNodo(dados);
	for(fim=lista->primeiro;fim->proximo !=NULL;fim=fim->proximo);
	fim->proximo = nodo;
	nodo->proximo = NULL;
	lista->comprimento++;
	return 1;
}

void* obtemItem(Lista * lista, unsigned int posicao){
  struct Nodo *nodo;
  int i=0;


  if(posicao>=lista->comprimento) return NULL;  
  
  nodo=lista->primeiro;


  while(i<posicao){
      nodo=nodo->proximo;
      i++;
  }
  return nodo->dados;
}
	 


void * removePrimeiroItem(Lista * lista){
       
  struct Nodo *removNodo;
  void *aux;
 
  
        if (lista->comprimento == 0)       
                return NULL;       
  
        	
                
		removNodo=lista->primeiro;
		aux=removNodo->dados;		
		lista->primeiro= lista->primeiro->proximo;    
		free(removNodo);     
                lista->comprimento--;       
                return aux;       
        
}





   // a função malloc aloca dinamicamente uma certa quantidade de bytes.
  // ela retorna um ponteiro para a área de memória alocada, ou NULL
  // se não conseguir realizar a alocação (ex: acabou a memória livre).

void   destroiLista(Lista * lista){
    
	while(lista->comprimento>0) removePrimeiroItem(lista);
	free(lista);
}




// A função free libera uma área de memória que foi alocada anteriormente com malloc
// umNodo é uma variável do tipo "struct Nodo *"


/*void mostraLista(Lista *lista, FMostra f){
    struct Nodo *aux;
    int posicao=0;
    
	if(lista->comprimento==0){
	printf("A lista esta vazia\n");
	return;
	}	   
     for(aux=lista->primeiro; aux != NULL; aux=aux->proximo, posicao++){
         printf("Nodo %d: %s\n",posicao, f(aux->dados));
                  
     }
}

*/

int comprimentoDaLista(Lista*lista){
	return lista->comprimento;
}

int enfileira(Fila * fila, void * dados){
	return adicionaItemNoFim(fila,dados);
}

void * desenfileira(Fila * fila){
       return removePrimeiroItem(fila);       
}

/*void insereOrdenado(Lista * lista, void * dados){

	struct Nodo *ant, *p, *nodo;
	
		if(lista->comprimento==0){
			return adicionaItem(lista, dados);
			
		}

	//mostraLista(lista);
		for (ant=NULL, p=lista->primeiro; p != NULL; ant=p, p=p->proximo){
                        if (p->dados == NULL) {
			  printf("%p, %p\n", p, p->dados);			
                          //mostraLista(lista);
                         }
			if( compara(p->dados, dados)>0){
				if(ant==NULL){
					adicionaItem(lista, dados);
					return;
				}
			nodo=criaNodo(dados);
			ant->proximo=nodo;
			nodo->proximo=p;
			lista->comprimento++;
			return;
			}
		}
	nodo=criaNodo(dados);
	ant->proximo=nodo;
	lista->comprimento++;
	} 
*/
void *  removeItem(Lista * lista, unsigned int posicao){

struct Nodo *ant, *prox;
void *aux;

if(lista->comprimento==0){
printf("A lista já esta vazia\n");
return;
}

if(lista->comprimento==1){
prox=lista->primeiro;
aux=prox->dados;
free(prox);
lista->primeiro=NULL;
lista->comprimento--;
return aux;
}

if(posicao==0){
	return removePrimeiroItem(lista);
}
if (posicao>=lista->comprimento-1){
	for(ant=NULL,prox=lista->primeiro;prox->proximo!=NULL;ant=prox,prox=prox->proximo);
	ant->proximo=NULL;
	aux=prox->dados;		
	free(prox);
	lista->comprimento--;
return aux;
}
for(ant=NULL,prox=lista->primeiro;posicao>0;ant=prox,prox=prox->proximo,posicao--);
ant->proximo=prox->proximo;
aux=prox->dados;		
free(prox);
lista->comprimento--;
return aux;
}



