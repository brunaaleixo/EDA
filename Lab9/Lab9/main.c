//
//  main.c
//  Lab9
//
//  Created by Bruna Aleixo on 10/30/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include "mapa.h"

int main() {
    int result;
    Mapa* mapa1 = cria();
    
    mapa1 = insere(mapa1, 10);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 13);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 7);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 8);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 6);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 11);
    debug_mostra_mapa(mapa1);
    mapa1 = insere(mapa1, 12);
    debug_mostra_mapa(mapa1);
    
    // buscar chave existente
    result = busca(mapa1, 13);
    result ? printf("\nEncontrou 13\n"): printf("\nNao encontrou 13\n");
    result = busca(mapa1, 6);
    result ? printf("Encontrou 6\n"): printf("Nao encontrou 6\n");
    
    // buscar chave inexistente
    result = busca(mapa1, 20);
    result ? printf("Encontrou 20\n\n"): printf("Nao encontrou 20\n\n");
    

    mapa1 = retira(mapa1, 10);
    debug_mostra_mapa(mapa1);

    
    return 0;
}
