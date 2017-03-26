#include <stdio.h> 

typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
int busca (Mapa *m, int chave);
Mapa* removeMapa (Mapa *m, int chave);
void destroi (Mapa *m);
void imprimeMapa(Mapa* m);
