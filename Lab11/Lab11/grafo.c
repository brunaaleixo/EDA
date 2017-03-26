//
//  grafo.c
//  Lab11
//
//  Created by Bruna Aleixo on 11/16/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include "grafo.h"


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

void grafoPercorreProfundidade(Grafo * grafo, int no_inicial) {
    int* visitado = (int*)malloc(grafo->nv*sizeof(int));
    int i,nv = grafo->nv;
    Viz* temp;
    SQ* aux = NULL;
    assert(visitado);
    
    for (i = 0; i < grafo->nv; i++) {
        visitado[i] = 0;
    }
    i = no_inicial;
    printf("%d >", i);
    visitado[i] = 1;
    
    while(nv>1) {
        for (temp = grafo->viz[i]; temp != NULL; temp = temp->prox) {
            if (!visitado[temp->noj]) {
                aux = push(aux, temp->noj);
                visitado[temp->noj] = 1;
            }
        }
        aux = pop(aux, &i);
        if (nv>2)
            printf(" %d >", i);
        else
            printf(" %d", i);
        nv--;
    } 
    printf("\n");
}



Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
    return NULL;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial){
    int i, poppedInfo;
    Viz *viz;
    
    SQ* fila = (SQ*)malloc(sizeof(SQ));
    assert(fila);
    
    int* visitados = (int*)malloc(sizeof(int) * grafo->nv);
    assert(visitados);
    
    for (i = 0; i < grafo->nv; i++) {
        visitados[i] = 0;
    }
    
    fila = pop(fila, &poppedInfo);
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

