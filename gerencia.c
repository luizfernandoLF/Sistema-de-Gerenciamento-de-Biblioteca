#include <stdio.h>
#include <string.h>
#include "livro.h"

int main(int argc, char *argv[]) {
    // Verificar se os arquivos foram passados como argumentos
    if (argc != 3) {
        printf("Entradas incorretas: Eh necessario um arquivo de entrada"
                " e um de saida!");
        return 1;
    }

    // Abrindo os arquivos de entrada e saída passados por argumento
    FILE* infile = fopen(argv[1], "r");
    FILE* outfile = fopen(argv[2], "w");

    if (infile == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        fclose(infile);
        return 1;
    }
    if (outfile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(outfile);
        return 1;
    }

    // Variáveis para armazenar os dados lidos
    Lista* lista = criaLista();
    char busca[100];
    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISBN[50];
    char ano[6];
    char separador[4];

    // Lendo e processando o arquivo
    while (fscanf(infile, "%s", CMD) != EOF) {
        if(strcmp(CMD, "ADD") == 0) {
            if (fscanf(infile, " %[^;];", ISBN) == 1 &&
                fscanf(infile, " %[^;];", titulo) == 1 &&
                fscanf(infile, " %[^;];", autor) == 1 &&
                fscanf(infile, " %s", ano) == 1) {
                adicionarLivro(outfile, lista, titulo, autor, ISBN, ano);
            } else {
                fprintf(outfile, "Erro ao ler as informações do livro!\n\n");
            }
            //adicionarLivro(outfile, lista, titulo, autor, ISBN, ano);
        } else if (strcmp(CMD, "SEARCH") == 0) {
            if (fscanf(infile, " %[^;];", busca) == 1) {
                buscarLivro(outfile, lista, busca);
            } else {
                fprintf(outfile, "Erro ao ler as informações de busca do livro!\n\n");
            }
        }
        // } else if (strcmp(CMD, "CHECK_OUT") == 0) {

        // } else if (strcmp(CMD, "CHECK_IN") == 0) {

        // } else {
        //     printf("Comando não encontrado!");
        // }
        // Escrevendo no arquivo de saída
        //fprintf(outfile, "%s|%s|%s|%s|%s\n", CMD, ISBN, titulo, autor, ano);
    }

    // Fechando os arquivos
    fclose(infile);
    fclose(outfile);

    return 0;
}
