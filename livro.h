
#include <stdbool.h>
#include "estrutura.h"


Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao);
void adicionarLivro(Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao);
bool isISBN(char* input);
Livro* buscarLivro(Lista* l, char* busca);
bool validarISBN(char* ISBN);
int checkout(Lista* l, char* ISBN);
int checkin(Lista* l, char* ISBN);
// void exibirLivros(Lista* l);
void exibir1Livro(Livro* l);
