//
//  listaprio2.h
//  Lab12
//
//  Created by Bruna Aleixo on 11/23/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

typedef struct _listaprio ListaP;
typedef struct info info;


/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
ListaP *listap_cria (int max);

/* insere um novo dado na lista */
void listap_insere (ListaP *lp, int prioridade, int dado);

/* remove e retorna a menor prioridade */
int listap_remove(ListaP *lp);

/* libera a lista de prioridades */
void listap_libera(ListaP *lp);

/* corrige a prioridade associada a determinado valor */
void listap_corrige (ListaP* heap, int novaprio, int dado);

/* sÃ³ para debug: enxerga representaÃ§Ã£o interna! */
void debug_listap_show (ListaP *hp, char* title);

void corrige_pos(ListaP* heap, int velha, int nova);
