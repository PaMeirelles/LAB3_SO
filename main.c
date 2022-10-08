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
  printa_processo(processos[0]);
  while(1){
    interpreta(inicio, processos, states, n_processos);
    //gettimeofday(&agora, NULL);
    //printf("%d", agora.tv_sec - inicio.tv_sec);
    sleep(1);

  }
    }