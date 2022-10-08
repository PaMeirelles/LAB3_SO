#define BUFFER_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"


s_processo ** le_entrada(unsigned short * n){  
    s_processo ** processos = malloc(8 * BUFFER_SIZE);
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    fp = fopen("entrada.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        processos[counter] = carrega_processo(line, n);
      counter++;
    }

    fclose(fp);
    if (line)
        free(line);
    processos[counter] = NULL;
    return processos;
}

void interpreta(struct timeval inicio, s_processo ** processos, s_no_prio * base){
  //printa_processo((*(processos+1)));
  s_processo ** p = processos;
  struct timeval agora;
  gettimeofday(&agora, NULL);
  while(*p != NULL){
    if((*p)->state == 0 && ((agora.tv_sec - inicio.tv_sec) >= (*p)->inicio)){
      //printf("Manda o processo %s!\n", (*p)->nome);
      s_no_processo * np = create_no_processo(*p);
      add_process(np, base);
     (*p)->state = 1;
      }
      p++;

  }
}