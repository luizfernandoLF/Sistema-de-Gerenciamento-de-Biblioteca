#include <stdbool.h>

// typedef struct Livro {
//     char titulo[100];
//     char autor[40];
//     char ISBN[50];
//     char anoPublicacao[6];
//     bool status;
//     struct Livro* prox;
// } livro;

// typedef struct lista {
//     livro* prim;
//     livro* ult;
//     int tamanho;
// } lista;


Livro* crialivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao);
void alterarLivro(Livro* lv);
void exibir1Livro(Livro* lv);
bool validarISBN(char* ISBN);
