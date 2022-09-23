#include "s21_matrix.h"


int main() {
    matrix_t matrix_1;
    matrix_t matrix_2;
    matrix_t result;
    int n = 1;

    s21_create_matrix(2, 3, &matrix_1);
    s21_create_matrix(2, 2, &matrix_2);

    for (int i = 0; i < matrix_1.rows; i++) {
        for (int j = 0; j < matrix_1.columns; j++) {
            matrix_1.matrix[i][j] = n;
            n++;
        }
    }
    printf("matrix_1: \n");
    print_matrix(&matrix_1);


    for (int i = 0; i < matrix_2.rows; i++) {
        for (int j = 0; j < matrix_2.columns; j++) {
            matrix_2.matrix[i][j] = 2;
        }
    }
    printf("\nmatrix_2: \n");
    print_matrix(&matrix_2);

    // TEST

    // // =
    // printf("\ns21_eq_matrix: %d\n", s21_eq_matrix(&matrix_1, &matrix_2));

    // // +
    // printf("\ns21_sum_matrix: %d\n", s21_sum_matrix(&matrix_1, &matrix_2, &result));
    // printf("result: \n");
    // print_matrix(&result);

    // // -
    // printf("\ns21_sub_matrix: %d\n", s21_sub_matrix(&matrix_1, &matrix_2, &result));
    // printf("result: \n");
    // print_matrix(&result);

    // // * number
    // printf("\ns21_mult_number: %d\n", s21_mult_number(&matrix_1, 2, &result));
    // printf("result: \n");
    // print_matrix(&result);

    // trans
    printf("\ns21_transpose: %d\n", s21_transpose(&matrix_1, &result));
    printf("result: \n");
    print_matrix(&result);


    s21_remove_matrix(&matrix_1);
    s21_remove_matrix(&matrix_2);
    // s21_remove_matrix(&result);
}

void print_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            printf("%lf ", A->matrix[i][j]);
        }
        printf("\n");
    }
}


matrix_t init_struct() {
    matrix_t res = {NULL, 0, 0};
    return res;
}


int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res = INCORR_MATRIX;
    *result = init_struct();

    result->matrix = memory_allocation(rows, columns);
    if (result->matrix != NULL) {
        result->columns = columns;
        result->rows = rows;
        res = OK;
    }

    return res;
}


double **memory_allocation(int rows, int columns) {
    double **arr = (double**) malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++) {
        arr[i] = (double*)malloc(columns * sizeof(double));
    }

    return arr;
}


void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for(int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
    }
    free(A->matrix);
}


int matrix_is_exist(matrix_t *A) {
    // Возвращает 1, если матрица существует 

    return A && A->matrix && A->columns > 0 && A->rows > 0;
}


int size_is_eq(matrix_t *A, matrix_t *B) {
    // Возвращает 1, если размеры матриц одинаковы

    return A->columns == B->columns && A->rows == B->rows;
}


int matrices_exist_and_eq(matrix_t *A, matrix_t *B) {
    // Возвращает 1, если матрицы существуют и их размеры равны

    return matrix_is_exist(A) && matrix_is_exist(B) && size_is_eq(A, B);
}


int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = FAILURE;

    if (matrices_exist_and_eq(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                res = (fabs(A->matrix[i][j] - B->matrix[i][j]) <= EPS) ? SUCCESS : FAILURE;
            }
        }
    }

    return res;
}


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return calc_sum_sub(A, B, result, 1);
}


int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return calc_sum_sub(A, B, result, -1);
}


int calc_sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int factor) {
    // Вычисление суммы и разности, для разности знак меняется с помощью множителя factor

    int res = CALC_ERROR;

    if (matrices_exist_and_eq(A, B)) {
        int rows = A->rows, columns = A->columns;
        s21_create_matrix(rows, columns, result);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * factor);
            }
        }
        res = OK;
    }

    return res;
}


int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    // Умножение матрицы на число

    int res = CALC_ERROR;

    if (matrix_is_exist(A)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        res = OK;
    }

    return res;
}


// int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){

// }


int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = CALC_ERROR;

    if (matrix_is_exist(A)) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
        res = OK;
    }

    return res;
}


// int s21_calc_complements(matrix_t *A, matrix_t *result);
// int s21_determinant(matrix_t *A, double *result);
// int s21_inverse_matrix(matrix_t *A, matrix_t *result);



