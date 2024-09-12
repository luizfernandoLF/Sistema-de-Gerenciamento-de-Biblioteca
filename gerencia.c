#include <stdio.h>

int main(int argc, char *argv[]) {
    // Verificar se os arquivos foram passados como argumentos
    if (argc != 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    // Abrindo os arquivos de entrada e saída passados por argumento
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");

    if (infile == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }
    if (outfile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(infile);
        return 1;
    }

    // Variáveis para armazenar os dados lidos
    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISBN[50];
    char ano[6];
    char separador[4];

    // Lendo e processando o arquivo
    while (fscanf(infile, "%s %[^;]; %[^;]; %[^;]; %s", CMD, ISBN, titulo, autor, ano) != EOF) {
        // Escrevendo no arquivo de saída
        fprintf(outfile, "%s|%s|%s|%s|%s\n", CMD, ISBN, titulo, autor, ano);
    }

    // Fechando os arquivos
    fclose(infile);
    fclose(outfile);

    return 0;
}
