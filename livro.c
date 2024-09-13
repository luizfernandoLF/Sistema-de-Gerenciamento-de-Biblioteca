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
    Livro* novoLivro = criaLivro(titulo, autor, ISBN, anoPublicacao);
    
    if (novoLivro == NULL) {
        fprintf(output, "Erro: Não foi possível criar o livro.\n");
        return;
    }

    if (l->prim == NULL) {
        l->prim = l->ult = novoLivro;
    } else {
        l->ult->prox = novoLivro;
        l->ult = novoLivro;
    }
    l->tamanho++;

    // Mensagem de saída formatada
    fprintf(output, "\n*****************************************************\n");
    fprintf(output, "Livro adicionado com êxito!\n");
    fprintf(output, "Dados do livro:\n");
    fprintf(output, "Título: %s\n", titulo);
    fprintf(output, "Autor: %s\n", autor);
    fprintf(output, "ISBN: %s\n", ISBN);
    fprintf(output, "Ano de publicação: %s\n", anoPublicacao);
    fprintf(output, "Status de disponibilidade: Disponível\n");
    fprintf(output, "*****************************************************\n\n");
}


Livro* buscarLivro(FILE* output, Lista* l, char* busca) {
    Livro* at = l->prim;
    while (at != NULL) {
        if (strcmp(at->ISBN, busca) == 0 || strcmp(at->titulo, busca) == 0 || strcmp(at->autor, busca) == 0) {
            // Livro encontrado
            fprintf(output, "\n*****************************************************\n");
            fprintf(output, "Livro encontrado:\n");
            fprintf(output, "Título: %s\n", at->titulo);
            fprintf(output, "Autor: %s\n", at->autor);
            fprintf(output, "ISBN: %s\n", at->ISBN);
            fprintf(output, "Ano de publicação: %s\n", at->anoPublicacao);
            fprintf(output, "Status de disponibilidade: %s\n", at->status ? "Disponível" : "Emprestado");
            fprintf(output, "*****************************************************\n\n");
            return at;
        }
        at = at->prox;
    }

    // Caso o livro não seja encontrado
    fprintf(output, "\n*****************************************************\n");
    fprintf(output, "Livro com identificador '%s' não encontrado!\n", busca);
    fprintf(output, "*****************************************************\n\n");
    return NULL;
}


int checkout(FILE* output, Lista* l, char* ISBN) {
    Livro* lv = buscarLivro(output, l, ISBN);  

    if (lv == NULL) {
        // Livro não encontrado
        // fprintf(output, "\n*****************************************************\n");
        fprintf(output, "Erro: O livro com ISBN %s não foi encontrado no sistema.\n", ISBN);
        fprintf(output, "*****************************************************\n\n");
        return 0;
    }

    if (lv->status == true) {
        // Se o livro está disponível para empréstimo
        lv->status = false;
        fprintf(output, "\n*****************************************************\n");
        fprintf(output, "Livro retirado para empréstimo com sucesso!\n");
        fprintf(output, "Dados do livro:\n");
        fprintf(output, "Título: %s\n", lv->titulo);
        fprintf(output, "Autor: %s\n", lv->autor);
        fprintf(output, "ISBN: %s\n", lv->ISBN);
        fprintf(output, "Ano de publicação: %s\n", lv->anoPublicacao);
        fprintf(output, "Status de disponibilidade: Emprestado\n");
        fprintf(output, "*****************************************************\n\n");
        return 1;
    } else {
        // Se o livro já está emprestado
        fprintf(output, "\n*****************************************************\n");
        fprintf(output, "Livro com ISBN %s já está emprestado!\n", ISBN);
        fprintf(output, "*****************************************************\n\n");
        return 0;
    }
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
    if (l == NULL) {
        fprintf(output, "\n*****************************************************\n");
        fprintf(output, "Erro: Livro não encontrado.\n");
        fprintf(output, "*****************************************************\n\n");
        return;
    }
    fprintf(output, "\n*****************************************************\n");
    fprintf(output, "Dados do livro:\n");
    fprintf(output, "Título: %s\n", l->titulo);
    fprintf(output, "Autor: %s\n", l->autor);
    fprintf(output, "ISBN: %s\n", l->ISBN);
    fprintf(output, "Ano de publicação: %s\n", l->anoPublicacao);
    fprintf(output, "Status de disponibilidade: %s\n", l->status ? "Disponível" : "Emprestado");
    fprintf(output, "*****************************************************\n\n");
}
