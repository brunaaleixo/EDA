//
//  esparsas.h
//  nlab6
//
//  Created by Bruna Aleixo on 10/6/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

typedef struct smatrix tsm;

tsm* createFromFile (FILE *h);
/* cria matriz a partir de arquivo com formato:
 numlinhas numcolunas
 numelementos
 linha coluna valor
 linha coluna valor
 ...
 linha coluna valor
 */

int* matrixvectormult (tsm* a, int *b, int tamb);
/* multiplica matriz por vetor - se dimensões erradas retorna NULL */

void debug_listas(tsm* matriz);

void debug_vetor(int* v, int n);
