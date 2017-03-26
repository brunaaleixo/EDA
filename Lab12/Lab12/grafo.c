//
//  grafo.c
//  Lab12
//
//  Created by Bruna Aleixo on 11/23/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "listaprio2.h"

typedef struct _viz Viz;
struct _viz {
    int noj;
    float peso;
    Viz*  prox;
};

struct _grafo {
    int nv;           /* numero de nos ou vertices */
    int na;           /* numero de arestas */
    Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila e pilha */
typedef struct _sq SQ;
struct _sq {
    int info;
    SQ* prox;
};

static void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, int* visitados);
static void criaArvoreGeradoraRec (Grafo *novoGrafo, Grafo *grafo, int no_inicial, int* visitados);

static SQ* push(SQ* stack, int info){
    /* empilha um item */
    SQ* novo = (SQ*)malloc(sizeof(SQ));
    assert(novo);
    novo->info = info;
    novo->prox = stack;
    return novo;
}

static SQ* enqueue(SQ* queue, int info){
    /* enfileira um item */
    SQ* novo = (SQ*)malloc(sizeof(SQ));
    SQ* aux = queue;
    assert(novo);
    novo->info = info;
    novo->prox = NULL;
    if (!queue){
        return novo;
    }
    while (aux->prox){
        aux = aux->prox;
    }
    aux->prox = novo;
    return queue;
}

static SQ* pop(SQ* stack,int* popped_info){
    /* retira um item da fila/pilha */
    SQ* libera;
    if (!stack){
        *popped_info = -1;
        return NULL;
    }
    *popped_info = stack->info;
    libera = stack;
    stack = stack->prox;
    free(libera);
    return stack;
}

static Viz* criaViz(Viz* head, int noj, float peso) {
    /* insere vizinho no inicio da lista */
    Viz* no = (Viz*) malloc(sizeof(Viz));
    assert(no);
    no->noj = noj;
    no->peso = peso;
    no->prox = head;
    return no;
}

static Grafo* grafoCria(int nv, int na) {
    
    int i;
    Grafo* g = (Grafo *) malloc(sizeof(Grafo));
    g->nv = nv;
    g->na = na;
    g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
    for (i = 0; i < nv; i++)
        g->viz[i] = NULL;
    return g;
}


Grafo* grafoLe( char* filename ) {
    /* cria grafo nÃ£o orientado - supÃµe que arquivo estÃ¡ correto! */
    
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0;
    float peso;
    Grafo* novo;
    
    fscanf(arq, "%d %d", &nv, &na);
    novo = grafoCria(nv, na);
    assert(novo);
    while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
        novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
        novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
    }
    return novo;
}

Grafo* grafoLibera(Grafo* grafo) {
    if (grafo) {
        int i = 0;
        Viz* no,*aux;
        for (i = 0; i < grafo->nv; i++){
            no = grafo->viz[i];
            while (no){
                aux = no->prox;
                free(no);
                no = aux;
            }
        }
        free(grafo->viz);
        free(grafo);
    }
    return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
    int i;
    if (title)
        printf("%s", title);
    if (grafo) {
        printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
        for (i = 0; i < grafo->nv; i++){
            Viz* viz = grafo->viz[i];
            printf("[%d]->", i);
            while (viz) {
                printf("{%d, %g}->", viz->noj, viz->peso);
                viz = viz->prox;
            }
            printf("NULL\n");
        }
    }
}


void grafoPercorreProfundidade(Grafo *grafo, int no_inicial){
    int i;
    int* visitados = (int*)malloc(sizeof(int)*grafo->nv);
    assert(visitados);
    
    for (i = 0; i < grafo->nv; i++) {
        visitados[i] = 0;
    }
    
    grafoPercorreProfundidadeRec(grafo, no_inicial, visitados);
}

static void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, int* visitados) {
    Viz* elem;
    
    if (visitados[no_inicial] == 0) {
        printf("%d ", no_inicial);
        visitados[no_inicial] = 1;
    }
    
    for(elem = grafo->viz[no_inicial]; elem != NULL; elem = elem->prox) {
        if (visitados[elem->noj] == 0) {
            grafoPercorreProfundidadeRec(grafo, elem->noj, visitados);
        }
    }
    
}

Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
    Grafo* novoGrafo;
    int i;
    int* visitados = (int*)malloc(sizeof(int)*grafo->nv);
    assert(visitados);
    
    if (grafo == NULL) {
        return NULL;
    }
    
    novoGrafo = grafoCria(grafo->nv, 0);
    
    for (i = 0; i < grafo->nv; i++) {
        visitados[i] = 0;
    }
    
    criaArvoreGeradoraRec(novoGrafo, grafo, no_inicial, visitados);
    printf("\n");
    
    return novoGrafo;
    
}

static void criaArvoreGeradoraRec (Grafo *novoGrafo, Grafo *grafo, int no_inicial, int* visitados) {
    Viz* viz;
    
    visitados[no_inicial] = 1;
    
    for (viz = grafo->viz[no_inicial]; viz != NULL; viz = viz->prox) {
        if (visitados[viz->noj] == 0) {
            novoGrafo->na++;
            novoGrafo->viz[no_inicial] = criaViz(novoGrafo->viz[no_inicial], viz->noj, viz->peso);
            novoGrafo->viz[viz->noj] = criaViz(novoGrafo->viz[viz->noj], no_inicial, viz->peso);
            criaArvoreGeradoraRec(novoGrafo, grafo, viz->noj, visitados);
        }
    }
    
}
void grafoPercorreLargura(Grafo *grafo, int no_inicial){
    int i, poppedInfo;
    Viz *viz;
    SQ* fila;
    
    int* visitados = (int*)malloc(sizeof(int) * grafo->nv);
    assert(visitados);
    
    for (i = 0; i < grafo->nv; i++) {
        visitados[i] = 0;
    }
    
    fila = enqueue(fila, no_inicial);
    fila = pop(fila, &poppedInfo);
    visitados[no_inicial] = 1;
    
    while (poppedInfo != -1) {
        printf("%d ", poppedInfo);
        
        viz = grafo->viz[poppedInfo];
        while (viz) {
            if (visitados[viz->noj] == 0) {
                fila = enqueue(fila, viz->noj);
                
                visitados[viz->noj] = 1;
            }
            viz = viz->prox;
        }
        
        fila = pop(fila, &poppedInfo);
    }
    printf("\n");
}


int* menoresCaminhos(Grafo* grafo, int noinicial) {
    int i, no;
    Viz *viz;
    ListaP* heap;
    
    int* caminhos = (int*) malloc(sizeof(int)*(grafo->nv+1));
    assert(caminhos);
    
    int* visitados = (int*) malloc(sizeof(int)*grafo->nv);
    assert(visitados);

    heap = listap_cria(grafo->nv);

    for(i=0; i<grafo->nv; i++) {
        caminhos[i] = INT_MAX;
        visitados[i] = 0;
        listap_insere(heap, INT_MAX, i);
    }
    
    caminhos[noinicial] = 0;
    corrige_pos(heap, noinicial, 0);
    
    no = listap_remove(heap);
    
    for(i=0; i<grafo->nv; i++) {
        visitados[no] = 1;
        
        for (viz = grafo->viz[no]; viz != NULL; viz = viz->prox) {
            if (!visitados[viz->noj]) {
                if (caminhos[viz->noj] > (viz->peso + caminhos[no])) {
                    caminhos[viz->noj] = (viz->peso + caminhos[no]);
                    corrige_pos(heap, viz->noj, (viz->peso + caminhos[no]));

                }
            }
        }
        
        no = listap_remove(heap);
    }
    
    caminhos[grafo->nv] = -1;
    
    return caminhos;
}

