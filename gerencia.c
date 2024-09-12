#include <stdio.h>
#include <stdlib.h>
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
    char divisor[100] = "\n*****************************************************\n";
    Lista* lista = criaLista();
    char busca[100];
    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISBN[50];
    char ano[6];

    // Lendo e processando o arquivo
    while (fscanf(infile, "%s", CMD) != EOF) {
        fprintf(outfile, divisor);
        if(strcmp(CMD, "ADD") == 0) {
            if (fscanf(infile, " %[^;];", ISBN) == 1 &&
                fscanf(infile, " %[^;];", titulo) == 1 &&
                fscanf(infile, " %[^;];", autor) == 1 &&
                fscanf(infile, " %s", ano) == 1) {
                //fprintf(outfile, divisor);
                adicionarLivro(outfile, lista, titulo, autor, ISBN, ano);
            } else {
                //fprintf(outfile, divisor);
                fprintf(outfile, "Erro ao ler as informações do livro!\n\n");
            }
        } else if (strcmp(CMD, "SEARCH") == 0) {
            //fprintf(outfile, divisor);
            fprintf(outfile, "Buscando livro...\n");
            if (fscanf(infile, " %[^;];", busca) == 1) {
                if (buscarLivro(outfile, lista, busca) != NULL) {
                    fprintf(outfile, "Livro encontrado!\n");
                    exibir1Livro(outfile, buscarLivro(outfile, lista, busca));
                }
            } else {
                fprintf(outfile, "Erro ao ler as informações de busca do livro!\n\n");
            }
        } else if (strcmp(CMD, "CHECK_OUT") == 0) {
            if (fscanf(infile, " %[^;];", busca) == 1) {
                //fprintf(outfile, divisor);
                checkout(outfile, lista, busca);
            } else {
                //fprintf(outfile, divisor);
                fprintf(outfile, "Erro ao fazer a retirada do livro!\n\n");
            }
        } else if (strcmp(CMD, "CHECK_IN") == 0) {
            if (fscanf(infile, " %[^;];", busca) == 1) {
                checkin(outfile, lista, busca);
            } else {
                fprintf(outfile, "Erro ao fazer a devolução do livro!\n\n");
            }
        }
    }

    // Fechando os arquivos
    fclose(infile);
    fclose(outfile);

    return 0;
}
