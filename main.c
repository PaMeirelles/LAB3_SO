#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "interpretador.h"
#include "escalonador.h"

int main(void) {
  unsigned short n_processos = 0;
  s_processo ** processos = le_entrada(&n_processos);
  s_no_processo * running = NULL;
  struct timeval inicio, ultima_mod, agora, ultimo_inc;
  gettimeofday(&inicio, NULL);
  gettimeofday(&ultimo_inc, NULL);
  gettimeofday(&ultima_mod, NULL);
  s_no_prio * base = init_prios(7);
  while(1){
    interpreta(inicio, processos, base);
    escalona(&inicio, &ultima_mod, &ultimo_inc, base, &running);
  }
  }


