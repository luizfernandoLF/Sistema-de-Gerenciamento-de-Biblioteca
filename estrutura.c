#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estrutura.h"

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


// /// @brief Cria um tipo Livro
// /// @param titulo 
// /// @param autor 
// /// @param ISBN 
// /// @param anoPublicacao 
// /// @return um tipo Livro
// Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
//     Livro* l = malloc(sizeof(Livro));
//     strcpy(l->titulo, titulo);
//     strcpy(l->autor, autor);
//     strcpy(l->ISBN, ISBN);
//     strcpy(l->anoPublicacao, anoPublicacao);
//     l->status = true;  // Quando o Livro está disponível, status = true
//     l->prox = NULL;
//     return l;
// }

/// @brief Cria uma Lista de Livros
/// @return Lista vazia
Lista* criaLista(){
    Lista* l = malloc(sizeof(Lista));
    l->prim = l->ult = NULL;
    l->tamanho = 0;
    return l;
}



// /// @brief 
// /// @param l 
// /// @param ISBN 
// /// @return 
// int removerLivroISBN(Lista* l, char* ISBN) {  // ISBN como string
//     if (l->prim == NULL) {
//         printf("Lista vazia\n");
//         return 0;
//     }

//     Livro* at = l->prim;
//     Livro* ant = NULL;

//     // Percorre a Lista até encontrar o Livro ou chegar ao final
//     while (at != NULL && strcmp(at->ISBN, ISBN) != 0) {
//         ant = at;
//         at = at->prox;
//     }

//     if (at == NULL) {  
//         printf("Livro com ISBN %s nao encontrado.\n", ISBN);
//         return 0;
//     }

//     // aqui remove
//     if (at == l->prim) {
//         l->prim = at->prox;
//         if (l->prim == NULL) {
//             l->ult = NULL;
//         }
//     } else {
//         ant->prox = at->prox;
//         if (at == l->ult) {
//             l->ult = ant;
//         }
//     }

//     free(at);
//     l->tamanho--;
//     return 1;
// }




// /// @brief Altera informações de um Livro
// /// @param l 
// /// @param ISBN 
// void alterarLivro(Lista* l, char* ISBN) {

//     Livro* lv = buscaISBN(l, ISBN);

//     if (lv == NULL) {
//         printf("Livro com ISBN %s nao encontrado.\n", ISBN);
//         return;
//     }

//     //mostra as infos atuais do Livro antes da troca
//     printf("Livro encontrado. Informacoes atuais:\n");
//     printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
//            lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
//            lv->status ? "Disponivel" : "Emprestado");

//     char novoTitulo[100];
//     char novoAutor[40];
//     int novoAnoPublicacao;

//     //muda o titulo
//     printf("\nDigite o novo titulo ou pressione Enter para manter o atual: ");
//     fgets(novoTitulo, sizeof(novoTitulo), stdin);
//     if (strcmp(novoTitulo, "\n") != 0) {  // caso o usuario digite algo
//         novoTitulo[strcspn(novoTitulo, "\n")] = 0;
//         strcpy(lv->titulo, novoTitulo);  // Alterar o título
//     }

//     //muda o autor
//     printf("Digite o novo autor ou pressione Enter para manter o atual: ");
//     fgets(novoAutor, sizeof(novoAutor), stdin);
//     if (strcmp(novoAutor, "\n") != 0) { 
//         novoAutor[strcspn(novoAutor, "\n")] = 0;
//         strcpy(lv->autor, novoAutor);
//     }

//     //muda o ano de publicacao
//     printf("Digite o novo ano de publicacao ou pressione 0 para manter o atual: ");
//     scanf("%d", &novoAnoPublicacao);
//     if (novoAnoPublicacao != 0) {
//         sprintf(lv->anoPublicacao, "%d", novoAnoPublicacao);  // Converte o ano para string 
//     }

//     //imprime as infos depois da troca
//     printf("\nAs informacoes do Livro foram atualizadas com sucesso!\n");
//     printf("Novas informacoes:\n");
//     printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
//            lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
//            lv->status ? "Disponivel" : "Emprestado");
// }



void destruirLista (Lista* l){
    Livro* at = l->prim;

    while (at != NULL){
        Livro* prox = at->prox;
        free(at);
        at = prox;
    }
    free(l);
}

// void exibirLivros(Lista* l){
//     if (l->prim == NULL){
//         printf("Lista vazia :( \n");
//     }
    
//     Livro* at = l->prim;

//     while(at!=NULL){
//         printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
//                at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
//                at->status ? "Disponivel" : "Emprestado");
//         at = at->prox;
//     }
// }
