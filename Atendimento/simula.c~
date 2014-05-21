#include <stdio.h>
#include "sim.h"

// 1 mes de simulacao
#define DURACAO (86400*30)
#define CAPACIDADE 4

int main() {
  Atendente * caixa;
  Fila * fila = criaFila();
  double U, dt;

  caixa = criaAtendente(CAPACIDADE, 60, 5, fila);
  dt = simula(DURACAO, 30, 10, caixa);

  printf("Tempo total de simulação (real): %.4fs\n", dt);
  U = caixa->tempo_total/DURACAO;
  printf("Utilização: %.2f/%d (%.1f %%)\n", U, CAPACIDADE, 100*U/CAPACIDADE);
  printf("Atendimentos: %d\n", caixa->atendimentos);
  printf("Chegadas: %d\n", caixa->chegadas);
  printf("Atendimento mais rapido: %.2f s\n", caixa->mais_rapido);
  printf("Atendimento mais demorado: %.2f s\n", caixa->mais_demorado);
  printf("Atendimento medio: %.2f s\n", caixa->tempo_total/caixa->atendimentos);
  printf("Tempo maximo na fila: %.2f s\n", caixa->maior_espera);
  printf("Tempo minimo na fila: %.2f s\n", caixa->menor_espera);
  printf("Tempo medio na fila: %.2f s\n", caixa->tempo_fila/caixa->atendimentos);
  printf("Comprimento maximo da fila: %d\n", caixa->fila_max);
  printf("Comprimento medio da fila: %.2f\n", (float)caixa->fila_total/caixa->fila_cont);

  return 0;
}
