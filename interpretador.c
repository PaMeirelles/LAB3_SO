#include "interpretador.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

s_processo * carrega_processo(char * linha){
  char * indices[4];
  char buffer[100];
  int i;
  s_processo * processo = malloc(sizeof(s_processo));
  
  indices[0] = strstr(linha, "exec ");
  indices[1] = strstr(linha,  ", prioridade=");
  indices[2] = strstr(linha,  ", inicio_tempo_execucao=");
  indices[3] = strstr(linha,  ", tempo_total_execucao=");
  printf("%p %p %p %p\n", indices[0], indices[1], indices[2], indices[3]);
  
  for(int j=0; j < 4; j++){
    if(!indices[j]){
      printf("Erro de sintaxe no argumento %d\n", j+1);
      exit(-j);
    }
  }
  
  i = indices[1] - indices[0] - 5;
  processo->nome = malloc(i);
  for(int j=0; j < i; j++){
    processo->nome[j] = *(indices[0] + 5 + j);
  }
  
  i = indices[2] - indices[1] - 13;
  for(int j=0; j < i; j++){
    buffer[j] = *(indices[i] + 13 + j);
  }
  processo->prio = atoi(buffer);
  
  i = indices[3] - indices[2] - 24;
  for(int j=0; j < i; j++){
    buffer[j] = *(indices[i] + 24 + j);
  }
  buffer[i] = '\0';
  processo->inicio = atoi(buffer);
  
  char * p = indices[3]+23;
  int counter = 0;
  while(*p){
    buffer[counter] = *p;
    counter++;
    p++;
  }
  buffer[counter] = '\0';
  processo->duracao = atoi(buffer);
  
  return processo;
}

void printa_processo(s_processo * processo){
  printf("Nome: %s\nPrioridade:%d\nInicio:%d\nDuracao:%d\n",
  processo->nome, processo->prio, processo->inicio, processo->duracao);
}