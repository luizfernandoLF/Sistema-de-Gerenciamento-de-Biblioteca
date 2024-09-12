#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "livro.h"

int main(int argc, char* argv[]) {
    // Abrindo os arquivos de entrada e saída
    FILE* infile = fopen(arg[1], "r");
    FILE* outfile = fopen(arg[2], "w");

    if (infile == NULL || outfile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISBN[50];
    char ano[6];
    char separador[4];

    // Processando cada linha do arquivo de entrada
    while (fscanf(infile, "%s %[^;]; %[^;]; %[^;]; %s", CMD, ISBN, titulo, autor, ano) != EOF) {
        // Escrevendo no arquivo de saída
        fprintf(outfile, "%s|%s|%s|%s|%s\n", CMD, ISBN, titulo, autor, ano);
    }

    // Fechando os arquivos
    fclose(infile);
    fclose(outfile);

    return 0;
}
