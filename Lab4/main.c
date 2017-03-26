//
//  main.c
//  nlab4
//
//  Created by Bruna Aleixo on 9/24/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "mapa.h"

#define TAM 10000000

Mapa* preenche (Mapa* m, int inicio, int fim) {
    /* para usar no programa teste com: preenche(meumapa2, 0, TAM) */
    int meio;
    
    if (inicio>fim)
        return m;
    
    meio = (fim+inicio)/2;
    m = insere(m, meio, meio*2);
    m = preenche(m, inicio, meio-1);
    m = preenche(m, meio+1, fim);
    
    return m;
}


int main() {
    Mapa* meumapa1 = cria();
    Mapa* meumapa2 = cria();
    
    //int i;
    clock_t inicio, fim, tempo;
    
    /*
    // TESTE INSERE
    for (i=0; i<TAM; i++) {
        meumapa1 = insere(meumapa1, i, 2*i);
    }
    
     // TESTE IMPRIME
     debug_mostra_mapa(meumapa1);
    
    
     // TESTE BUSCA
     if (busca(meumapa1, 3) != INT_MAX) {
     	printf("\nEncontrou elemento de chave 3\n");
     }
     else {
     	printf("\nNão encontrou elemento de chave 3\n");
     }
    
     // TESTE REMOVE
     meumapa1 = removeMapa(meumapa1, 1);
     if (meumapa1 != NULL) {
     	printf("Removeu com exito o elemento de chave 3\n");
     }
     else {
     	printf("Não encontrou o elemento de chave 3\n");
     }
     debug_mostra_mapa(meumapa1);
    
    
     // TESTE DESTROI
     printf("\nDestroiMapa\n");
     destroi(meumapa1);
    */
    
     //Clock Busca Mapa 1
     inicio = clock();
     busca(meumapa1, TAM-1);
     fim = clock();
    
     tempo = (double)(fim - inicio);
     printf("\nTempo 1 busca: %ld\n", tempo);
    
    
     //Clock Remocao Mapa 1
     inicio = clock();
     meumapa1 = removeMapa(meumapa1, TAM-1);
     fim = clock();
    
     tempo = (double)(fim - inicio);
     printf("\nTempo 1 remocao: %ld\n", tempo);
    
    
    
     preenche(meumapa2, 0, TAM);
    
     //Clock Busca Mapa 2
     inicio = clock();
     busca(meumapa2, TAM-1);
     fim = clock();
    
     tempo = (double)(fim - inicio);
     printf("\nTempo 2 busca: %ld\n", tempo);
    
    
     //Clock Remocao Mapa 2
     inicio = clock();
     meumapa2 = removeMapa(meumapa2, TAM-1);
     fim = clock();
    
     tempo = (double)(fim - inicio);
     printf("\nTempo 2 remocao: %ld\n", tempo);
    
    
    return 0;
}
