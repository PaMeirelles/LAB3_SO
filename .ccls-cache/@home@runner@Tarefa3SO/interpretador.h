struct processo{
  char * nome;
  unsigned short prio;
  unsigned int inicio;
  unsigned int duracao;
} typedef s_processo;
void printa_processo(s_processo * processo);
s_processo * carrega_processo(char * linha);