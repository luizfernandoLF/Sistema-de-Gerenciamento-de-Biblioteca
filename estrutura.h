#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdbool.h>

typedef struct Livro { 
    char titulo[100];
    char autor[40];
    char ISBN[50];  
    char anoPublicacao[6];
    bool status;  
    struct Livro* prox;
} Livro;

typedef struct Lista {
    Livro* prim;
    Livro* ult;
    int tamanho;
} Lista;

Lista* criaLista();
void destruirLista(Lista* l);

#endif
