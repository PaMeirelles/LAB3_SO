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
  gettimeofday(&agora, NULL);

  s_no_prio * base = init_prios(7);
  freopen("saida.txt", "w", stdout);

  interpreta(inicio, processos, base);
  escalona(&ultima_mod, base, &running);
  
  while(1){
    gettimeofday(&agora, NULL);
    if((agora.tv_sec - ultimo_inc.tv_sec) >= 1){
          printf("Tempo: %d Executando: %s\n", agora.tv_sec - inicio.tv_sec, running->processo->nome);

      gettimeofday(&ultimo_inc, NULL);
      interpreta(inicio, processos, base);
      escalona(&ultima_mod, base, &running);
    }
  }
}


