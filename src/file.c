#include <stdio.h>
#include <string.h>
#include "file.h"

FILE *entrada, *saida;

// Função para abertura do arquivo de entrada para leitura, e de saída para escrita.
void abre_arquivo(char argv[]) {

    // Cria uma variável para armazenar o nome do arquivo de entrada dado, depois copia o nome para essa variável e concatena o '.out'.
    char outputName[100];
    strcpy(outputName, argv);
    strcat(outputName, ".out");

    entrada = fopen(argv, "r");
    saida = fopen(outputName, "w");

    // Se o arquivo de entrada estiver vazio retorna erro.
    if (entrada == NULL) {
        printf("Falha na abertura do arquivo.\n");
    }
}

//Função para o fechamento dos arquivos.
void fecha_arquivo() {
    fclose(entrada);
    fclose(saida);
}