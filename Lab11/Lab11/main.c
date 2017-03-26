//
//  main.c
//  Lab11
//
//  Created by Bruna Aleixo on 11/16/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char * argv[]) {
    Grafo *g;
    
    if (argc != 2) {
        printf("Numero de parametros invalido\n");
        exit(1);
    }
    
    g = grafoLe(argv[1]);
    grafoMostra("Grafo1\n", g);
    grafoPercorreProfundidade(g, 0);

    grafoPercorreLargura(g, 0);
    grafoLibera(g);
    
    return 0;
}
