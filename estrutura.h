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
Lista* criaLista();
void adicionarLivro(Lista* l, char* titulo, char* autor, char* ISBN, char* anoPublicacao);
bool isISBN(char* input);
Livro* buscarLivro(Lista* l, char* busca);
int checkout(Lista* l, char* ISBN);
int checkin(Lista* l, char* ISBN);
//void alterarLivro(Lista* l, char* ISBN);
void destruirLista(Lista* l);
void exibirLivros(Lista* l);
