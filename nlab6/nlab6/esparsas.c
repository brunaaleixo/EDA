//
//  esparsas.c
//  nlab6
//
//  Created by Bruna Aleixo on 10/6/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "esparsas.h"


struct smatrix {
    int l, c, j; /* número de linhas e colunas */
    int nelems;
    int *vals;
    int *cols;
    int *ri;
};

static int descobreFimLinha(tsm* a, int i);

tsm* createFromFile (FILE *h) {
    int i, j, linha, linhaAnt = -1;
    tsm *matriz;
    
    matriz = (tsm*)malloc(sizeof(tsm));
    if (matriz == NULL) {
        return NULL;
    }
    
    fscanf(h, " %d %d %d", &matriz->l, &matriz->c, &matriz->nelems);
    
    matriz->vals = (int*)malloc(sizeof(int)*(matriz->nelems));
    if (matriz->vals == NULL) {
        return NULL;
    }
    
    matriz->cols = (int*)malloc(sizeof(int)*(matriz->nelems));
    if (matriz->cols == NULL) {
        return NULL;
    }
    
    matriz->ri = (int*)malloc(sizeof(int)*(matriz->l));
    if (matriz->ri == NULL) {
        return NULL;
    }
    
    
    for (i = 0; i< matriz->nelems; i++) {
        fscanf(h, " %d %d %d", &linha, &matriz->cols[i], &matriz->vals[i]);
        
        if(linha == linhaAnt + 1) {
            matriz->ri[linha] = i;
        } else if (linha >= linhaAnt + 1) {
            // Compara a linha atual com a linha anterior registrada. Caso a diferença for maior que um, significa que entre essas linhas pelo menos uma linha está em branco. Popula todas essas linhas em branco como tendo índice de -1
            for(j=linhaAnt+1; j<linha; j++) {
                matriz->ri[j] = -1;
            }
            matriz->ri[linha] = i;
        }
        
        linhaAnt = linha;
        
    }
    
    return matriz;
    
}


void debug_listas(tsm* matriz) {
    int i, numLinhas, numElementos;
    
    numLinhas = matriz->l;
    numElementos = matriz->nelems;
    
    printf("Linhas: %d\ncolunas: %d\nNumero de elementos: %d\n\n", numLinhas, matriz->c, numElementos);
    
    printf("Lista valores:\n");
    for(i = 0; i< numElementos; i++) {
        printf("%d ", matriz->vals[i]);
    }
    
    printf("\n\nLista colunas:\n");
    for(i = 0; i< numElementos; i++) {
        printf("%d ", matriz->cols[i]);
    }
    
    printf("\n\nLista indices das linhas:\n");
    for(i = 0; i< numLinhas; i++) {
        printf("%d ", matriz->ri[i]);
    }
    
    printf("\n\n");
}

void debug_vetor(int* v, int n) {
    int i;
    
    printf("\nVetor resultante da multiplicacao:\n");
    for(i = 0; i< n; i++) {
        printf("%d ", v[i]);
    }
    
    printf("\n\n");
}


int* matrixvectormult (tsm* a, int *b, int tamb) {
    int i, k, fimLinha;
    int* mult;
    
    mult = (int*) malloc(sizeof(int)*(tamb));
    
    for (i = 0; i < tamb; i++) {
        mult[i] = 0;
        if (a->ri[i]>=0) {
            fimLinha = descobreFimLinha(a, i);
            // descobre quantos elementos tem em uma determinada linha
            for (k = a->ri[i]; k < fimLinha; k++) {
                
                // multiplica o k-ésimo valor nao nulo na matriz pelo valor do pelo elemento que se encontra na posicao da coluna desse valor no vetor passado 
                mult[i] += a->vals[k]*b[a->cols[k]];
            }
        }
    }
    
    return mult;
}


static int descobreFimLinha(tsm* a, int i) {
    int j = i;
    // se o proximo indice da linha for menor que zero, significa que a linha está em branco. Portanto, o indice da lista de valores que representa o fim da linha atual será o próximo que for maior que zero
    if (a->ri[i+1] < 0) {
        while (a->ri[j+1] < 0) {
            j++;
        }
        return a->ri[j+1];
    }
    
    //  Se o proximo índice da linha for maior do que a quantidade de linhas menos um (subtrai um porque o a primeira posicao do vetor é zero e não um) significa que a linha atual é a última. Índice do ultimo elemento dessa linha corresponde à quantidade de elementos.
    if (i+1 > a->l-1) {
        return a->nelems;
    }
    
    return a->ri[i+1]; 
}
