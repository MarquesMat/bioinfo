#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define k 10   // Tamanho máximo das sequências
#define g (-2) // Penalidade por espaço vazio (gap)
char align_s[k * 2];
char align_t[k * 2];

struct auxiliar {
  int m, n;
  int **a;
  char s[k], t[k];
};

int tam_seq(char *seq) { // Retorna o tamanho da sequência
  char c = seq[0];
  int i = 0;
  while (seq[i])
    i++;
  return i;
}

int par(char a, char b) { // Verifica se duas bases são iguais
  if (a == b)
    return 1;  // Acerto (match)
  return (-1); // Erro (mismatch)
}

int max(int x, int y, int z) { // Retorna o maior valor
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

void print_matrix(char *s, char *t, int m, int n, int **a) {
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

int **similaridade(char *s, char *t, int m, int n) { // Gera a matriz de similaridade
  int p;
  // Alocar memória para a matriz de similaridade
  int **a = (int **)malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++)
    a[i] = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < m; i++)
    a[i][0] = i * g;
  for (int j = 0; j < n; j++)
    a[0][j] = j * g;

  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
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

void print_alignments(char *align, int len) {
  printf("\n");
  for (int i = 0; i <= len; i++)
      printf("%c", align[i]);
}

int main(void) {
  char s[k], t[k]; // Sequências de bases
  int **a; // Matriz de similaridade
  struct auxiliar aux;
  int len = 0;

  printf("---INSIRA SEQUÊNCIAS DE ATÉ %d CARACTERES---\n", k);
  printf("---COMECE AS SEQUÊNCIAS COM '-' OU OUTRO CARACTER PARA INDICAR GAP---\n\n");
  printf("EXEMPLOS: -ACT E -AACT\n\n");
  printf("Insira a primeira sequência: ");
  scanf("%s", s);
  printf("\nInsira a segunda sequência: ");
  scanf("%s", t);
  
  int m = tam_seq(s); // Tamanho da primeira sequência
  int n = tam_seq(t); // Tamanho da segunda sequência

  // O programa considera que s é maior que t
  if(m>=n) {
    strcpy(aux.s, s);
    strcpy(aux.t, t);
  } else {
    strcpy(aux.s, t);
    strcpy(aux.t, s);
  }

  aux.m = tam_seq(aux.s); // Tamanho da primeira sequência
  aux.n = tam_seq(aux.t); // Tamanho da segunda sequência

  // A função recebe a maior função como primeiro parâmetro, isto garante que a
  // matriz seja impressa no formato correto
  aux.a = similaridade(aux.s, aux.t, aux.m, aux.n);
  len = alinhar(aux.m-1, aux.n-1, len, aux);

  print_alignments(align_s, len);
  print_alignments(align_t, len);

  return 0;
}
