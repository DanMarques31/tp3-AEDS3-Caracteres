#include <stdio.h>
#include "file.h"

FILE* entrada, *saida;

//Função para abertura do arquivo de entrada para leitura, e de saída para escrita.
void abre_arquivo(char argv[]) {
    entrada = fopen(argv, "r");
    saida = fopen("saida.txt", "w");

    //Se o arquivo estiver vazio retorna erro.
    if (entrada == NULL) {
        printf("Falha na abertura do arquivo.\n");
    }
}

//Função para o fechamento dos arquivos.
void fecha_arquivo() {
    fclose(entrada);
    fclose(saida);
}