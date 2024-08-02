#include <stdio.h>
#include <stdlib.h>

#define NUM_FILES 5
#define SIZE 20

typedef struct {
    char* seq;
    int size;
} sequence;

int get_size(char *s) {
    int t = 0;
    while(s[t]) t++;
    return t;
}

void swap(sequence** x, sequence** y){ 
    sequence* temp = *x; 
    *x = *y; 
    *y = temp;
} 
  
void selectionSort(sequence** s) { 
    int i, j, min_idx; 
    for (i = 0; i < NUM_FILES - 1; i++) { 
        min_idx = i; 
        for (j = i + 1; j < NUM_FILES; j++) 
            if (s[j]->size < s[min_idx]->size) 
                min_idx = j; 
        swap(&s[min_idx], &s[i]); 
    } 
}

int malloc_memory(sequence** s) {
    for(int i = 0; i < NUM_FILES; i++) {
        s[i] = (sequence*)malloc(sizeof(sequence));
        if (s[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para sequence[%d].\n", i);
            return 1;
        }
        s[i]->seq = (char*)malloc(SIZE * sizeof(char));
        if (s[i]->seq == NULL) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            return 1;
        }
    }
    return 0;
}

int read_files(const char** fileNames, sequence** s) {
    FILE* file;
    for(int i = 0; i < NUM_FILES; i++) {
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
    const char* fileNames[NUM_FILES] = {"seq1.txt", "seq2.txt", "seq3.txt", "seq4.txt", "seq5.txt"};
    sequence* sequences[NUM_FILES];

    // Alocar memória para as sequências
    if (malloc_memory(sequences)) return 1;

    // Ler os arquivos
    if (read_files(fileNames, sequences)) return 1;

    // Ordenar as sequências pelo tamanho
    selectionSort(sequences);

    // Imprimir as sequências
    for(int i = 0; i < NUM_FILES; i++) {
        printf("Seq %d: %s Tam: %d\n", i, sequences[i]->seq, sequences[i]->size);
    }

    // Liberar a memória alocada
    for(int i = 0; i < NUM_FILES; i++) {
        free(sequences[i]->seq);
        free(sequences[i]);
    }

    return 0;
}
