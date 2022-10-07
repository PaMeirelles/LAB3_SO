#include <stdio.h>
#include <stdlib.h>
#include "interpretador.h"

int main(void) {
  s_processo * processo = malloc(sizeof(s_processo));

  processo->nome = "teste";
  processo->prio = 3;
  processo->inicio = 15;
  processo->duracao = 20;

  printa_processo(processo);
}