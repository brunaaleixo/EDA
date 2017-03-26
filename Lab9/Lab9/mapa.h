//
//  mapa.h
//  Lab9
//
//  Created by Bruna Aleixo on 10/30/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave);
int busca (Mapa *m, int chave);
Mapa* retira (Mapa *m, int chave); /* atenção! nome mudou :-) */
void destroi (Mapa *m);


void debug_mostra_mapa (Mapa *m);
