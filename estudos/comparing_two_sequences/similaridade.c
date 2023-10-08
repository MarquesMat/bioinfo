#include <string.h>

// Bibliotecas criadas
#include "global.h"
#include "local.h"
#include "semiglobal.h"
#include "all.h"

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

  switch (choose_comparation())
  {
  case 1: // Global
    aux.a = similaridade(aux.s, aux.t, aux.m, aux.n); // A função recebe a maior sequência como primeiro parâmetro
    len = alinhar(aux.m-1, aux.n-1, len, aux);
    break;
  case 2: // Local
    aux.a = local_comparison(aux.s, aux.t, aux.m, aux.n); // A função recebe a maior sequência como primeiro parâmetro
    len = alinhar_local(aux.m-1, aux.n-1, len, aux);
    break;
  case 3: // Semiglobal -CAGCACTTGGATTCTCGG  -CAGCGTGG
    aux.a = semiglobal_comparison(aux.s, aux.t, aux.m, aux.n); // A função recebe a maior sequência como primeiro parâmetro
    int ind_i = max_last_colunmn(aux.a, aux.m, aux.n);
    len = alinhar_semiglobal(ind_i, aux.n-1, len, aux);
    len = end_sequences(aux, len);
    break;
  default:
    printf("---OPÇÃO INVÁLIDA---");
    break;
  }

  print_alignments(align_s, len);
  print_alignments(align_t, len);
  printf("\n");
  return 0;
}
