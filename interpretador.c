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
    return processos;
}

void interpreta(struct timeval inicio, s_processo ** processos, unsigned short * states, int size){
  struct timeval agora;
  gettimeofday(&agora, NULL);
  printf("Tempo: %ds\n", (agora.tv_sec - inicio.tv_sec));
  for(int i=0; i < size; i++){
    if(states[i] == 0 && ((agora.tv_sec - inicio.tv_sec) >= processos[i]->inicio)){
      printf("Manda o processo %d!\n", processos[i]->id);
      states[i] = 1;
    }

  }
  
}