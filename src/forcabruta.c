#include <stdio.h>
#include <string.h>
#include "forcabruta.h"
#include "file.h"

void forca_bruta(char *padrao, char *pedra, FILE *saida) {

    // Armazena o tamanho da sequencia e da pedra.
    int tam_padrao = strlen(padrao);
    int tam_pedra = strlen(pedra);

    for (int i = 0; i < tam_pedra; i++) {
        
        int casamento = 1;

        for (int j = 0; j < tam_padrao; j++) {

            if (pedra[(i + j) % tam_pedra] != padrao[j]) {
                casamento = 0;
                break;
            }
        }

        if (casamento == 0) {
            
            casamento = 1;

            for (int j = 0; j < tam_padrao; j++) {

                if (pedra[(i - j + tam_pedra) % tam_pedra] != padrao[j]) {
                    casamento = 0;
                    break;
                }
            }
        }

        if (casamento == 1) {

            fprintf(saida, "S %d\n", i + 1);
            return;
        }
    }

    // Sequência não encontrada
    fprintf(saida, "N\n");
}

