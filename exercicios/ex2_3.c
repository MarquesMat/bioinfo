//PROGRAMA PARA CRIAR A FITA DE DNA COMPLEMENTAR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define m 100
//tamanho da fita

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
    default: return '?'; //erro
  }
}

char *fita_complementar(char *dna) {
  int tam = tamanho_dna(dna);
  char *fita = (char*) malloc(tam * sizeof(char));
  for(int i=0; i<tam; i++) {
    fita[i] = base_complementar(dna[i]);
  }
  return fita;
}

int main(void) {
  char dna[m];
  printf("Insira uma sequência de DNA: ");
  scanf("%s", dna);
  printf("\nFITA COMPLETA:\n");
  printf("5' %s 3':\n", dna);
  printf("3' %s 5':", fita_complementar(dna));
  return 0;
}