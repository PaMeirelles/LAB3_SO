#include "utility.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void escalona(struct timeval * inicio, struct timeval * ultima_mod, struct timeval * ultimo_inc, s_no_prio * base, s_no_processo ** running){
  s_no_prio * p = base;
  struct timeval agora;
  int over = 0;
  int pid;
  gettimeofday(&agora, NULL);
  
  if((agora.tv_sec - ultimo_inc->tv_sec) < 1){
    return;
  }
  printf("Tempo: %ds\n", agora.tv_sec - inicio->tv_sec);

  gettimeofday(ultimo_inc, NULL);
  if(*running != NULL){
      (*running)->processo->decorrido += 1;
  }

  if((*running) != NULL &&   (*running)->processo->decorrido >=   (*running)->processo->duracao){
    remove_processo((*running)->processo->nome, (*running)->processo->prio, base);
    over = 1;
    *running = NULL;
    }

  while(1){
    if(p == NULL){
      printf("Fim do programa\n");
      exit(1);
    }
    if(p->no == NULL){
      p = p->next;
    }
    else{
      break;
    }
  }


    if((*running) != NULL && (agora.tv_sec - ultima_mod->tv_sec) % 3 != 0 && (*running)->processo->prio == p->no->next->processo->prio){
    return;
  }


  if(!over && (*running) == p->no->next && (*running) != NULL){
    return;
    }


  if((*running) != NULL){
    printf("Interrompe %s\n", (*running)->processo->nome);
   (*running)->processo->state = 3;
    if((*running) == p->no){
        p->no = p->no->next;
    }
  }

  if(p->no->processo->state == 1){
    printf("Inicia processo %s\n", p->no->processo->nome);
    if(pid=fork() == 0){
      p->no->processo->id = getpid();
      execve(p->no->processo->nome, NULL, NULL);
    }
  }
  else if(p->no->processo->state == 3){
    printf("Retoma processo %s\n", p->no->processo->nome);
  }
  else{
    printf("Deu merda %d\n", p->no->processo->state);
    exit(1);
  }
  gettimeofday(ultima_mod, NULL);

  p->no->processo->state = 2;
  *running = p->no;
  return;
}