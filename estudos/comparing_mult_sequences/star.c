#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FILES 5
#define SIZE 20
#define g -2

typedef struct {
  char *seq;
  int size;
} sequence;

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

int alinhar(int i, int j, int len, int **a, char *s, char *t, char *align_s,
            char *align_t) {
  if (i == 0 && j == 0)
    len = 0;
  else if (i > 0 && a[i][j] == a[i - 1][j] + g) { // Seta vertical
    len = alinhar(i - 1, j, len, a, s, t, align_s, align_t);
    len++;
    align_s[len] = s[i];
    align_t[len] = '-';
  } else if (i > 0 && j > 0 &&
             a[i][j] == a[i - 1][j - 1] + par(s[i], t[j])) { // Seta diagonal
    len = alinhar(i - 1, j - 1, len, a, s, t, align_s, align_t);
    len++;
    align_s[len] = s[i];
    align_t[len] = t[j];
  } else { // Seta horizontal
    len = alinhar(i, j - 1, len, a, s, t, align_s, align_t);
    len++;
    align_s[len] = '-';
    align_t[len] = t[j];
  }
  return len;
}

int similaridade(sequence *seq_s, sequence *seq_t, sequence *seq_align_s,
                 sequence *seq_align_t) { // Gera a matriz de similaridade
  char *s, *t;
  s = seq_s->seq;
  t = seq_t->seq;
  int p, m, n;
  m = seq_s->size;
  n = seq_t->size;
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
      a[i][j] =
          max((a[i - 1][j] + g), (a[i - 1][j - 1] + p), (a[i][j - 1] + g));
    }
  }
  print_matrix(s, t, m, n, a);
  return alinhar(m-1, n-1, 0, a, s, t, seq_align_s->seq, seq_align_t->seq);
}

int get_size(char *s) {
  int t = 0;
  while (s[t])
    t++;
  return t;
}

void swap(sequence **x, sequence **y) {
  sequence *temp = *x;
  *x = *y;
  *y = temp;
}

void selectionSort(sequence **s) {
  int i, j, min_idx;
  for (i = 0; i < NUM_FILES - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < NUM_FILES; j++)
      if (s[j]->size < s[min_idx]->size)
        min_idx = j;
    swap(&s[min_idx], &s[i]);
  }
}

int malloc_memory(sequence **s, int size_seq) {
  for (int i = 0; i < NUM_FILES; i++) {
    s[i] = (sequence *)malloc(sizeof(sequence));
    if (s[i] == NULL) {
      fprintf(stderr, "Erro ao alocar memória para sequence[%d].\n", i);
      return 1;
    }
    s[i]->seq = (char *)malloc(size_seq * sizeof(char));
    if (s[i]->seq == NULL) {
      fprintf(stderr, "Erro ao alocar memória.\n");
      return 1;
    }
  }
  return 0;
}

int read_files(const char **fileNames, sequence **s) {
  FILE *file;
  for (int i = 0; i < NUM_FILES; i++) {
    file = fopen(fileNames[i], "r");
    if (file == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo %s.\n", fileNames[i]);
      return 1;
    }
    fgets(s[i]->seq, SIZE, file);
    fclose(file);
    s[i]->size = get_size(s[i]->seq);
  }
  return 0;
}

int main(void) {
  const char *fileNames[NUM_FILES] = {"seq1.txt", "seq2.txt", "seq3.txt",
                                      "seq4.txt", "seq5.txt"};
  sequence *sequences[NUM_FILES];
  sequence *sequences_align[NUM_FILES];
  sequence *center[NUM_FILES];

  // Alocar memória para as sequências
  if (malloc_memory(sequences, SIZE))
    return 1;
  if (malloc_memory(sequences_align, 2*SIZE))
    return 1;
  if (malloc_memory(center, 2*SIZE))
    return 1;

  // Ler os arquivos
  if (read_files(fileNames, sequences))
    return 1;

  // Ordenar as sequências pelo tamanho
  selectionSort(sequences);

  // Imprimir as sequências
  for (int i = 0; i < NUM_FILES; i++) {
    printf("Seq %d: %s Tam: %d\n", i, sequences[i]->seq, sequences[i]->size);
  }

  printf("\nTestando as matrizes:\n");
  for (int i = 1; i < NUM_FILES; i++) {
    printf("%d", similaridade(sequences[0], sequences[i], center[i], sequences_align[i]));
  }

  // Liberar a memória alocada
  for (int i = 0; i < NUM_FILES; i++) {
    free(sequences[i]->seq);
    free(sequences[i]);
    free(sequences_align[i]->seq);
    free(sequences_align[i]);
    free(center[i]->seq);
    free(center[i]);
  }

  return 0;
}
