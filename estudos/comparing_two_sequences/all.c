#include "all.h"

char align_s[k * 2];
char align_t[k * 2];

int tam_seq(char *seq)
{ // Retorna o tamanho da sequência
    char c = seq[0];
    int i = 0;
    while (seq[i])
        i++;
    return i;
}

int par(char a, char b)
{ // Verifica se duas bases são iguais
    if (a == b)
        return 1; // Acerto (match)
    return (-1);  // Erro (mismatch)
}

int max(int x, int y, int z)
{ // Retorna o maior valor
    int maior = x;
    if (maior < y)
        maior = y;
    if (maior < z)
        maior = z;
    return maior;
}

void print_seq(char *t, int n)
{
    printf("      ");
    for (int i = 0; i < n; i++)
        printf("  %c   ", t[i]);
    printf("\n");
}

void print_matrix(char *s, char *t, int m, int n, int **a)
{
    print_seq(t, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!j)
                printf("  %c  ", s[i]);
            if (a[i][j] < 0)
                printf("  %d  ", a[i][j]);
            else
                printf("   %d  ", a[i][j]);
        }
        printf("\n");
    }
}
