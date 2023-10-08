#ifndef SEMIGLOBAL_H
#define SEMIGLOBAL_H

#include "all.h"

int **semiglobal_comparison(char *s, char *t, int m, int n);
int max_last_colunmn(int **a, int m, int n);
int alinhar_semiglobal(int i, int j, int len, struct auxiliar aux);
int end_sequences(struct auxiliar aux, int len); // Completa o fim das sequências

#endif // SEMIGLOBAL_H