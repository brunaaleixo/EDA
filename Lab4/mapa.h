//
//  mapa.h
//  nlab4
//
//  Created by Bruna Aleixo on 9/24/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>

typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
int busca (Mapa *m, int chave);
Mapa* removeMapa (Mapa *m, int chave);
void destroi (Mapa *m);
void debug_mostra_mapa(Mapa* m);

