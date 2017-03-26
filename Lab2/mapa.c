#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"

struct smapa {
	int chave;
	int dado;
	Mapa* esq;
	Mapa* dir;
};

Mapa* cria() {
	return NULL;
}

Mapa* cria_no(int chave, int dado) {
	Mapa* no = (Mapa*) malloc(sizeof(Mapa));

	if (no == NULL) {
		printf("Memoria insuficiente\n");
		exit(1);
	}

	no->chave = chave;
	no->dado = dado;
	no->esq = no->dir = NULL;

	return no;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
	if (m == NULL)
		return cria_no(chave, novodado);
	else if (chave < m->chave) 
		m->esq = insere(m->esq, chave, novodado);
	else 
		m->dir = insere(m->dir, chave, novodado);

	return m;
}


int busca (Mapa *m, int chave) {
	while(m != NULL) {
		if (chave < m->chave) {
			m = m->esq;
		} 
		else if (chave > m->chave) {
			m = m->dir;
		} 
		else {
			return m->dado;
		}
	}

	return INT_MAX;
}

Mapa* removeMapa(Mapa* m, int chave) { 
	Mapa *sucessor, *temp;
	if ( m == NULL )
	{
		return NULL;
	}
	else if (chave < m->chave)
	{
		m->esq = removeMapa(m->esq, chave);
	}
	else if (chave > m->chave)
	{
		m->dir = removeMapa(m->dir, chave);
	}
	else /* achou o nó a remover */
	{ 
		if (m->esq == NULL && m->dir == NULL) /* nó sem filhos */
		{ 
			free (m); 
			m = NULL;
		}
		else if (m->esq == NULL) /* nó só tem filho à direita */
		{
			Mapa* t = m;
			m = m->dir;
			free (t);
		}
		else if (m->dir == NULL) /* só tem filho à esquerda */
		{
			Mapa* t = m; 
			m = m->esq; 
			free (t);
		}
		else {/* nó tem os dois filhos: busca o sucessor */
			// o sucessor é o menor nó da subárvore da direita
			sucessor = m->dir;

			while (sucessor->esq != NULL) {
			// o temporario armazena o valor do 'pai' do sucessor
				temp = sucessor;
				sucessor = sucessor->esq;
			}

			
			// caso o sucessor tenha nó a direita, esse nó vai substituir a 			posicao do sucessor
			if (sucessor->dir != NULL) {
				temp->esq = sucessor->dir;
			}

			m->chave = sucessor->chave;
			m->dado = sucessor->dado;
			free(sucessor);
		}
	}

	return m;
}


void destroi(Mapa* m){
	if (m != NULL) {
		destroi(m->esq);
		destroi(m->dir);
		free(m);
	}
}

void imprimeMapa(Mapa* m) {
	if(m != NULL) {
		printf("%d ", m->chave);
	        imprimeMapa(m->dir);
	        imprimeMapa(m->esq);
	}
}

