#include "echangeContenu.h"

void echangeContenu(int *a, int *b)
{
    int temp_int = *b;

    *b = *a;
    *a = temp_int;
}