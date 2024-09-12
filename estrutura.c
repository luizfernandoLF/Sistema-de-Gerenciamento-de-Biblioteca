#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <estrutura.h>

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


/// @brief Cria um tipo livro
/// @param titulo 
/// @param autor 
/// @param ISBN 
/// @param anoPublicacao 
/// @return um tipo Livro
Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao) {
    Livro* l = malloc(sizeof(Livro));
    strcpy(l->titulo, titulo);
    strcpy(l->autor, autor);
    strcpy(l->ISBN, ISBN);
    strcpy(l->anoPublicacao, anoPublicacao);
    l->status = true;  // Quando o Livro está disponível, status = true
    l->prox = NULL;
    return l;
}

/// @brief Cria uma lista de livros
/// @return lista vazia
Lista* criaLista(){
    Lista* l = malloc(sizeof(Lista));
    l->prim = l->ult = NULL;
    l->tamanho = 0;
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

/// @brief Busca um livro a partir do seu ISBN
/// @param l
/// @param ISBN
/// @return o livro procurado, caso seu ISBN esteja na lista, e NULL caso não esteja
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
livro* buscarLivro(lista* l, char* busca) {
    if (l->prim == NULL) {
        printf("Lista vazia :/ \n");
        return NULL;
    }

    livro* at = l->prim;

    bool buscaEhISBN = isISBN(busca);  // Verifica se a busca é por ISBN

    // Percorre a lista para procurar o livro correspondente
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


/// @brief Efetua ação de empréstimo de livro e muda seu status de disponibilidade para falso
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

/// @brief Efetua ação de devolução de livro e muda seu status de disponibilidade para verdadeiro
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

/// @brief Altera informações de um livro
/// @param l 
/// @param ISBN 
void alterarLivro(Lista* l, char* ISBN) {

    Livro* lv = buscaISBN(l, ISBN);

    if (lv == NULL) {
        printf("Livro com ISBN %s nao encontrado.\n", ISBN);
        return;
    }

    //mostra as infos atuais do Livro antes da troca
    printf("Livro encontrado. Informacoes atuais:\n");
    printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
           lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
           lv->status ? "Disponivel" : "Emprestado");

    char novoTitulo[100];
    char novoAutor[40];
    int novoAnoPublicacao;

    //muda o titulo
    printf("\nDigite o novo titulo ou pressione Enter para manter o atual: ");
    fgets(novoTitulo, sizeof(novoTitulo), stdin);
    if (strcmp(novoTitulo, "\n") != 0) {  // caso o usuario digite algo
        novoTitulo[strcspn(novoTitulo, "\n")] = 0;
        strcpy(lv->titulo, novoTitulo);  // Alterar o título
    }

    //muda o autor
    printf("Digite o novo autor ou pressione Enter para manter o atual: ");
    fgets(novoAutor, sizeof(novoAutor), stdin);
    if (strcmp(novoAutor, "\n") != 0) { 
        novoAutor[strcspn(novoAutor, "\n")] = 0;
        strcpy(lv->autor, novoAutor);
    }

    //muda o ano de publicacao
    printf("Digite o novo ano de publicacao ou pressione 0 para manter o atual: ");
    scanf("%d", &novoAnoPublicacao);
    if (novoAnoPublicacao != 0) {
        sprintf(lv->anoPublicacao, "%d", novoAnoPublicacao);  // Converte o ano para string 
    }

    //imprime as infos depois da troca
    printf("\nAs informacoes do Livro foram atualizadas com sucesso!\n");
    printf("Novas informacoes:\n");
    printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
           lv->titulo, lv->autor, lv->ISBN, lv->anoPublicacao, 
           lv->status ? "Disponivel" : "Emprestado");
}



void destruirLista (Lista* l){
    Livro* at = l->prim;

    while (at != NULL){
        Livro* prox = at->prox;
        free(at);
        at = prox;
    }
    free(l);
}

void exibirLivros(Lista* l){
    if (l->prim == NULL){
        printf("Lista vazia :( \n");
    }
    
    Livro* at = l->prim;

    while(at!=NULL){
        printf("Titulo: %s\nAutor: %s\nISBN: %s\nAno de publicacao: %s\nStatus: %s\n", 
               at->titulo, at->autor, at->ISBN, at->anoPublicacao, 
               at->status ? "Disponivel" : "Emprestado");
        at = at->prox;
    }
}

