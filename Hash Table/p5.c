#include <stdio.h>
#include "thash.h"
#include<stdlib.h>
 
// As chaves dos valores a serem armazenados
#define CHAVE1 "abcd"
#define CHAVE2 "xyz2"
#define CHAVE3 "3qwert"
 
// Tamanho default da tabela
#define CAPACIDADE 5
 
// Funcao para converter os dados armazenados em strings
char* mostra(void * p) {
  return (char*)p;
}

char* func (void *p){
	return (char*)p;
}

int main(int argc, char ** argv) {
  THash tab;
  int capacidade;
 
  if (argc < 2) capacidade = CAPACIDADE;
  else {
    if (sscanf(argv[1], "%d", &capacidade) < 1) capacidade = CAPACIDADE;
  }
 
  tab = criaTabela(capacidade);
 
  adicionaItemTabela(tab, CHAVE1, "primeira frase");
  adicionaItemTabela(tab, CHAVE2, "segunda frase");
  adicionaItemTabela(tab, CHAVE3, "terceira frase");
 
  printf("tab[%s]=%s\n", CHAVE1, (char*)obtemItemTabela(tab, CHAVE1));
  printf("tab[%s]=%s\n", CHAVE2, (char*)obtemItemTabela(tab, CHAVE2));
  printf("tab[%s]=%s\n", CHAVE3, (char*)obtemItemTabela(tab, CHAVE3));

  removeItemTabela(tab, CHAVE1);

  printf("tab[%s]=%s\n", CHAVE1, (char*)obtemItemTabela(tab, CHAVE1));
  printf("tab[%s]=%s\n", CHAVE2, (char*)obtemItemTabela(tab, CHAVE2));
  printf("tab[%s]=%s\n", CHAVE3, (char*)obtemItemTabela(tab, CHAVE3));

  
 
  puts("");
  mostraTabela(tab, NULL);
 
  puts("");
  mostraTabela(tab, mostra);
 
  destroiTabela(tab);

  printf("tab[%s]=%s\n", CHAVE1, (char*)obtemItemTabela(tab, CHAVE1));
  printf("tab[%s]=%s\n", CHAVE2, (char*)obtemItemTabela(tab, CHAVE2));
  printf("tab[%s]=%s\n", CHAVE3, (char*)obtemItemTabela(tab, CHAVE3));
 
  return 0;
}
