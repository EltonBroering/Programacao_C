#include <stdio.h>
#include "glista.h"
 
int compara(void * x1, void * x2) {
  return 0;
}
 
int main() {
  Fila * fila;
  int numeros[10] = {1,2,3,4,5,6,7,8,9,10};
  int *p;
 
  fila = criaFila();
 
  p = numeros;
  enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
 enfileira(fila, (void*)p++);
 enfileira(fila, (void*)p++);
 enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
  enfileira(fila, (void*)p++);
 enfileira(fila, (void*)p++);
 enfileira(fila, (void*)p++);
  
 
  mostraLista(fila);
 
  desenfileira(fila);
  printf("Apos desenfileirar item:\n");
  mostraLista(fila);
 
  enfileira(fila, (void*)p++);
  printf("Apos enfileirar item:\n");
  mostraLista(fila);

  desenfileira(fila);
  printf("Apos desenfileirar item:\n");
  mostraLista(fila);
 
  enfileira(fila, (void*)p++);
  printf("Apos enfileirar item:\n");
  mostraLista(fila);
 
  while (desenfileira(fila) != NULL);
 
  printf("Apos desenfileirar da fila vazia (resultado foi %p):\n", desenfileira(fila));
  mostraLista(fila);

  enfileira(fila, (void*)p++);
  printf("Apos enfileirar item:\n");
  mostraLista(fila);
 
  return 0;
}
