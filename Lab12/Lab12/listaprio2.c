//
//  listaprio2.c
//  Lab12
//
//  Created by Bruna Aleixo on 11/23/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "listaprio2.h"

struct _listaprio {
    int max; /* tamanho maximo do heap */
    int pos; /* proxima posicao disponivel no vetor */
    info* infos; /* vetor das prioridades */
};

struct info {
    int prioridade;
    int dado;
};

static void corrige_abaixo(info* infos, int atual, int tam);

ListaP* listap_cria(int max){
    ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio));
    heap->max=max;
    heap->pos=0;
    heap->infos = (info *)malloc(max*sizeof(info));
    return heap;
}

static void troca(int a, int b, info* v) {
    info f = v[a];
    v[a] = v[b];
    v[b] = f;
}

static void corrige_acima(ListaP* heap, int pos) {
    int pai;
    while (pos > 0){
        pai = (pos-1)/2;
        if (heap->infos[pai].prioridade > heap->infos[pos].prioridade)
            troca(pos,pai,heap->infos);
        else
            break;
        pos=pai;
    }
}

void corrige_pos(ListaP* heap, int dado, int nova) {
    int i;
    
    for(i=0; i<heap->pos; i++) {
        if (heap->infos[i].dado == dado) {
            heap->infos[i].prioridade = nova;
            corrige_acima(heap, i);
            break;
        }
    }
    
}


void listap_insere(ListaP* heap, int prioridade, int dado) {
    if ( heap->pos < heap->max ) {
        heap->infos[heap->pos].prioridade=prioridade;
        heap->infos[heap->pos].dado = dado;
        corrige_acima(heap,heap->pos);
        heap->pos++;
    }
    else {
        printf("Heap CHEIO!\n");
        exit(1);
    }
}

static void corrige_abaixo(info* infos, int atual, int tam){
    int pai=atual;
    int filho_esq, filho_dir, filho;
    while (2*pai+1 < tam){
        filho_esq=2*pai+1;
        filho_dir=2*pai+2;
        if (filho_dir >= tam) filho_dir=filho_esq;
        if (infos[filho_esq].prioridade<infos[filho_dir].prioridade)
            filho=filho_esq;
        else
            filho=filho_dir;
        if (infos[pai].prioridade>infos[filho].prioridade)
            troca(pai,filho,infos);
        else
            break;
        pai=filho;
    }
}

int listap_remove(ListaP* heap) {
    if (heap->pos>0) {
        int topo=heap->infos[0].dado;
        heap->infos[0].dado = heap->infos[heap->pos-1].dado;
        heap->infos[0].prioridade=heap->infos[heap->pos-1].prioridade;
        heap->pos--;
        corrige_abaixo(heap->infos, 0, heap->pos);
        return topo;
    }
    else {
        return -1;
    }
}

void listap_libera (ListaP * h) {
    free(h->infos);
    free(h);
}

void debug_listap_show (ListaP *h, char* title){
    int i;
    printf("%s={",title);
    for (i=0; i<(h->pos); i++)
        printf("Prioridade: %d, Dado: %d,  ",h->infos[i].prioridade, h->infos[i].dado);
    printf("}\n");
    
}
