//
//  main.c
//  nlab6
//
//  Created by Bruna Aleixo on 10/6/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "esparsas.h"


int main() {
    FILE* h;
    tsm* matriz;
    int v[5] = {0, 1, 2, 3, 2};
    int* vResult;
    
    vResult = (int*)malloc (sizeof(int) * 5);
    
    h = fopen("arq.txt", "r");
    if (h == NULL) {
        printf("Arquivo inexistente\n");
        exit(0);
    }
    
    matriz = createFromFile(h);
    
    debug_listas(matriz);
    
    vResult = matrixvectormult(matriz, v, 6);
    
    debug_vetor(vResult, 6);
    
    return 0;
}
