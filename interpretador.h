#include <sys/time.h>

s_processo ** le_entrada(unsigned short * n);
void interpreta(struct timeval inicio, s_processo ** processos, unsigned short * states, int size);