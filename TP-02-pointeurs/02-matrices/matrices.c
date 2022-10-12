#include "matrices.h"

int init_matrix(Matrice *M, int i, int j)
{
    M->i = i;
    M->j = j;
    M->cbSize = sizeof(int) * M->i * M->j;

    M->ppValeurs = (int*) calloc(M->i, sizeof(int) * M->j);
    if (M->ppValeurs == NULL) return -1;
    return 0;
}

void add_value_matrix(Matrice *M, int value, int i, int j)
{  
    if (M->ppValeurs != NULL) 
    {
        if (i * j <= M->cbSize)
        {
            *((M->ppValeurs + i * M->j) + j) = value;
        }
    }
}

int matrix_mult(Matrice *M, Matrice *m1, Matrice *m2)
{
    int i = 0, j = 0, k = 0;

    int value = 0;

    if (m1->i != m2->j) return -1;

    if (init_matrix(M, m1->i, m2->j) != 0) return -2;

    for (i = 0; i < M->i; i++)
    {
        for (j = 0; j < M->j; j++)
        {
            for (k = 0; k < M->j; k++)
            {
                value += *((m1->ppValeurs + i) + k) * *((m2->ppValeurs + k) + j);
            }
            add_value_matrix(M, value ,i , j);
            value = 0;
        }
    }

    return 0;
}

void matrix_print(Matrice *M)
{
    int i = 0, j = 0;

    for (i = 0; i < M->i; i++)
    {
        for (j = 0; j < M->j; j++)
        {
            fprintf(stdout, "%d ", *((M->ppValeurs + i) + j));
        }
        fprintf(stdout, "\n");
    }
}