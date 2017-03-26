//
//  main.c
//  Lab10
//
//  Created by Bruna Aleixo on 11/9/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo *grafo1, *grafo2;
    
    grafo1 = grafoLe("input.txt");
    
    grafoMostra("Grafo1", grafo1);
    
    grafoPercorreProfundidade(grafo1, 0);
    
    grafo2 = criaArvoreGeradora(grafo1, 0);
    
    grafoMostra("Grafo2", grafo2);
    
    return 0;
}
