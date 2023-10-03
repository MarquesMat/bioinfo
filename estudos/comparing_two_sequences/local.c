#include "local.h"

int alinhar_local(int i, int j, int len, struct auxiliar aux)
{
    if (i == 0 && j == 0)
        len = 0;
    else if (i > 0 && aux.a[i][j] == aux.a[i - 1][j] + g)
    { // Seta vertical
        len = alinhar_local(i - 1, j, len, aux);
        len++;
        align_s[len] = aux.s[i];
        align_t[len] = '-';
    }
    else if (i > 0 && j > 0 && aux.a[i][j] == aux.a[i - 1][j - 1] + par(aux.s[i], aux.t[j]))
    { // Seta diagonal
        len = alinhar_local(i - 1, j - 1, len, aux);
        len++;
        align_s[len] = aux.s[i];
        align_t[len] = aux.t[j];
    }
    else
    { // Seta horizontal
        len = alinhar_local(i, j - 1, len, aux);
        len++;
        align_s[len] = '-';
        align_t[len] = aux.t[j];
    }
    return len;
}

int **local_comparasion(char *s, char *t, int m, int n)
{ // Gera a matriz de similaridade para alinhamento local
    int p, max_value;
    // Alocar memória para a matriz de similaridade
    int **a = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        a[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++)
        a[i][0] = 0;
    for (int j = 0; j < n; j++)
        a[0][j] = 0;

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            p = par(s[i], t[j]);
            max_value = max((a[i - 1][j] + g), (a[i - 1][j - 1] + p), (a[i][j - 1] + g));
            // Garante que o menor valor atribuído será zero
            a[i][j] = max_value >= 0 ? max_value : 0;
        }
    }

    print_matrix(s, t, m, n, a);

    return a;
}
