/*
 * matrix-product.c
 *
 *  Created on: Nov 24, 2014
 *      Author: nome
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 0;  // This is the row and column dimension of the matrices
    int* matrix1 = NULL;
    int* matrix2 = NULL;
    int* product = NULL;
    int accumulator = 0;

    FILE* fileHandle = fopen("Data4.txt", "r");

    fscanf(fileHandle, "%d", &size);

    // Allocate space for 3 matrices of equal dimensions. The
    // matrices are represented by a 1-dimensional array and are of
    // length nxn (size x size).
    matrix1 = (int*) (malloc(sizeof(int) * size * size));
    matrix2 = (int*) (malloc(sizeof(int) * size * size));
    product = (int*) (malloc(sizeof(int) * size * size));

    for (int i = 0; i < size * size; i++) {
        fscanf(fileHandle, "%d", &matrix1[i]);
    }

    for (int i = 0; i < size * size; i++) {
        fscanf(fileHandle, "%d", &matrix2[i]);
    }

    fclose(fileHandle);

    {
        // My algorithm is based on the observation that (with respect to
        // square matrix dimensions) all elements of
        // a row have the same integer-division result, and all elements of
        // a column are the same modulus. This allows one extra loop
        // to be cut out!

        int row_start;
        int column_start;

        for (int i = 0; i < size * size; i++) {
            row_start = (i/size) * size;
            column_start = i % size;
            accumulator = 0;

            for (int j = 0; j < size; j++) {
                accumulator += matrix1[row_start + j] *
                               matrix2[column_start + (j * size)];
            }

            product[i] = accumulator;

        }


        printf("\nThe product is:\n[");

        for (int i = 0; i < size * size; i++) {

            if (i % size == 0)
                printf("\n");

            printf("%d ", product[i]);
        }
        printf("]\n");


    }

    free(matrix1);
    free(matrix2);
    free(product);

    return 0;
}

