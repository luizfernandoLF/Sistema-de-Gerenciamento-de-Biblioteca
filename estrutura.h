#include <stdbool.h>

typedef struct Livro { // nó
    char titulo[100];
    char autor[40];
    char ISBN[50];  
    char anoPublicacao[6];
    bool status;  // true = disponível, false = emprestado
    struct Livro* prox;
} Livro;


typedef struct Lista {
    Livro* prim;
    Livro* ult;
    int tamanho;
} Lista;


Lista* criaLista();
void destruirLista(Lista* l);
// void exibirLivros(Lista* l);
