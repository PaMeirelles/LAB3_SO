#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "interpretador.h"

int main(void) {
  unsigned short n_processos = 0;
  s_processo ** processos = le_entrada(&n_processos);

  s_no_prio * base = init_prios(7);

  s_no_processo * p1 = create_no_processo(processos[0]);
  s_no_processo * p2 = create_no_processo(processos[1]);
  s_no_processo * p3 = create_no_processo(processos[2]);
  s_no_processo * p4 = create_no_processo(processos[3]);
  s_no_processo * p5 = create_no_processo(processos[4]);

  printa_processo(processos[0]);
  
  add_process(p1, base);
  add_process(p2, base);
  add_process(p3, base);
  add_process(p4, base);
  add_process(p5, base);

  
  printa_tudo(base);

  remove_processo("p1", 3, base);
  printa_tudo(base);
  
    }