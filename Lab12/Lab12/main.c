//
//  main.c
//  Lab12
//
//  Created by Bruna Aleixo on 11/23/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "listaprio2.h"
#include "grafo.h"

int main(void) {
    int i,n=8, no;
    int info, v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    ListaP* lp = listap_cria(30);
    int * caminhos;

    
    for (i=0;i<n;i++) {
        listap_insere(lp,v[i], i);
        printf("insere %d, ", v[i]);
        debug_listap_show(lp, "lp= ");
    }
    printf("\n\n\n");
    
    do{
        info = listap_remove(lp);
        printf("remove %d ", info);
        debug_listap_show(lp, "lp=");
        n--;
    } while(n>0);
    
    printf("\n\n\n");

    
    listap_libera(lp);
    
    Grafo * g = grafoLe("grafo.dat");
    grafoMostra("Grafo dado: ",g);
    
    while (1) {
        printf ("no origem? (-1 para fim):");
        scanf("%d", &no);
        if (no==-1) break;
        caminhos = menoresCaminhos(g, no);
        if (caminhos == NULL) printf ("no invalido!\n");
        else {
            for (i=0; caminhos[i]!=-1; i++)
                printf ("menor caminho de %d ate %d: %d\n", no, i, caminhos[i]);
            free (caminhos);
        }
    }
    
    free(g);
    
    return 0;
}
