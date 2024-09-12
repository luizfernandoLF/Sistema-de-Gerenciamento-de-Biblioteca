#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "livro.h"

Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
    Livro* l = malloc(sizeof(Livro));
    strcpy(l->titulo, titulo);
    strcpy(l->autor, autor);
    strcpy(l->ISBN, ISBN);
    strcpy(l->anoPublicacao, anoPublicacao);
    l->status = true;
    l->prox = NULL;
    return l;
}

void adicionarLivro(FILE* output, Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
    Livro* novo = criaLivro(titulo, autor, ISBN, anoPublicacao);

    if (l->prim == NULL) {
        l->prim = l->ult = novo;
    } else {
        l->ult->prox = novo;
        l->ult = novo;
    }
    l->tamanho++;

    fprintf(output, "Livro adicionado com exito! Dados do livro:\n"
            "Titulo: %s\n"
            "Autor: %s\n"
            "ISBN:%s\n"
            "Ano de publicacao: %s\n"
            "Status de disponibilidade: %s\n\n\n",
            novo->titulo, novo->autor, novo->ISBN, novo->anoPublicacao,
            novo->status ? "Disponivel" : "Indisponivel");
}

Livro* buscarLivro(FILE* output, Lista* l, char* busca) {
    Livro* at = l->prim;
    while (at != NULL) {
        if (strcmp(at->ISBN, busca) == 0 || strcmp(at->titulo, busca) == 0 || strcmp(at->autor, busca) == 0) {
            exibir1Livro(output, at);
            return at;
        }
        at = at->prox;
    }
    return NULL;
}

int checkout(Lista* l, char* ISBN) {
    Livro* lv = buscarLivro(l, ISBN);
    if (lv != NULL && lv->status == true) {
        lv->status = false;
        return 1;
    }
    return 0;
}

int checkin(Lista* l, char* ISBN) {
    Livro* lv = buscarLivro(l, ISBN);
    if (lv != NULL && lv->status == false) {
        lv->status = true;
        return 1;
    }
    return 0;
}

void exibir1Livro(FILE* output, Livro* l) {
    if (l != NULL) {
        printf(
            "Dados do livro:\n"
            "Titulo: %s\n"
            "Autor: %s\n"
            "ISBN: %s\n"
            "Ano de publicacao: %s\n"
            "Status de disponibilidade: %s\n\n\n",
            l->titulo, l->autor, l->ISBN, l->anoPublicacao,
            l->status ? "Disponivel" : "Indisponivel");
    } else {
        printf("Livro não encontrado.\n\n\n");
    }
}
