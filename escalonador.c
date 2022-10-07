#include "escalonador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printa_prio(s_no_prio * head){
  s_no_processo * p = head->no;
  printf("\nPrioridade: %d\n\n", head->prio);
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
  while(head){
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
  do{
    if(strcmp(nome, p->next->processo->nome) == 0){
      if(p->next == first){
        head->no = p;
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
      printf("%d\n", head->prio);

  while(head){
    /*
    if(head->prio == prio){
      remove_from_prio(nome, head);
      return 0;
    }
    */
    head = head->next;
  }
  return 1;
}
