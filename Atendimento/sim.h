#ifndef SIM_H
#define SIM_H

#include "glista.h"

// Um cliente possui um tipo, um horário de entrada no 
// sistema (inicio) e um horário de saída (fim).
struct CLIENTE {
  unsigned int tipo;
  double chegada, inicio;
};

typedef struct CLIENTE Cliente;


// A fila pode ser circular, implementada com vetor, ou 
// feita com uma lista encadeada.

// Um atendente pode ser um caixa de banco, um caixa automatico, 
// um balcão de recepção, ...
// id: um número que identifica o atendente
// capacidade: quantos clientes ele consegue atender por vez
// proximo: o próximo atendente para onde devem ser encaminhados os clientes, caso houver
// fila: a fila de espera dos clientes para serem atendidos
// atendimentos: a quantidade de clientes atendidos
// tempo_total: a quantidade de tempo que o atendente dispendeu atendendo clientes
// tempo_atendimento: a duração média de cada atendimento. Usado para calcular quanto 
//   tempo deve durar cada atendimento que se inicia.
struct ATENDENTE {
  unsigned int capacidade;
  unsigned int uso;
  Fila * fila;
  unsigned int atendimentos;
  double tempo_total;
  double tempo_min;
  double tempo_max;
  double mais_rapido;
  double mais_demorado;
  double maior_espera;
  double menor_espera;
  double tempo_fila;
  unsigned int fila_cont, fila_total, fila_max;
  unsigned int chegadas;
};

typedef struct ATENDENTE Atendente;

// Roda a simulação.
// duracao: a duração da simulação
// intervalo_min: o menor intervalo entre chegadas de clientes
// intervalo_max: o maior intervalo entre chegadas de clientes
// Retorna: a duração real da simulação (tempo de computação)
// Ao final, os resultados da simulação estarão em "atendente".
double simula(double duracao, double intervalo_max, double intervalo_min, Atendente * atendente);

// cria um atendente com uma certa capacidade e fila.
Atendente * criaAtendente(unsigned int capacidade, double tempo_max, double tempo_min, Fila * fila);

#endif
