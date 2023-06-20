#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmp.h"

// Função para calcular o array tabSalto, usado para que o algoritmo KMP não tenha que realizar comparações desnecessarias
// Essa funçaõ torna o algoritmo mais eficiente, mas não é necessaria para o funcionamento do algoritmo 
int *tabela_salto(char *padrao) {

    int tam = strlen(padrao);
    int *tabSalto = (int *)malloc(sizeof(int) * tam);
    int i = 1;
    int j = 0;
    tabSalto[0] = 0;

    // Construindo o array tabSalto
    while (i < tam) {
        // Verifica se i é igual a j
        if (padrao[i] == padrao[j]) {
            // Caso seja, encotrou-se uma correspondencia
            tabSalto[i] = j + 1;
            // Incrementa i e j para as proximas posiçoes
            i++;
            j++;
        }
        
        else {
            // Não ha correspondencia 
            if (j != 0) {
                // Retrocede o array para encontrar a proxima posição paar comparar
                j = tabSalto[j - 1];
            // Não a correspondencia nem no caso anterior
            } else {
                tabSalto[i] = 0;
                // Avança para os proximos caracteres do padrao
                i++;
            }
        }
    }

    return tabSalto;
}

// Função para realizar a busca KMP
int kmp(char *texto, char *padrao) {

    int tam_texto = strlen(texto);
    int tam_padrao = strlen(padrao);
    int *tabSalto = tabela_salto(padrao);
    int i = 0;
    int j = 0;

    // Percorrendo o texto e buscando o padrão
    while (i < tam_texto) {

        if (texto[i] == padrao[j]) {
            i++;
            j++;
        }

        // Se o padrão for encontrado completamente, retorna a posição correspondente no texto
        if (j == tam_padrao) {
            free(tabSalto);
            return i - j;
        }

        // Caso haja uma diferença no caractere, atualiza o índice j usando o array tabSalto
        if (i < tam_texto && texto[i] != padrao[j]) {

            if (j != 0) {
                j = tabSalto[j - 1];
            }
            
            else {
                i++;
            }
        }
    }

    free(tabSalto);
    return -1; // Retorna -1 se o padrão não for encontrado
}

// Função para verificar a sequência no texto e no padrão
int verificar_padrao_kmp(char *padrao, char *pedra) {

    int tam_pedra = strlen(pedra);

    // Cria uma versão cíclica da pedra concatenando-a consigo mesma
    char *pedra_redonda = (char *)malloc(sizeof(char) * (2 * tam_pedra + 1));
    strcpy(pedra_redonda, pedra);
    strcat(pedra_redonda, pedra);

    // Verifica se há uma correspondência cíclica entre a sequência e a pedra
    int posicao = kmp(pedra_redonda, padrao);
    free(pedra_redonda);

    if (posicao != -1){
        return posicao;
    }

    // Cria uma versão invertida da pedra
    char *pedra_invertida = (char *)malloc(sizeof(char) * (tam_pedra + 1));

    for (int i = 0; i < tam_pedra; i++) {
        pedra_invertida[i] = pedra[tam_pedra - i - 1];
    }
    
    pedra_invertida[tam_pedra] = '\0';

    // Verifica se há uma correspondência com a palavra invertida
    posicao = kmp(pedra_invertida, padrao);
    free(pedra_invertida);

    if (posicao != -1){
        return tam_pedra - posicao - 1;
    }

    return posicao;
}

