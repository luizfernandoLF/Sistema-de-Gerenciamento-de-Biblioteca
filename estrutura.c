#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

Lista* criaLista() {
    Lista* l = malloc(sizeof(Lista));
    l->prim = l->ult = NULL;
    l->tamanho = 0;
    return l;
}

void destruirLista(Lista* l) {
    Livro* at = l->prim;

    while (at != NULL) {
        Livro* prox = at->prox;
        free(at);
        at = prox;
    }
    free(l);
}
