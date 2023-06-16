#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmh.h"

// Função auxiliar para calcular o deslocamento maximo
int verifica_max(int a, int b) {

    if (a > b) {
        return a;
    }

    return b;
}

// Função para construir a tabela de salto para o BMH
int* tabelaSalto(char* padrao, int tam_padrao) {

    int* tabela = (int*)malloc(sizeof(int) * 256);

    // Inicializa a tabela com o tamanho do padrão
    for (int i = 0; i < 256; i++) {
        tabela[i] = tam_padrao;
    }

    // Preenche a tabela com os saltos corretos para cada caractere do padrão
    for (int i = 0; i < tam_padrao - 1; i++) {
        tabela[padrao[i]] = tam_padrao - i - 1;
    }

    return tabela;
}

// Função de busca utilizando o algoritmo BMH
int bmh(char* texto, int tam_texto, char* padrao, int tam_padrao) {

    // Ponteiro para a tabela de saltos
    int* pTabelaSalto = tabelaSalto(padrao, tam_padrao);
    int shift = 0;
    int i = tam_padrao- 1;
    int j;

    while (i < tam_texto) {
        j = tam_padrao - 1;

        // Verifica os caracteres do padrão com o texto
        while (j >= 0 && texto[i] == padrao[j]) {
            i--;
            j--;
        }

        // Se chegou ao final do padrão, encontrou uma correspondência
        if (j < 0) {
            free(pTabelaSalto);
            return i + 1;
        }

        // Calcula o deslocamento com base na tabela de salto
        shift = verifica_max(pTabelaSalto[texto[i]], tam_padrao - j);
        i += shift;
    }

    free(pTabelaSalto);
    return -1;
}

// Função para verificar a correspondência da sequência na pedra
int verificar_padrao_bmh(char* padrao, char* pedra) {

    int tam_padrao = strlen(padrao);
    int tam_pedra = strlen(pedra);
    int posicao = -1;

    // Verificar sequência normal
    posicao = bmh(pedra, tam_pedra, padrao, tam_padrao);
    
    if (posicao != -1) {
        return posicao;
    }

    // Verificar sequência cíclica
    // Criar uma versão duplicada da pedra
    char* pedra_dupla = (char*)malloc(sizeof(char) * (2 * tam_pedra + 1));
    strcpy(pedra_dupla, pedra);// Copiar a pedra para a primeira metade
    strcat(pedra_dupla, pedra);// Concatenar a pedra novamente para formar a segunda metade
    
    // Verificar a correspondência com a sequência usando BMH na pedra duplicada
    posicao = bmh(pedra_dupla, 2 * tam_pedra, padrao, tam_padrao);

    if (posicao != -1) {

        // Se houver correspondência, calcular a posição cíclica
        int pos_ciclica = (posicao % tam_pedra);
        free(pedra_dupla);
        return pos_ciclica;
    }

    // Verificar sequência na ordem inversa
    char* padrao_inverso = (char*)malloc(sizeof(char) * (tam_padrao + 1));

    for (int i = 0; i < tam_padrao; i++) {
        padrao_inverso[i] = padrao[tam_padrao - 1 - i];
    }

    padrao_inverso[tam_padrao] = '\0';

    // Verificar a correspondência com a sequência inversa usando BMH
    posicao = bmh(pedra, tam_pedra, padrao_inverso, tam_padrao);

    if (posicao != -1) {

        // Se houver correspondência, calcular a posição inversa
        int pos_inversa = tam_pedra - posicao - 1;
        free(padrao_inverso);
        return pos_inversa;
    }

    // Sequência não encontrada
    free(padrao_inverso);
    return -1;
}
