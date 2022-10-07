#include <stdio.h>
#include <stdlib.h>
#include "interpretador.h"

int main(void) {
  char * linha = "exec p1, prioridade=3, inicio_tempo_execucao=10, tempo_total_execucao=8";
  s_processo * processo = carrega_processo(linha);

  printa_processo(processo);
}