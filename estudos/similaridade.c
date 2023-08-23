#include <stdio.h>
#include <string.h>

#define k 10
#define g (-2)
/*
char align_s[k]
char align_t[k]
*/
int tam_seq(char *seq) {
  char c = seq[0];
  int i = 0;
  while (seq[i])
    i++;
  return i;
}

int par(char a, char b) {
  if (a == b)
    return 1;
  return (-1);
}

int max(int x, int y, int z) {
  int maior = x;
  if (maior < y)
    maior = y;
  if (maior < z)
    maior = z;
  return maior;
}

void print_seq(char *t, int n) {
  printf("      ");
  for (int i = 0; i < n; i++)
    printf("  %c   ", t[i]);
  printf("\n");
}

void print_matrix(char *s, char *t, int m, int n, int a[m][n]) {
  print_seq(t, n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
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

int min(int x, int y, int z) {
  int min = x;
  if (y < min)
    y = min;
  if (z < min)
    z = min;
  return min;
}

char *alinhar(char *s, char *t, int m, int n, int a[m][n]) {
  char alin_s[m], alin_t[n];
  int min;
  for (int i = (m - 1); i > 0; i--) {
    for (int j = (n - 1); j > 0; j--) {
      
    }
  }
}

void similaridade(char *s, char *t, int m, int n) {
  int p;
  int a[m][n];
  for (int i = 0; i < m; i++)
    a[i][0] = i * g;
  for (int j = 0; j < n; j++)
    a[0][j] = j * g;

  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      p = par(s[i], t[j]);
      a[i][j] =
          max((a[i - 1][j] + g), (a[i - 1][j - 1] + p), (a[i][j - 1] + g));
    }
  }
  print_matrix(s, t, m, n, a);
}
/*
void alinhar(int i, int j, int len, int m, int n, int a[m][n], char *s, char *t)
{ if(i == 0 && j ==0 ) len = 0; else if(i > 0 && a[i][j] == a[i-1][j]+g) {
    alinhar(i-1, j, len, m, n, a, s, t);
    len = len+1;
    align_s[len] = s[i];
    align_t[len] = '-';
  } else if((i>0 && j>0) && a[i][j] == a[i-1][j-1] + par(s[i], t[j])) {

  }
}
*/
int main(void) {
  char s[k], t[k];

  printf("---INSIRA SEQUÊNCIAS DE ATÉ 10 CARACTERES---\n");
  printf("---COMECE AS SEQUÊNCIAS COM '-' OU OUTRO CARACTER PARA INDICAR "
         "GAP---\n\n");
  printf("EXEMPLOS: -ACT E -AACT\n\n");
  printf("Insira a primeira sequência: ");
  scanf("%s", s);
  printf("\nInsira a segunda sequência: ");
  scanf("%s", t);

  int m = tam_seq(s);
  int n = tam_seq(t);
  if (m < n)
    similaridade(s, t, m, n);
  else
    similaridade(t, s, n, m);

  return 0;
}