struct processo{
  char * nome;
  unsigned short id;
  unsigned short prio;

  unsigned int inicio;
  unsigned int duracao;
  unsigned int decorrido;
} typedef s_processo;

struct no_processo{
  s_processo * processo;
  struct no_processo * next;
}typedef s_no_processo;

struct no_prio{
  unsigned short prio;
  s_no_processo * no;
  struct no_prio * next;
}typedef s_no_prio;

void printa_prio(s_no_prio * head);
void printa_tudo(s_no_prio * head);
s_no_processo * create_no_processo(s_processo * p);
s_no_prio * create_no_prio(unsigned short prio);
void add_to_prio(s_no_processo * processo, s_no_prio * prio);
void add_prio_level(s_no_prio * head, s_no_prio * prio_level);
int add_process(s_no_processo * no, s_no_prio * head);
int remove_from_prio(char * nome, s_no_prio * head);
int remove_processo(char * nome, unsigned short prio, s_no_prio * head);
void printa_processo(s_processo * processo);
s_processo * carrega_processo(char * linha, unsigned short * num_processos);
s_no_prio * init_prios(unsigned short n);
unsigned short * init_states(int size);