#include "semiglobal.h"

/*
AVISO
Esta comparação semiglobal está zerando os custos dos gaps localizados no início e no fim da segunda sequência
Assim como nas demais comparações, considera-se que a segunda sequência (t) é a menor
*/

int **semiglobal_comparison(char *s, char *t, int m, int n)
{ // Gera a matriz de similaridade
  int p;
  // Alocar memória para a matriz de similaridade
  int **a = (int **)malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++)
    a[i] = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < m; i++)
    a[i][0] = 0; // Inicializar primeira coluna com zeros
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

int max_last_colunmn(int **a, int m, int n) {
    int ind_i = 0;
    int maior = a[0][-1];
    for(int i=1; i<m; i++) {
        if(a[i][n-1] >= maior) {
            maior = a[i][n-1];
            ind_i = i;
        }
    }
    return ind_i;
}

int end_sequences(struct auxiliar aux, int len) {
  int gap = 0, base = 0;
  for(int i=0; i<len; i++) {
    if(align_s[i] == '-') gap++;
    else base++;
  }
  for(int i=base+gap+1; i<aux.m; i++) {
    align_s[i] = aux.s[i];
    align_t[i] = '-';
  }
  return aux.m+gap;
}

int alinhar_semiglobal(int i, int j, int len, struct auxiliar aux)
{
  if (i == 0 && j == 0)
    len = 0;
  else if (j == 0 || (i > 0 && aux.a[i][j] == aux.a[i - 1][j] + g))
  { // Seta vertical
    len = alinhar_semiglobal(i - 1, j, len, aux);
    len++;
    align_s[len] = aux.s[i];
    align_t[len] = '-';
  }
  else if (i > 0 && j > 0 && aux.a[i][j] == aux.a[i - 1][j - 1] + par(aux.s[i], aux.t[j]))
  { // Seta diagonal
    len = alinhar_semiglobal(i - 1, j - 1, len, aux);
    len++;
    align_s[len] = aux.s[i];
    align_t[len] = aux.t[j];
  }
  else
  { // Seta horizontal
    len = alinhar_semiglobal(i, j - 1, len, aux);
    len++;
    align_s[len] = '-';
    align_t[len] = aux.t[j];
  }
  return len;
}