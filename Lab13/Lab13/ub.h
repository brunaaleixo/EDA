//
//  ub.h
//  Lab13
//
//  Created by Bruna Aleixo on 11/30/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

typedef struct suniaoBusca UniaoBusca;

UniaoBusca* ub_cria(int tam);
/* cria particao de conjunto com tam elementos */
/* cada elemento estÃ¡ inicialmente em parte separada */

int ub_busca (UniaoBusca* ub, int u);
/* retorna o representante da parte em que estÃ¡ u */

int ub_uniao (UniaoBusca* ub, int u, int v);
/* retorna o representante do resultado */

void ub_libera (UniaoBusca* ub);
/* libera a estrutura */

void debug (UniaoBusca *ub);
