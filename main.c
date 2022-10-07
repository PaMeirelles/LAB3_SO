#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

int main(void) {
  char * linha1 = "exec p1, prioridade=3, inicio_tempo_execucao=10, tempo_total_execucao=8";
  char * linha2 = "exec p2, prioridade=2, inicio_tempo_execucao=2, tempo_total_execucao=9";
  char * linha3 = "exec p3, prioridade=1, inicio_tempo_execucao=3, tempo_total_execucao=11";
  char * linha4 = "exec p4, prioridade=2, inicio_tempo_execucao=4, tempo_total_execucao=13";
  char * linha5 = "exec p5, prioridade=1, inicio_tempo_execucao=5, tempo_total_execucao=14";

  s_processo * processo1 = carrega_processo(linha1);
  s_processo * processo2 = carrega_processo(linha2);
  s_processo * processo3 = carrega_processo(linha3);
  s_processo * processo4 = carrega_processo(linha4);
  s_processo * processo5 = carrega_processo(linha5);

  s_no_prio * base = init_prios(7);

  s_no_processo * p1 = create_no_processo(processo1);
  s_no_processo * p2 = create_no_processo(processo2);
  s_no_processo * p3 = create_no_processo(processo3);
  s_no_processo * p4 = create_no_processo(processo4);
  s_no_processo * p5 = create_no_processo(processo5);

  add_process(p1, base);
  add_process(p2, base);
  add_process(p3, base);
  add_process(p4, base);
  add_process(p5, base);

  
  printa_tudo(base);

  remove_processo("p1", 3, base);
  printa_tudo(base);
}