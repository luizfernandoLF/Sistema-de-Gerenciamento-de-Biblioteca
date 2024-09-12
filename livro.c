#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Livro.h"
#include <stdbool.h>
#include "estrutura.h"

bool validarISBN(char* ISBN) {
    if (strlen(ISBN) == 0) {
        printf("Campo ISBN vazio.\n");
        return false;
    }

    // //verifica se o ISBN tem só números
    // for (int i = 0; i < strlen(ISBN); i++) {
    //     if (ISBN[i] < '0' || ISBN[i] > '9') {
    //         printf("ISBN invalido. So pode conter numeros\n");
    //         return false;
    //     }
    // }
    
    return true;
}


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

void alterarLivro(Livro* lv) {
    if (lv == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }

    // Exibe as informações atuais do Livro antes da alteração
    printf("Livro encontrado. Informacoes atuais:\n");
    printf("Título: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
           lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
           lv->status ? "Disponivel" : "Emprestado");

    char novoTitulo[100];
    char novoAutor[40];
    int novoAnoPublicacao;

    //alteração do título
    printf("\nDigite o novo titulo ou pressione Enter para manter o atual: ");
    fgets(novoTitulo, sizeof(novoTitulo), stdin);
    if (strcmp(novoTitulo, "\n") != 0) {
        novoTitulo[strcspn(novoTitulo, "\n")] = 0;
        strcpy(lv->titulo, novoTitulo);
    }

    //alteração do autor
    printf("Digite o novo autor ou pressione Enter para manter o atual: ");
    fgets(novoAutor, sizeof(novoAutor), stdin);
    if (strcmp(novoAutor, "\n") != 0) {
        novoAutor[strcspn(novoAutor, "\n")] = 0;
        strcpy(lv->autor, novoAutor);
    }

    //alteração do ano de publicação
    printf("Digite o novo ano de publicação ou pressione 0 para manter o atual: ");
    scanf("%d", &novoAnoPublicacao);
    if (novoAnoPublicacao != 0) {
        sprintf(lv->anoPublicacao, "%d", novoAnoPublicacao);  
    }

    //exibe as novas informações do Livro
    printf("\nAs informações do Livro foram atualizadas com sucesso!\n");
    printf("Novas informações:\n");
    printf("Título: %s\nAutor: %s\nISBN: %s\nAno de publicação: %s\nStatus: %s\n", 
           lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
           lv->status ? "Disponível" : "Emprestado");
}


void exibirLivros(Lista* l){
    if (l->prim == NULL){
        printf("Lista vazia :( \n");
        return;
    }
    
    Livro* at = l->prim;

    while(at!=NULL){
        printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
               at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
               at->status ? "Disponivel" : "Emprestado");
        at = at->prox;
    }
}

void exibir1Livro(Livro* l){
    if (l==NULL){
        printf("Livro nao encontado\n");
        return;
    }
    printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
        l->titulo, l->autor, l->ISBN, l->anoPublicacao, 
        l->status ? "Disponivel" : "Emprestado");
    
}
