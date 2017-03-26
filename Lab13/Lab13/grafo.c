//
//  grafo.c
//  Lab13
//
//  Created by Bruna Aleixo on 11/30/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "listaprio.h"
#include "ub.h"


typedef struct _viz Viz;
struct _viz {
    int noj;
    int peso;
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
    SQ* novo = (SQ*)malloc(sizeof(SQ));
    assert(novo);
    novo->info = info;
    novo->prox = stack;
    return novo;
}

static SQ* enqueue(SQ* queue, int info){
    SQ* novo = (SQ*)malloc(sizeof(SQ));
    assert(novo);
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

static Viz* criaViz(Viz* head, int noj, int peso) {
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
    assert(g);
    g->nv = nv;
    g->na = na;
    g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
    assert(g->viz);
    for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
    return g;
}


Grafo* grafoLe( char* filename ) {
    /* cria grafo nÃ£o orientado - supÃµe que arquivo estÃ¡ correto! */
    
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0;
    int peso;
    Grafo* novo;
    
    fscanf(arq, "%d %d", &nv, &na);
    novo = grafoCria(nv, na);
    assert(novo);
    while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
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

void grafoMostra (Grafo * grafo) {
    int i;
    if (grafo) {
        printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
        for (i = 0; i < grafo->nv; i++){
            Viz* viz = grafo->viz[i];
            printf("[%d]->", i);
            while (viz) {
                printf(" {%d, %d}", viz->noj, viz->peso);
                viz = viz->prox;
            }
            printf("\n");
        }
    }
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial){
    SQ *q = NULL;
    Viz *v; int no;
    char *visitado;
    if (grafo == NULL) return;
    visitado = (char*) malloc(sizeof(int)*grafo->nv);
    assert(visitado);
    for (no=0;no<(grafo->nv);no++) visitado[no] = 0;
    no = no_inicial;
    while (no>=0) {
        if (!visitado[no]) {
            printf ("%d-", no);
            visitado[no] = 1;
            v = grafo->viz[no];
            while (v!=NULL) {
                if (!visitado[(v->noj)]) {
                    q = push (q, v->noj);
                }
                v = v->prox;
            }
        }
        q=pop(q, &no);
    }
    printf ("\n");
}


Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
    return NULL;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial){
    SQ *q = NULL;
    Viz *v; int no;
    int *enfileirado;
    
    if (grafo == NULL) return;
    
    enfileirado = (int*) malloc(sizeof(int)*grafo->nv);
    assert(enfileirado);
    
    for (no=0;no<(grafo->nv);no++) enfileirado[no] = 0;
    
    q = enqueue (q, no_inicial);
    enfileirado[no_inicial] = 1;
    q = pop(q, &no);
    
    while (no>=0) {
        printf ("%d-", no);
        v = grafo->viz[no];
        while (v!=NULL) {
            if (!enfileirado[(v->noj)]) {
                q = enqueue (q, v->noj);
                enfileirado[v->noj] = 1;
            }
            v = v->prox;
        }
        q=pop(q, &no);
    }
    printf ("\n");
} 

Grafo* arvoreCustoMinimo (char *filename) {
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0;
    int peso, busca1, busca2;
    Grafo* novo;
    ListaP* heap;
    UniaoBusca* ub;
    
    fscanf(arq, "%d %d", &nv, &na);
    
    heap = listap_cria(na);
    ub = ub_cria(nv);
    novo = grafoCria(nv, (nv-1));
    assert(novo);
    
    while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
        listap_insere(heap, peso, no1, no2);
    }
    

    peso = listap_remove(heap, &no1, &no2);
    
    while (peso != -1) {
        busca1 = ub_busca(ub, no1);
        busca2 = ub_busca(ub, no2);
        if (busca1 != busca2){
            novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
            novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
            
            ub_uniao(ub, no1, no2);
        }

        peso = listap_remove(heap, &no1, &no2);
    }
    
    ub_libera(ub);
    listap_libera(heap);
    fclose(arq);
    
    return novo;
}


int tem_ciclo (char *filename) {
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0;
    int peso, busca1, busca2;
    ListaP* heap;
    UniaoBusca* ub;
    
    fscanf(arq, "%d %d", &nv, &na);
    
    heap = listap_cria(na);
    ub = ub_cria(nv);
    
    while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
        listap_insere(heap, peso, no1, no2);
    }
    
    fclose(arq);
    peso = listap_remove(heap, &no1, &no2);
    
    while (peso != -1) {
        busca1 = ub_busca(ub, no1);
        busca2 = ub_busca(ub, no2);
        if (busca1 != busca2){
            ub_uniao(ub, no1, no2);
        } else {
            ub_libera(ub);
            listap_libera(heap);
            return 1;
        }
        
        peso = listap_remove(heap, &no1, &no2);
    }
    
    ub_libera(ub);
    listap_libera(heap);
    
    return 0;
}

int num_componentes (char *filename) {
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0, i, cont = 0;
    int peso, busca1, busca2;
    ListaP* heap;
    UniaoBusca* ub;
    
    fscanf(arq, "%d %d", &nv, &na);
    
    heap = listap_cria(na);
    ub = ub_cria(nv);
    
    while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
        listap_insere(heap, peso, no1, no2);
    }
    
    
    peso = listap_remove(heap, &no1, &no2);
    
    while (peso != -1) {
        busca1 = ub_busca(ub, no1);
        busca2 = ub_busca(ub, no2);
        if (busca1 != busca2){
            ub_uniao(ub, no1, no2);
        }
        
        peso = listap_remove(heap, &no1, &no2);
    }
    
    for (i=0; i<nv; i++) {
        if (ub_busca(ub, i) == i) {
            cont++;
        }
    }
    
    ub_libera(ub);
    listap_libera(heap);
    fclose(arq);
    
    return cont;
}


int nv_maior_componente (char *filename) {
    FILE *arq = fopen(filename,"rt");
    int nv, na, no1, no2 = 0, i, maior;
    int peso, busca1, busca2;
    int *pais;
    ListaP* heap;
    UniaoBusca* ub;
    
    fscanf(arq, "%d %d", &nv, &na);
    
    heap = listap_cria(na);
    ub = ub_cria(nv);
    
    while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
        listap_insere(heap, peso, no1, no2);
    }
    
    peso = listap_remove(heap, &no1, &no2);
    
    while (peso != -1) {
        busca1 = ub_busca(ub, no1);
        busca2 = ub_busca(ub, no2);
        if (busca1 != busca2){
            ub_uniao(ub, no1, no2);
        }
        
        peso = listap_remove(heap, &no1, &no2);
    }
    
    pais = (int*) malloc(sizeof(int)*nv);
    assert(pais);
    
    for (i=0; i<nv; i++) {
        pais[i] = 0;
    }
    
    for (i=0; i<nv; i++) {
        pais[ub_busca(ub, i)]++;
    }
    
    maior = pais[0];
    for (i=1; i<nv; i++) {
        if (pais[i] > maior) {
            maior = pais[i];
        }
    }
    
    ub_libera(ub);
    listap_libera(heap);
    fclose(arq);
    
    return maior;
}
