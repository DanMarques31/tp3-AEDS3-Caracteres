#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include "file.h"
#include "forcabruta.h"
#include "kmp.h"
#include "bmh.h"

int main(int argc, char *argv[]) {

    //Cria a struct e a variável para o uso da função 'getrusage' .
    struct rusage usage;
    double user_time, system_time;

    //Caso n° de argumentos no terminal seja < 3 significa que não foi passado arquivo de texto ou estratégia.
    if (argc < 3) {
        printf("Erro: Faltam argumentos no terminal.\n");
        return 1;
    }

    //Abre o arquivo de entrada e saida.
    abre_arquivo(argv[1]);

    // Cria a variável que armazena a quantidade de testes e lê ela do arquivo.
    int casos_teste;
    fscanf(entrada, "%d", &casos_teste);

    // Executa a 1ª estratégia, o algoritmo de casamento força bruta.
    if (atoi(argv[2]) == 1) {

        // Itera sobre cada casos teste.
        for (int i = 0; i < casos_teste; i++) {
            
            // Aloca memória para o padrão e para a pedra.
            char *padrao = (char *)malloc(sizeof(char) * 100);
            char *pedra = (char *)malloc(sizeof(char) * 1000);

            // Obtém as strings de padrão e pedra do arquivo e faz a chamada da função do algoritmo força bruta.
            fscanf(entrada, "%s %s", padrao, pedra);
            forca_bruta(padrao, pedra, saida);

            // Libera a memória do padrão e da pedra.
            free(padrao);
            free(pedra);
        }
    }

    //Executa a 2ª estratégia, o algoritmo de casamento KMP - Knuth Morris Prath.
    if (atoi(argv[2]) == 2) {
        
        // Itera sobre cada casos teste.
        for (int i = 0; i < casos_teste; i++) {

            // Aloca memória do padrão e da pedra e obtém as strings do arquivo.
            char* padrao = (char*)malloc(sizeof(char) * 100);
            char* pedra = (char*)malloc(sizeof(char) * 1000);
            fscanf(entrada, "%s %s", padrao, pedra);

            // Verifica se há um casamento na pedra.
            int posicao = verificar_padrao_kmp(padrao, pedra);

            // Imprime o resultado.
            if (posicao != -1) {
                fprintf(saida, "S %ld\n", (posicao % strlen(pedra)) + 1);
            }

            // Imprime caso não haja casamento.
            else {
                fprintf(saida, "N\n");
            }

            // Libera a memória do padrão e da pedra.
            free(padrao);
            free(pedra);
        }
    }

    // Executa a 3ª estratégia, o algoritmo de casamento BMH - Boyer-Moore-Horspool.
    if (atoi(argv[2]) == 3) {

        // Itera sobre cada casos teste.
        for (int i = 0; i < casos_teste; i++) {

            // Aloca memória do padrão e da pedra e obtém as strings do arquivo.
            char* padrao = (char*)malloc(sizeof(char) * 100);
            char* pedra = (char*)malloc(sizeof(char) * 1000);
            fscanf(entrada, "%s %s", padrao, pedra);

            // Verifica se há um casamento na pedra.
            int posicao = verificar_padrao_bmh(padrao, pedra);

            // Imprime o resultado.
            if (posicao != -1) {
                fprintf(saida, "S %d\n", posicao + 1);
            }

            // Imprime caso não haja casamento.
            else {
                fprintf(saida, "N\n");
            }

            // Libera a memória do padrão e da pedra.
            free(padrao);
            free(pedra);
        }
    }

    //Chamada da função 'getrusage'.
    getrusage(RUSAGE_SELF, &usage);

    //Conversão dos tempos para segundos.
    user_time = (double) usage.ru_utime.tv_sec + (double) usage.ru_utime.tv_usec / 1000000.0;
    system_time = (double) usage.ru_stime.tv_sec + (double) usage.ru_stime.tv_usec / 1000000.0;
    
    //Impressão dos tempos de execução.
    printf("Tempo de usuário: %f segundos\n", user_time);
    printf("Tempo de sistema: %f segundos\n", system_time);

    fecha_arquivo();
    return 0;
}