#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "forcabruta.h"
#include "kmp.h"

int main(int argc, char *argv[]) {

    //Caso n° de argumentos no terminal seja < 3 significa que não foi passado arquivo de texto ou estratégia.
    if (argc < 3) {
        printf("Erro: Faltam argumentos no terminal.\n");
        return 1;
    }

    //Abre o arquivo.
    abre_arquivo(argv[1]);

    int casos_teste;
    fscanf(entrada, "%d", &casos_teste);

    //Executa a 1ª estratégia, o algoritmo de casamento força bruta.
    if (atoi(argv[2]) == 1) {

        for (int i = 0; i < casos_teste; i++) {

            char *padrao = (char *)malloc(sizeof(char) * 100);
            char *pedra = (char *)malloc(sizeof(char) * 1000);

            fscanf(entrada, "%s %s", padrao, pedra);
            forca_bruta(padrao, pedra, saida);

            free(padrao);
            free(pedra);
        }
            
        fecha_arquivo();
        return 0;
    }

    //Executa a 2ª estratégia, o algoritmo de casamento KMP - Knuth Morris Prath.
    if (atoi(argv[2]) == 2) {
    
        for (int i = 0; i < casos_teste; i++) {

            char* padrao = (char*)malloc(sizeof(char) * 100);
            char* pedra = (char*)malloc(sizeof(char) * 1000);
            fscanf(entrada, "%s %s", padrao, pedra);

            // Verifica se há uma sequência correspondente na pedra
            int posicao = verificar_padrao(padrao, pedra);

            // Imprime o resultado
            if (posicao != -1) {
                fprintf(saida, "S %ld\n", (posicao % strlen(pedra)) + 1);
            }

            else {
                fprintf(saida, "N\n");
            }

            free(padrao);
            free(pedra);
        }

        return 0;
    }    
}