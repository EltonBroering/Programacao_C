#include <stdio.h>
#include "glista.h"
 
int compara(void * x1, void * x2) {
  int * p1 = x1, *p2 = x2;

  if (*p1 < *p2) return -1;
  return *p1 > *p2;
}
 
int main() {
  Lista * lista;
  int numeros[10] = {1,2,3,4,5,6,7,8,9,10};
  int *p, i=10;
 
  lista = criaLista();
 
  p = numeros;
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
  insereOrdenado(lista, (void*)p++);
 
  mostraLista(lista);
 
  removePrimeiroItem(lista);
  printf("Apos remover primeiro item:\n");
  mostraLista(lista);
 
  removeItem(lista, lista->comprimento-1);
  printf("Apos remover ultimo item:\n");
  mostraLista(lista);
 
  insereOrdenado(lista, (void*)p++);
  printf("Apos adicionar mais um item:\n");
  mostraLista(lista);

  while (i > 0) {
    removePrimeiroItem(lista);
    printf("Apos remover primeiro item:\n");
    mostraLista(lista);
    i--;
  }
return 0;
}
