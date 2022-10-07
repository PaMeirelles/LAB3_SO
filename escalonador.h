#include "interpretador.h"

struct no_processo{
  s_processo * processo;
  struct no_processo * next;
}typedef s_no_processo;

struct no_prio{
  unsigned short prio;
  s_no_processo * no;
  struct no_prio * next;
}typedef s_no_prio;

void print_prio(s_no_prio * head);
void printa_tudo(s_no_prio * head);
s_no_processo * create_no_processo(s_processo * p);
s_no_prio * create_no_prio(unsigned short prio);
void add_to_prio(s_no_processo * processo, s_no_prio * prio);
void add_prio_level(s_no_prio * head, s_no_prio * prio_level);