#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <stdlib.h>

#define k 10   // Tamanho máximo das sequências
#define g (-2) // Penalidade por espaço vazio (gap)
extern char align_s[k * 2];
extern char align_t[k * 2];

struct auxiliar
{
    int m, n;
    int **a;
    char s[k], t[k];
};

int tam_seq(char *seq);
int par(char a, char b);
int max(int x, int y, int z);
void print_seq(char *t, int n);
void print_matrix(char *s, char *t, int m, int n, int **a);

#endif // ALL_H