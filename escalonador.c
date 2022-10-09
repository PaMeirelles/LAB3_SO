#include "utility.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void escalona(struct timeval * ultima_mod, s_no_prio * base, s_no_processo ** running){
  // variaveis
  s_no_prio * p = base;
  struct timeval agora;
  int over = 0;
  // checa se uma UT se passou
  gettimeofday(&agora, NULL);
  // printa report
  if(*running != NULL){
      (*running)->processo->decorrido += 1;
    }
  // Se um processo rodou tudo que precisava, removemos ele
  if((*running) != NULL &&   (*running)->processo->decorrido >= (*running)->processo->duracao){
    char * nome = (*running)->processo->nome;
    unsigned short prio = (*running)->processo->prio;
    kill((*running)->processo->id, SIGKILL);
     remove_processo(nome, prio, base);
    over = 1;
    *running = NULL;
    }
  // Encontramos o nível de prioridade não-vazio mais alto, e encerramos o programa caso não haja
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

  // Se o próximo da fila era o próprio processo já rodando, retornamos
  if(!over && (*running) == p->no->next && (*running) != NULL){
    gettimeofday(ultima_mod, NULL);
    return;
    }
  
  // Se a maior prioridade está no mesmo nível do anterior e ainda não acabou o time slice, retornamos
    if((*running) != NULL && (agora.tv_sec - ultima_mod->tv_sec) % 3 != 0 && (*running)->processo->prio == p->no->next->processo->prio){
    return;
  }

  // Interrompemos o processo que executava
  if((*running) != NULL){
    kill((*running)->processo->id, SIGSTOP);
   (*running)->processo->state = 3;
    // Se o processo que rodava se encontra na maior prioridade, damos a vez ao proximo
    if((*running) == p->no){
        p->no = p->no->next;
    }
  }

  // Caso o processo nunca tenha sido executado, o criamos
  if(p->no->processo->state == 1){

    acha_processo(p->no->processo->nome, p->no->processo->prio, base)->processo->id = getpid();

    if(fork() != 0){
      execve(p->no->processo->nome, NULL, NULL);
    }
  }
  // Caso esteja em espera, retomamos
  else if(p->no->processo->state == 3){
    kill(p->no->processo->id, SIGCONT);

  }
  // Se chegamos aqui, deu merda em algum lugar
  else{
    printf("Deu merda %d\n", p->no->processo->state);
    exit(1);
  }
  gettimeofday(ultima_mod, NULL);

  p->no->processo->state = 2;
  *running = p->no;

  return;
}