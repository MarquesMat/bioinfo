#include "global.h"

int **similaridade(char *s, char *t, int m, int n)
{ // Gera a matriz de similaridade
    int p;
    // Alocar memória para a matriz de similaridade
    int **a = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        a[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++)
        a[i][0] = i * g;
    for (int j = 0; j < n; j++)
        a[0][j] = j * g;

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            p = par(s[i], t[j]);
            a[i][j] = max((a[i - 1][j] + g), (a[i - 1][j - 1] + p), (a[i][j - 1] + g));
        }
    }

    print_matrix(s, t, m, n, a);

    return a;
}

int alinhar(int i, int j, int len, struct auxiliar aux) {
  if (i == 0 && j == 0)
    len = 0;
  else if (i > 0 && aux.a[i][j] == aux.a[i - 1][j] + g) { // Seta vertical
    len = alinhar(i - 1, j, len, aux);
    len++;
    align_s[len] = aux.s[i];
    align_t[len] = '-';
  } else if (i > 0 && j > 0 && aux.a[i][j] == aux.a[i - 1][j - 1] + par(aux.s[i], aux.t[j])) { // Seta diagonal
    len = alinhar(i - 1, j - 1, len, aux);
    len++;
    align_s[len] = aux.s[i];
    align_t[len] = aux.t[j];
  } else { // Seta horizontal
    len = alinhar(i, j - 1, len, aux);
    len++;
    align_s[len] = '-';
    align_t[len] = aux.t[j];
  }
  return len;
}