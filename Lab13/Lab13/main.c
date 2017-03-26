//
//  main.c
//  Lab13
//
//  Created by Bruna Aleixo on 11/30/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include "grafo.h"

int main(int argc, const char * argv[]) {

    Grafo * g = arvoreCustoMinimo("grafo.dat");
    grafoMostra(g);
    
    if (tem_ciclo("grafo.dat")) {
        printf("Tem ciclo\n");
    } else {
        printf("Nao tem ciclo\n");
    }
    
    
    printf("Numero de componentes conexos: %d\n", num_componentes("grafo.dat"));
    printf("Raiz com mais componentes: %d\n", nv_maior_componente("grafo.dat"));
    
    return 0;
}
