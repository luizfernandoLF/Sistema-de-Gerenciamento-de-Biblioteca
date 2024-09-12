typedef struct Livro {
    char titulo[100];
    char autor[40];
    char ISBN[50];  
    char anoPublicacao[6];
    bool status;  
    struct Livro* prox;
} Livro;
typedef struct Lista {
    Livro* prim;
    Livro* ult;
    int tamanho;
} Lista;
Livro* criaLivro(char* titulo, char* autor, char* ISBN, char* anoPublicacao);
Livro* criaLista();
void adicionarLivro(Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao);
Livro* buscaISBN(Lista* l, char* ISBN);
Livro* buscaAutor(Lista* l, char* autor);
Livro* buscaTitulo(Lista* l, char* titulo);
int checkout(Lista* l, char* ISBN);
int checkin(Lista* l, char* ISBN);
void alterarLivro(Lista* l, char* ISBN);
void destruirLista(Lista* l);
void exibirLivros(Lista* l);
