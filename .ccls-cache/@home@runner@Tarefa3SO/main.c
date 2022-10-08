#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "interpretador.h"

int main(void) {
  unsigned short n_processos = 0;
  s_processo ** processos = le_entrada(&n_processos);
  unsigned short * states = init_states(n_processos);
  struct timeval inicio, agora;
  gettimeofday(&inicio, NULL);

  s_no_prio * base = init_prios(7);
  printa_tudo(base);
  while(1){
    interpreta(inicio, processos, states, n_processos);
    printa_tudo(base);
    //gettimeofday(&agora, NULL);
    //printf("%d", agora.tv_sec - inicio.tv_sec);
    sleep(1);
    printf("-------------\n");

  }
    }