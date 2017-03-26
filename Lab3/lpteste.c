#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaprio.h"
#include "teste.h"


int compara (const void* a, const void* b) {
  int *ia = (int*)a;
  int *ib = (int*)b;
  if (*ia>*ib)
    return 1;
  else if (*ib>*ia)
    return -1;
  else return 0;
}

int main(void) {
  int n=1000;
  int *v, *vordenado;
  clock_t inicio3, fim3, tempo3, inicio4, fim4, tempo4;
  ListaP *lp1;
  
  v = gerar_vetor_prioridades();


  printf("\nHEAPSORT\n");
  inicio3 = clock();
  lp1 = listap_cria(n, n, v);
  vordenado = cria_listaordenada(lp1, &n); 
  fim3 = clock();

  tempo3 = (double)(fim3 - inicio3);
	
  printf("\nInicio: %ld", inicio3);
  printf("\nFinal: %ld", fim3);
  printf("\nTempo em clocks: %ld", tempo3);
  printf("\nTempo em segundos: %ld\n", (tempo3/CLOCKS_PER_SEC));

  // printf("{");
  // for (i=0;i<n;i++) {
  //   printf ("%d,", v[i]);
  // }
  // printf("}\n");



  printf("\nQUICKSORT\n");
  inicio4 = clock();
  qsort(v, n, sizeof(int), compara);
  fim4 = clock();

  tempo4 = (double)(fim4 - inicio4);
  
  printf("\nInicio: %ld", inicio4);
  printf("\nFinal: %ld", fim4);
  printf("\nTempo em clocks: %ld", tempo4);
  printf("\nTempo em segundos: %ld\n", (tempo4/CLOCKS_PER_SEC));


  // printf("{");
  // for (i=0; i<n; i++)
  //    printf("%d,",vordenado[i]);
  // printf("}\n");


  return 0;
}

