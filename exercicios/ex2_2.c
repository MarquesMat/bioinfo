//PROGRAMA PARA IDENTIFICAR SUBSTRINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define m 100 
//tamanho máximo da sequência

int tamanho_vetor(char *vetor) {
  if(!vetor[0]) return 0;
  int tam = 1;
  for(int i=1; vetor[i]; i++) tam++;
  return tam;
}

char *pegar_sub(char *vetor, int tam, int ind) {
  char *sub = (char*) malloc(tam * sizeof(char));
  for(int i=ind; i<(tam+ind); i++) sub[i-ind] = vetor[i];
  return sub;
}

int eh_substring(char *v1, char *v2, int b) {
  if(!strcmp(v1, v2)) return 3; //verifica se são iguais
  int tam1 = tamanho_vetor(v1), tam2 = tamanho_vetor(v2);
  if(tam1 < tam2) return eh_substring(v2, v1, 2); //garante que v1 seja o maior vetor
  else if(tam1 == tam2) return 0;
  for(int i=0; i<(tam1-tam2); i++) {
    if(v1[i] == v2[0]) {
      if(!strcmp(pegar_sub(v1, tam2, i), v2)) return b;
    }
  }
  return 0;
}

int main(void) {
  char vetor_p[m], vetor_t[m];

  //usar apenas caracteres em maiúsculo
  printf("Insira a primeira sequência de bases: "); //AATGCTTGC
  scanf("%s", vetor_p);
  
  printf("Insira a segunda sequência de bases: "); //GCT
  scanf("%s", vetor_t);
  
  printf("\nSequência: %s\nTamanho: %d\n", vetor_p, tamanho_vetor(vetor_p));
  printf("\nSequência: %s\nTamanho: %d\n", vetor_t, tamanho_vetor(vetor_t));

  switch(eh_substring(vetor_p, vetor_t, 1)) {
    case 1: printf("\nA segunda sequência é uma substring da primeira sequência."); break;
    case 2: printf("\nA primeira sequência é uma substring da segunda sequência."); break;
    case 3: printf("\nAs sequências são iguais."); break;
    default: printf("\nNão há substrings.");
  }
  
  return 0;
}