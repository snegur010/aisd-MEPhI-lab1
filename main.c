#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {
    int rows = 0;

    printf("Enter the number of rows in the matrix: ");
    if (getPositiveInteger(&rows) == 1 || rows == 0) {
        printf("Неудачная попытка создания матрицы\n\n");
        return 1;
    }

    Matrix *matrix = Matrix_create(rows);
    if (matrix == NULL) {
        return 1;
    }

    int check = readMatrix(rows, matrix);
    if (check == 1) {
        Matrix_free(matrix);
        return 1;
    }

    printf("\nMATRIX:\n");
    Matrix_print(matrix);

    Matrix *new_matrix = Matrix_create(rows);
    if (new_matrix == NULL) {
        Matrix_free(matrix);
        return 1;
    }

    check = individual(matrix, new_matrix);
    if (check == 1) {
        Matrix_free(matrix);
        Matrix_free(new_matrix);
        return 1;
    }
    printf("\nNEW MATRIX:\n");
    Matrix_print(new_matrix);
    printf("\n");

    Matrix_free(matrix);
    Matrix_free(new_matrix);

    return 0;
}

