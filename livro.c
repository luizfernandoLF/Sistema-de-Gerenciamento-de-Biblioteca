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

    fprintf(output, "Livro adicionado com êxito!\nDados do livro:\n"
            "Título: %s\n"
            "Autor: %s\n"
            "ISBN: %s\n"
            "Ano de publicação: %s\n"
            "Status de disponibilidade: %s\n\n",
            novo->titulo, novo->autor, novo->ISBN, novo->anoPublicacao,
            novo->status ? "Disponível" : "Indisponível");
}

Livro* buscarLivro(FILE* output, Lista* l, char* busca) {
    Livro* at = l->prim;
    while (at != NULL) {
        if (strcmp(at->ISBN, busca) == 0 || strcmp(at->titulo, busca) == 0 || strcmp(at->autor, busca) == 0) {
            //fprintf(output, "Busca com sucesso!\n");
            //exibir1Livro(output, at);
            return at;
        }
        at = at->prox;
    }

    fprintf(output, "Livro não encontrado!\n\n");
    return NULL;
}

int checkout(FILE* output, Lista* l, char* ISBN) {
    Livro* lv = buscarLivro(output, l, ISBN);
    if (lv != NULL && lv->status == true) {
        lv->status = false;
        fprintf(output, "Livro retirado para empréstimo com sucesso!\n");
        exibir1Livro(output, lv);
        return 1;
    } else if (lv->status == false) {
        fprintf(output, "Livro indisponível para empréstimo!\n");
        return 0;
    }
    fprintf(output, "Erro ao fazer a retirada do livro!\n\n");
    return 0;
}

int checkin(FILE* output, Lista* l, char* ISBN) {
    Livro* lv = buscarLivro(output, l, ISBN);
    if (lv != NULL && lv->status == false) {
        lv->status = true;
        fprintf(output, "Livro devolvido com sucesso!\n");
        exibir1Livro(output, lv);
        return 1;
    }
    fprintf(output, "Erro ao fazer a devolução do livro!\n\n");
    return 0;
}

void exibir1Livro(FILE* output, Livro* l) {
    if (l != NULL) {
        fprintf(output,
            "Dados do livro:\n"
            "Titulo: %s\n"
            "Autor: %s\n"
            "ISBN: %s\n"
            "Ano de publicacao: %s\n"
            "Status de disponibilidade: %s\n\n\n",
            l->titulo, l->autor, l->ISBN, l->anoPublicacao,
            l->status ? "Disponivel" : "Indisponivel");
    } else {
        fprintf(output, "Livro não encontrado.\n\n\n");
    }
}
