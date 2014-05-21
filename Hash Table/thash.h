#ifndef HASH_H
#define HASH_H
 
#include "glista.h"
 
struct HASH {
  Lista ** tabela; // ALTERAÇÃO: cada linha da tabela contém uma lista encadeada
  int capacidade;
};
 
// O tipo "THash" equivale a um ponteiro para "struct HASH"
typedef struct HASH * THash;
 
// ALTERAÇÃO: declaração da struct PAR, que representa o par (chave, valor)
struct PAR {
  char * chave;
  void * dados;
};
 
// o tipo "Par" representa o par (chave, valor) guardados na lista encadeada 
// associada a cada linha da tabela.
typedef struct PAR Par;
 
// Esta função é interna à tabela de dispersão ... não deve ser usada diretamente
int funcao_hash(THash tabela, char * chave);
 
// Abaixo estão as funções que formam a interface da tabela de dispersão.
// Quem for usar esta tabela (tipo THash) deve manipulá-la somente por meio
// dessas funções.
 
// Cria uma tabela de dispersão com uma determinada capacidade.
THash criaTabela(int capacidade);
 
// Destroi uma tabela de dispersão (porém não destrói os dados lá guardados).
void destroiTabela(THash tab);
 
// Destroi uma tabela de dispersão, incluindo os dados lá guardados.
void destroiTabelaTotalmente(THash tab);
 
// Obtem um dado associado a uma determinada chave. Se ele não estiver
// na tabela, retorna NULL.
void * obtemItemTabela(THash tab, char * chave);
 
// Adiciona um dado associado a uma determinada chave.
// Se a posição da tabela já estiver ocupada (o que se chama "colisão"), alguma
// medida deve ser tomada: ou o dado não é guardado e de alguma forma retorna-se um erro, 
// ou sobrescreve-se o dado existente.
void adicionaItemTabela(THash tab, char * chave, void * dados);
 
// Remove um dado associado a uma determinada chave (e o retorna).
void * removeItemTabela(THash tab, char * chave);
 
// retorna quantos dados existem na tabela
int tamanhoTabela(THash tab);
 
// O tipo FMostra define como deve ser uma funcao que mostre o valor de um dado
// armazenado na tabela. Funcoes como essa devem retornar uma representacao em string de
// um dado que esta na tabela.
typedef char* (*FMostra)(void*);
 
// Mostra os dados que estao na tabela. "func" eh uma funcao
// que sabe mostrar os dados na tela.
// Se "func" for NULL, será mostrado somente o endereço de memória de cada dado.
void mostraTabela(THash tab, FMostra func);
 
#endif
