//
//  mapa.c
//  nlab4
//
//  Created by Bruna Aleixo on 9/24/16.
//  Copyright © 2016 Bruna Aleixo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

struct smapa {
    int chave;
    int dado;
    short int bf;
    struct smapa* esq;
    struct smapa *dir;
};

static Mapa* ajusta_dir(Mapa* m);
static Mapa* ajusta_esq(Mapa* m);
static Mapa* rotacao_dir(Mapa* m);
static Mapa* rotacao_esq(Mapa* m);
static Mapa* remove2 (Mapa *m, int chave, int *flag);
static Mapa* insere2 (Mapa* m, int chave, int novodado, int *flag);

static Mapa *cria_no (int c, int novodado) {
    Mapa *nn = (Mapa *)malloc(sizeof(Mapa));
    if (nn!=NULL) {
        nn->esq = nn->dir = NULL;
        nn->chave =c;
        nn->dado = novodado;
        nn->bf = 0;
    }
    return nn;
}

Mapa* cria (void) {
    return NULL;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
    int flag = 0;
    
    return insere2(m, chave, novodado, &flag);
}

Mapa* insere2 (Mapa* m, int chave, int novodado, int *flag) {
    if (m == NULL) {
        m = cria_no(chave, novodado);
        *flag = 1;
    }
    else if (m->chave > chave) {
        m->esq = insere2(m->esq, chave, novodado, flag);
        
        if (*flag) {
            if (m->bf == 0) {
                m->bf = -1;
            } else if (m->bf == 1) {
                m->bf = 0;
                *flag = 0;
            } else {
                m = ajusta_esq(m);
                *flag = 0;
            }
        }
    }
    else if (m->chave < chave) {
        m->dir = insere2(m->dir, chave, novodado, flag);
        
        if (*flag) {
            if (m->bf == 0) {
                m->bf = 1;
            } else if (m->bf == -1) {
                m->bf = 0;
                *flag = 0;
            } else {
                m = ajusta_dir(m);
                *flag = 0;
                
            }
        }
    }
    
    return m;
}


Mapa* ajusta_dir(Mapa* m) {
    Mapa *t = NULL;
    if (m->dir->bf == 1) {
        t = rotacao_esq(m);
    } else if (m->dir->bf == -1) {
        m->dir = rotacao_dir(m->dir);
        t = rotacao_esq(m);
    }
    return t;
}

Mapa* ajusta_esq(Mapa* m) {
    Mapa* t = NULL;
    if (m->esq->bf == -1) {
        t= rotacao_dir(m);
    } else if (m->esq->bf == 1) {
        m->esq = rotacao_esq(m->esq);
        t = rotacao_dir(m);
    }
    return t;
}

Mapa* rotacao_dir(Mapa* m) {
    Mapa* t = m->esq, *r = t->dir;
    if (r != NULL) {
        m->esq = r;
    } else {
        m->esq = NULL;
    }
    t->dir = m;
    t->bf = m->bf = 0;
    return t;
}


Mapa* rotacao_esq(Mapa* m) {
    Mapa* t = m->dir, *r = t->esq;
    if (r != NULL) {
        m->dir = r;
    } else {
       m->dir = NULL;
    }

    t->esq = m;
    t->bf = m->bf = 0;
    return t;
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

Mapa* removeMapa (Mapa* m, int chave) {
    int flag = 0;
    
    return remove2(m, chave, &flag);
}


Mapa* remove2 (Mapa *m, int chave, int *flag){
    if (m == NULL) {
        return m;
    }
    if (chave < m->chave) {
        m->esq = remove2(m->esq, chave, flag);
        
        if (*flag) {
            if (m->bf == 0) {
                m->bf = 1;
                *flag = 1;
            }
            else if (m->bf == -1) {
                m->bf = 0;
                *flag = 0;
            }
            else {
                m->bf = 2;
                m = ajusta_dir(m);
                m->bf = 1;
                *flag = 0;
            }
        }
    }
    else if (chave > m->chave) {
        m->dir = remove2(m->dir, chave, flag);
        
        if (*flag) {
            if (m->bf == 0) {
                m->bf = -1;
                *flag = 1;
            }
            else if (m->bf == 1) {
                m->bf = 0;
                *flag = 0;
            }
            else {
                m->bf = -2;
                m = ajusta_esq(m);
                m->bf = -1;
                *flag = 0;
            }
        }
    }
    else {
        if (m->esq == NULL && m->dir == NULL) /* nó sem filhos */
        {
            free (m);
            m = NULL;
            *flag = 1;
            
        }
        else if (m->esq == NULL) /* nó só tem filho à direita */
        {
            Mapa* t = m;
            m = m->dir;
            free (t);
            
            *flag = 1;
        }
        else if (m->dir == NULL) /* só tem filho à esquerda */
        {
            Mapa* t = m; 
            m = m->esq; 
            free (t);
            
            *flag = 1;
            
        }
        else {/* nó tem os dois filhos: busca o sucessor */
            // o sucessor é o menor nó da subárvore da direita
            Mapa* sucessor = m->dir;
            
            while (sucessor->esq != NULL) {
                sucessor = sucessor->esq;
            }
            
            *flag = 0;

            m->chave = sucessor->chave;
            m->dado = sucessor->dado;
            
            m->dir = remove2(sucessor, sucessor->chave, flag);
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


void debug_mostra_mapa(Mapa* m) {
    if (m != NULL) {
        printf("%d ", m->chave);
        debug_mostra_mapa(m->esq);
        debug_mostra_mapa(m->dir);
    }
}




