#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_TERMS 101 // maximum number of terms + 1
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y))? 0: 1)

typedef struct{
    int32_t col;
    int32_t row;
    int32_t value;
} term;

// Program 2.8
void fast_sparse_transpose(term a[],term b[]);

// Program 2.10
void store_sum(term d[], int32_t *totald, int32_t row, int32_t column, int32_t *sum);

// Program 2.9
void mmult(term a[], term b[], term d[]);
