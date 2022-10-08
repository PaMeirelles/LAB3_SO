#include "utility.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

s_processo * carrega_processo(char * linha, unsigned short * num_processos){
  char * indices[4];
  char buffer[100];
  int i;
  s_processo * processo = malloc(sizeof(s_processo));
  *num_processos += 1;
  processo->id = *num_processos;
  processo->state = 0;
  processo->decorrido = 0;
  
  indices[0] = strstr(linha, "exec ");
  indices[1] = strstr(linha,  ", prioridade=");
  indices[2] = strstr(linha,  ", inicio_tempo_execucao=");
  indices[3] = strstr(linha,  ", tempo_total_execucao=");
  
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
    buffer[j] = *(indices[1] + 13 + j);
  }
  buffer[i] = '\0';

  processo->prio = atoi(buffer);
  
  i = indices[3] - indices[2] - 24;
  for(int j=0; j < i; j++){
    buffer[j] = *(indices[2] + 24 + j);
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
  printf("\nId:%d\nNome: %s\nPrioridade:%d\nInicio:%d\nDuracao:%d\nDecorrido:%d\n", processo->id,
  processo->nome, processo->prio, processo->inicio, processo->duracao, processo->decorrido);
}

void printa_prio(s_no_prio * head){
    printf("\nPrioridade: %d\n\n", head->prio);

  s_no_processo * p = head->no;
  if(p == NULL){
    return;
  }
  while(p->next != head->no){
    printa_processo(p->processo);
    p = p->next;
  }
  printa_processo(p->processo);
}

void printa_tudo(s_no_prio * head){
  while(head){
    printa_prio(head);
    head = head->next;
    }
  printf("---------------\n");
}
s_no_processo * create_no_processo(s_processo * p){
  s_no_processo * no = malloc(sizeof(s_no_processo));
  no->processo = p;
  no->next = NULL;

  return no;
}

s_no_prio * create_no_prio(unsigned short prio){
  s_no_prio * no = malloc(sizeof(s_no_prio));
  no->prio = prio;
  no->no = NULL;
  no->next = NULL;

  return no;
}

void add_to_prio(s_no_processo * processo, s_no_prio * prio){
  if(prio->no == NULL){
    prio->no = processo;
    processo->next = processo;
  }
  s_no_processo * temp = prio->no->next;

  prio->no->next = processo;
  processo->next = temp;
}

void add_prio_level(s_no_prio * head, s_no_prio * prio_level){
  while(head->next){
    head = head->next;
  }
  head->next = prio_level;
}

int add_process(s_no_processo * no, s_no_prio * head){
  while(head != NULL){
    if(no->processo->prio == head->prio){
      
      add_to_prio(no, head);
      return 0;
    }
    head = head->next;
  }
  printf("Nivel de prioridade(%d) não encontrado\n", no->processo->prio);
  return -1;
}

int remove_from_prio(char * nome, s_no_prio * head){
  s_no_processo * first = head->no;
  s_no_processo * p = head->no;
  s_no_processo * temp;
  if(first->next == first){
    free(first);
    head->no = NULL;
    return 0;
  }
  do{
    if(strcmp(nome, p->next->processo->nome) == 0){
      if(p->next == p){
        head->no = NULL;
      }
      else{

        head->no = head->no->next;
      }
      temp = p->next->next;
      free(p->next);
      p->next = temp;
      return 0;
    }
    else{
      p = p->next;
    }
  }while(head != first);
  return 1;
}

int remove_processo(char * nome, unsigned short prio, s_no_prio * head){
  while(head){
    if(head->prio == prio){
      remove_from_prio(nome, head);
      return 0;
    }  
    head = head->next;
  }
  return 1;
}

s_no_prio * init_prios(unsigned short n){
  if(n < 1){
    return NULL;
  }
  s_no_prio * ancora = create_no_prio(0);
  s_no_prio * temp;
  for(int i=1; i < n; i++){
    temp = create_no_prio(i);
    add_prio_level(ancora, temp);
  }
  return ancora;
}
