#include <stdio.h>
#include <stdlib.h>
#include "teste.h"

int* gerar_vetor_prioridades() {
	int i, qtd, prioridade, *prioridades; 
	FILE* entrada;
	entrada = fopen("entrada-1000000-troca", "r");
	
	if (entrada == NULL) {
		printf("Erro na abertura do arquivo\n");
		exit(1);
	}
	fscanf(entrada, "%d", &qtd);

	prioridades = (int*)malloc(sizeof(int)*qtd);
	if(prioridades == NULL) {
		printf("Memoria insuficiente");
		exit(1);
	}

	for(i=0; i<qtd; i++) {
		fscanf(entrada, "%d", &prioridade);
		prioridades[i] = prioridade; 
	}
	
	fclose(entrada);

	return prioridades;
}
