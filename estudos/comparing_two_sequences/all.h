#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <stdlib.h>

#define k 50   // Tamanho máximo das sequências
#define g (-2) // Penalidade por espaço vazio (gap)
extern char align_s[k * 2];
extern char align_t[k * 2];

// Essa estrutura facilita passar todos os valores dela nas funções recursivas
struct auxiliar
{
    int m, n;
    int **a;
    char s[k], t[k];
};

int choose_comparation(); // O usuário escolhe o tipo de comparação
int tam_seq(char *seq); // Retorna o tamanho de uma sequência
int par(char a, char b); // Retorn 1 se a == b ou 0 se a != b
int max(int x, int y, int z); // Retorna o maior valor entre x, y e z
void print_seq(char *t, int n); // Imprime a sequência t na parte superior da matriz
void print_matrix(char *s, char *t, int m, int n, int **a); // Imprime a matriz de similaridade, incluindo a sequência s na sua lateral
void print_alignments(char *align, int len); // Imprime as sequências alinhadas

#endif // ALL_H
