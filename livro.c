#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include <stdbool.h>
#include "estrutura.h"

/// @brief Cria um tipo Livro
/// @param titulo 
/// @param autor 
/// @param ISBN 
/// @param anoPublicacao 
/// @return um tipo Livro
Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
    if (!validarISBN(ISBN)){
        printf("ISBN invalido, Livro nao criado\n");
        return NULL;
    }
    
    Livro* l = malloc(sizeof(Livro));
    strcpy(l->titulo, titulo);
    strcpy(l->autor, autor);
    strcpy(l->ISBN, ISBN);
    strcpy(l->anoPublicacao, anoPublicacao);
    l->status = true;  // Quando o Livro está disponível, status = true
    l->prox = NULL;
    return l;
}

/// @brief Insere os Livros no final da Lista
/// @param l
/// @param titulo
/// @param autor
/// @param ISBN
/// @param anoPublicacao
/// @return 
void adicionarLivro(Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
    Livro* nl = criaLivro(titulo, autor, ISBN, anoPublicacao);
    
    if (l->prim == NULL) {  // Quando a Lista está vazia
        l->prim = l->ult = nl;  // Apenas um elemento
    } else {
        l->ult->prox = nl;  // Insere no final
        l->ult = nl;
    }
    l->tamanho++;
}

/// @brief Busca um Livro a partir do seu ISBN
/// @param l
/// @param ISBN
/// @return o Livro procurado, caso seu ISBN esteja na Lista, e NULL caso não esteja
bool isISBN(char* input) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return false;  //se tiver alguma [i] que não seja numérico não é ISBN
        }
    }
    return true;
}

// Função de busca unificada (ISBN, título ou autor)
Livro* buscarLivro(Lista* l, char* busca) {
    if (l->prim == NULL) {
        printf("Lista vazia :/ \n");
        return NULL;
    }

    Livro* at = l->prim;

    bool buscaEhISBN = isISBN(busca);  // Verifica se a busca é por ISBN

    // Percorre a Lista para procurar o Livro correspondente
    while (at != NULL) {
        if (buscaEhISBN) {
            // Se for ISBN, compara o ISBN
            if (strcmp(at->ISBN, busca) == 0) {
                printf("Livro encontrado por ISBN:\n");
                printf("Título: %s\nAutor: %s\nISBN: %s\nAno de publicação: %s\nStatus: %s\n", 
                       at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
                       at->status ? "Disponível" : "Emprestado");
                return at;
            }
        } else {
            // Caso não seja ISBN, compara tanto título quanto autor
            if (strcmp(at->titulo, busca) == 0 || strcmp(at->autor, busca) == 0) {
                printf("Livro encontrado por Título ou Autor:\n");
                printf("Título: %s\nAutor: %s\nISBN: %s\nAno de publicação: %s\nStatus: %s\n", 
                       at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
                       at->status ? "Disponível" : "Emprestado");
                return at;
            }
        }
        at = at->prox;
    }

    printf("Livro não encontrado.\n");
    return NULL;
}

bool validarISBN(char* ISBN) {
    if (strlen(ISBN) == 0) {
        printf("Campo ISBN vazio.\n");
        return false;
    }
    return true;
}

/// @brief Efetua ação de empréstimo de Livro e muda seu status de disponibilidade para falso
/// @param l 
/// @param ISBN 
/// @return 1 caso o empréstimo seja efetuado, e 0 caso não.
int checkout(Lista* l, char* ISBN) { 
    Livro* lv = buscaISBN(l, ISBN);
    if (lv != NULL) {
        if (lv->status == true) {
            lv->status = false;  // Marca como emprestado
            printf("Livro com ISBN %s emprestado com sucesso!\n", ISBN);
            return 1;
        } else {
            printf("Livro com ISBN %s ja esta emprestado.\n", ISBN);
            return 0;
        }
    }
    return 0;
}

/// @brief Efetua ação de devolução de Livro e muda seu status de disponibilidade para verdadeiro
/// @param l 
/// @param ISBN 
/// @return 1 caso a devolução seja efetuada, e 0 caso não.
int checkin(Lista* l, char* ISBN) {
    Livro* lv = buscaISBN(l, ISBN);
    if (lv != NULL) {
        if (lv->status == false) {
            lv->status = true;  // Marca como disponível
            printf("Livro com ISBN %s devolvido com sucesso!\n", ISBN);
            return 1;
        } else {
            printf("Livro com ISBN %s já está disponível.\n", ISBN);
            return 0;
        }
    }
    return 0;
}


// void exibirLivros(Lista* l){
//     if (l->prim == NULL){
//         printf("Lista vazia :( \n");
//         return;
//     }
    
//     Livro* at = l->prim;

//     while(at!=NULL){
//         printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
//                at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
//                at->status ? "Disponivel" : "Emprestado");
//         at = at->prox;
//     }
// }

void exibir1Livro(Livro* l){
    if (l==NULL){
        printf("Livro nao encontado\n");
        return;
    }
    printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
        l->titulo, l->autor, l->ISBN, l->anoPublicacao, 
        l->status ? "Disponivel" : "Emprestado");
    
}
