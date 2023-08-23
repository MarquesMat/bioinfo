#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 100

int tamanho_dna(char *vetor) {
  if(!vetor[0]) return 0;
  int tam = 1;
  for(int i=1; i<m && vetor[i]; i++) tam++;
  return tam;
}

char base_complementar(char base) {
  switch(base) {
    case 'A': return 'T';
    case 'T': return 'A';
    case 'C': return 'G';
    case 'G': return 'C';
    case ' ': return ' ';
    default: return '?'; //erro
  }
}

char *fita_complementar(char *seq, int tam) {
  char *fita = (char*) malloc(tam * sizeof(char));
  for(int i=0; i<tam; i++) {
    fita[i] = base_complementar(seq[i]);
  }
  return fita;
}

char *inverter(char *seq, int tam) {
  char *inv = (char*) malloc(tam * sizeof(char));
  for(int i=0; i<tam; i++) {
    inv[i] = seq[tam-1-i];
  }
  return inv;
}

int verif_palindromo(char *seq, int tam, int primeiro) {
  char *inv = inverter(seq, tam);
  inv = fita_complementar(inv, tam);
  if(!strcmp(seq, inv)) {
    if(primeiro) printf("\n\nPalindromos de tamanho %d:\n", tam);
    printf("|%s|", seq);
    return 0;
  }
  return primeiro;
}

void substring(char *seq) {
  int tam_seq = tamanho_dna(seq);
  int tam_sub = 2, pri = 1;
  while(tam_sub <= tam_seq) {
    char sub[tam_sub];
    for(int n=0; n<=tam_seq-tam_sub; n++) {
      for(int i=0; i<tam_sub; i++) {
        sub[i] = seq[i+n];
      }
      pri = verif_palindromo(sub, tam_sub, pri);
    }
    tam_sub += 2;
    pri = 1;
  }
}

int main(void) {
  char dna[m];
  printf("---ESTE PROGRAMA CONSIDERA SEQUÊNCIAS DE ATÉ %d CARACTERES---\n---PARA VALORES SUPERIORES, ALETERE A VARIÁVEL GLOBAL m NO CÓDIGO.---", m);
  printf("\n\nDigite uma sequência de DNA:\n");
  scanf("%s", dna);
  substring(dna);
  return 0;
}