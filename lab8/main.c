#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include "mapa.h"

#define TAM 5

int main(void) {

    int i;

    Mapa *mapa1 = cria();
    Mapa *mapa2 = cria();
    Mapa *mapa3 = cria();
    Mapa *mapa4 = cria();

    printf("insercao sempre a esquerda\n");
    for (i=TAM-1;i>=0;i--) {
       mapa1 = insere (mapa1, i, i);
    }
    debug_mostra_mapa(mapa1);

    //insercao da raiz
    mapa2 = insere(mapa2,1,1);
    
    //RLb
    printf("caso RLb\n");
    mapa2 = insere (mapa2,27,27);
    mapa2 = insere (mapa2,2,2);
    debug_mostra_mapa(mapa2);
    
    //RLr
    printf("caso rlr\n");
    mapa2 = insere (mapa2,15,15);
    debug_mostra_mapa(mapa2);
    
    //LLr
    printf("caso llr\n");
    mapa2 = insere (mapa2,35,35);
    mapa2 = insere (mapa2,9,9);
    debug_mostra_mapa(mapa2);
    
    //LRb
    printf("caso lrb\n");
    mapa2 = insere(mapa2,11,11);
    debug_mostra_mapa(mapa2);
    
    //LRr
    printf("caso lrr\n");
    mapa2 = insere(mapa2,10,10);
    debug_mostra_mapa(mapa2);

    //RRr
    printf("caso rrr\n");
    mapa2 = insere(mapa2,12,12);
    mapa2 = insere(mapa2,17,17);
    mapa2 = insere(mapa2,18,18);
    debug_mostra_mapa(mapa2);
    
    
    //NOVO MAPA
    //LLb
    printf("caso llb\n");
    mapa3 = insere(mapa3,4,4);
    mapa3 = insere(mapa3,3,3);
    mapa3 = insere(mapa3,2,2);
    debug_mostra_mapa(mapa3);
    
    //NOVO MAPA
    //RRb
    printf("caso rrb\n");
    mapa4 = insere(mapa4,4,4);
    mapa4 = insere(mapa4,5,5);
    mapa4 = insere(mapa4,6,6);
    debug_mostra_mapa(mapa4);


    return 0;
}


