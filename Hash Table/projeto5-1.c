#include <stdio.h>
#include <stdlib.h>

struct HASH{
	Lista ** tabela;
	int capacidade;
};

typedef struct HASH *THash;

int funcao_hash(THash tab,char *chave){
int r=0;
int n;

for(n=0; chave[n] != 0; n++) r+=chave[n];
r=r% tab->capacidade;
return r;
}


THash criaTabela (int capacidade){
THash tab;
int i;

tab=(THash)malloc(sizeof(struct HASH));
tab->capacidade=capacidade;
tab->tabela=malloc(capacidade*sizeof(void*));
for(i=0; i<capacidade; i++) tab->tabela[i]=NULL;
return tab;
}


void *obtemItem(THash tabela, char *chave);


void adicionaItem(THash tabela, char *chave, void *dados){







