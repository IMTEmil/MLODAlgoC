#ifndef _MATRICES_H_
#define _MATRICES_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct matrice
{
    int i;

    int j;

    int *ppValeurs;

    int cbSize;
} Matrice;

int init_matrix(Matrice *M, int i, int j);

void add_value_matrix(Matrice *M, int value, int i, int j);

int matrix_mult(Matrice *M, Matrice *m1, Matrice *m2);

void matrix_print(Matrice *M);

void matrix_free(Matrice *M);

#endif /* _MATRICES_H_ */