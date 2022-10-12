#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "matrices.h"

#define SIZE 5

int main(void)
{
    Matrice M;
    Matrice M1, M2;

    int matrice1[][SIZE] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5}};
    int matrice2[][SIZE] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5}};
    int i = 0, j = 0;

    if (init_matrix(&M1, 5, 5) != 0) return -1;
    if (init_matrix(&M2, 5, 5) != 0) return -1;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            add_value_matrix(&M1, matrice1[i][j], i, j);

            add_value_matrix(&M2, matrice1[i][j], i, j);
        }
    }

    matrix_print(&M1);
    matrix_print(&M2);

    //matrix_mult(&M, &M1, &M2);
    //matrix_print(&M);

    //free(M.ppValeurs);

    return 0;
}