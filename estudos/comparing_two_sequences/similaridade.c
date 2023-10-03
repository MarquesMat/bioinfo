#include <string.h>

// Bibliotecas criadas
#include "global.h"
#include "local.h"
#include "all.h"

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
  printf("\n\n");
  //aux.a = local_comparasion(aux.s, aux.t, aux.m, aux.n);
  len = alinhar(aux.m-1, aux.n-1, len, aux);

  print_alignments(align_s, len);
  print_alignments(align_t, len);
  printf("\n");
  return 0;
}
