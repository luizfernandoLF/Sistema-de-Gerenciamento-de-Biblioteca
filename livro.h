#ifndef LIVRO_H
#define LIVRO_H

#include "estrutura.h"

Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao);
void adicionarLivro(FILE* saida, Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao);
Livro* buscarLivro(FILE* output, Lista* l, char* busca);
int checkout(Lista* l, char* ISBN);
int checkin(Lista* l, char* ISBN);
void exibir1Livro(FILE* output, Livro* l);

#endif
