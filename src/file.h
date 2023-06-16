#ifndef FILE_H
#define FILE_H

#include <stdio.h>

//Extern indica para o compilador que a variável ja foi definida em outro arquivo, precisei usar para não gerar erros de redundância de declaração.

extern FILE* entrada, *saida;
void abre_arquivo(char[]);
void fecha_arquivo();

#endif
