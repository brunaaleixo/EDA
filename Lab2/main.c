#include <stdio.h> 
#include <limits.h>
#include <time.h>
#include "mapa.h"

#define TAM 10

Mapa* preenche (Mapa* m, int inicio, int fim) {
/* para usar no programa teste com: preenche(meumapa2, 0, TAM) */
	int meio;

	if (inicio>fim) 
	  	return m;
  
	meio = (fim+inicio)/2;
	m = insere(m, meio, meio*2);
	m = preenche(m, inicio, meio-1);
	m = preenche(m, meio+1, fim);
  	
	return m;
}


int main() {
	Mapa* meumapa1 = cria();
	Mapa* meumapa2 = cria();

	int i;
	clock_t inicioBusca1, fimBusca1, tempoBusca1, inicioRemocao1, fimRemocao1, tempoRemocao1, inicioBusca2, fimBusca2, tempoBusca2, inicioRemocao2, fimRemocao2, tempoRemocao2;

	
	// TESTE INSERE
	for (i=0; i<TAM; i++) 
		meumapa1 = insere(meumapa1, i, 2*i);


	
	// TESTE IMPRIME
   	imprimeMapa(meumapa1); 

	// TESTE BUSCA
	if (busca(meumapa1, 3) != INT_MAX) {
		printf("\nEncontrou elemento de chave 3\n");
	}
	else {
		printf("\nNão encontrou elemento de chave 3\n");
	}

	// TESTE REMOVE
	meumapa1 = removeMapa(meumapa1, 3);
	if (meumapa1 != NULL) {
		printf("Removeu com exito o elemento de chave 3\n");
	} 
	else {
		printf("Não encontrou o elemento de chave 3\n");	
	}
   	imprimeMapa(meumapa1); 

	
	// TESTE DESTROI
	printf("\nDestroiMapa\n"); 
	destroi(meumapa1);
	imprimeMapa(meumapa1);
	

	
	//Clock Busca Mapa 1
    	inicioBusca1 = clock();
	busca(meumapa1, TAM-1);
	fimBusca1 = clock();
     
	tempoBusca1 = (double)(fimBusca1 - inicioBusca1) / CLOCKS_PER_SEC;

	printf("\nInicio 1 busca: %ld", inicioBusca1);
    	printf("\nFinal 1 busca: %ld", fimBusca1);
    	printf("\nTempo 1 busca: %ld\n", tempoBusca1);

	//Clock Remocao Mapa 1
	inicioRemocao1 = clock();
	meumapa1 = removeMapa(meumapa1, TAM-1);
	fimRemocao1 = clock();
     
	tempoRemocao1 = (double)(fimRemocao1 - inicioRemocao1) / CLOCKS_PER_SEC;
	
	printf("\nInicio 1 remocao: %ld", inicioRemocao1);
    	printf("\nFinal 1 remocao: %ld", fimRemocao1);
    	printf("\nTempo 1 remocao: %ld\n", tempoRemocao1);



	preenche(meumapa2, 0, TAM);

	//Clock Busca Mapa 2
    	inicioBusca2 = clock();
	busca(meumapa2, TAM-1);
	fimBusca2 = clock();
     
	tempoBusca2 = (double)(fimBusca2 - inicioBusca2) / CLOCKS_PER_SEC;

	printf("\nInicio 2 busca: %ld", inicioBusca2);
    	printf("\nFinal 2 busca: %ld", fimBusca2);
    	printf("\nTempo 2 busca: %ld\n", tempoBusca2);

	//Clock Remocao Mapa 2
	inicioRemocao2 = clock();
	meumapa2 = removeMapa(meumapa2, TAM-1);
	fimRemocao2 = clock();
     
	tempoRemocao2 = (double)(fimRemocao2 - inicioRemocao2) / CLOCKS_PER_SEC;
	
	printf("\nInicio 2 remocao: %ld", inicioRemocao2);
    	printf("\nFinal 2 remocao: %ld", fimRemocao2);
    	printf("\nTempo 2 remocao: %ld\n", tempoRemocao2);


	return 0;
}
