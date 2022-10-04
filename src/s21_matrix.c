#include "s21_matrix.h"

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

    if (rows > 0 && columns > 0) {
        result->matrix = memory_allocation(rows, columns);
        if (result->matrix != NULL) {
            result->columns = columns;
            result->rows = rows;
            res = OK;
        }
    }


    return res;
}


double **memory_allocation(int rows, int columns) {
    double **arr = (double**) calloc(rows, rows * sizeof(double*));

    for (int i = 0; i < rows; i++) {
        arr[i] = (double*)calloc(columns, columns * sizeof(double));
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

    *A = init_struct();
}


int matrix_is_exist(matrix_t *A) {
    // Возвращает 1, если матрица существует 

    return A && A->matrix && A->columns > 0 && A->rows > 0;
}


int size_is_eq(matrix_t *A, matrix_t *B) {
    // Возвращает 1, если размеры матриц одинаковы

    return (A->columns == B->columns) && (A->rows == B->rows);
}


int matrices_exist_and_eq(matrix_t *A, matrix_t *B) {
    return matrix_is_exist(A) && matrix_is_exist(B) && size_is_eq(A, B);
}


int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = SUCCESS;

    if (matrices_exist_and_eq(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
                    res = FAILURE;
                    break;
                }
            }
            if (res == FAILURE) break;
        }
    } else {
        res = FAILURE;
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
    *result = init_struct();

    if (matrix_is_exist(A) && matrix_is_exist(B)) {
        if (size_is_eq(A, B)) {
            int rows = A->rows, columns = A->columns;
            s21_create_matrix(rows, columns, result);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * factor);
                }
            }
            res = OK;
        }
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    // Умножение матрицы на число

    int res = CALC_ERROR;
    *result = init_struct();

    if (matrix_is_exist(A)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        res = OK;
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    int res = CALC_ERROR;
    *result = init_struct();

    if (matrix_is_exist(A) && matrix_is_exist(B)) {
        if (A->columns == B->rows) {
            res = OK;
            mult_matrix(A, B, result);
        }
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


void mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            for (int m = 0; m < A->columns; m++) {
                result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
            }
        }
    }
}


int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = CALC_ERROR;
    *result = init_struct();

    if (matrix_is_exist(A)) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
        res = OK;
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int res = CALC_ERROR;
    *result = init_struct();

    if (matrix_is_exist(A)) {
        if (matrix_is_square(A)) {
            if (!s21_create_matrix(A->rows, A->columns, result)) {
                res = OK;
                calc_complements(A, result);
                if (A->rows == 1) {
                    result->matrix[0][0] = 1.;
                }
            }
        }
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


void calc_complements(matrix_t *A, matrix_t *result) {
    matrix_t mini_matrix;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            get_mini_matrix(A, &mini_matrix, i, j);
            s21_determinant(&mini_matrix, &result->matrix[i][j]);
            result->matrix[i][j] = result->matrix[i][j] * pow(-1, i + j);
            s21_remove_matrix(&mini_matrix);
        }
    }
}


void get_mini_matrix(matrix_t *A, matrix_t *result, int row, int column) {
    // Функция для получения матрицы с вычеркнутыми строками и столбцами

    int offset_row = 0, offset_col = 0;

    s21_create_matrix(A->rows - 1, A->columns - 1, result);

    for (int i = 0; i < result->rows; i++) {
        if (i == row) {
            offset_row = 1;
        }
        offset_col = 0;
        for (int j = 0; j < result->columns; j++) {
            if (j == column) {
                offset_col = 1;
            }
            result->matrix[i][j] = A->matrix[i + offset_row][j + offset_col];
        }
    }
}


double second_order_determinant(matrix_t *A) {
    // Определитель второго порядка (на вход матрица 2х2)
    // printf("\n%lf * %lf - %lf * %lf\n", A->matrix[0][0], A->matrix[1][1], A->matrix[0][1], A->matrix[1][0]);
    return A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
}


int matrix_is_square(matrix_t *A) {
    //  Возвращает 1, если матрциа квадратная 

    return (A->columns == A->rows);
}


int s21_determinant(matrix_t *A, double *result) {
    int res = CALC_ERROR;
    *result = 0;

    if (matrix_is_exist(A)) {
        if (matrix_is_square(A)) {
            *result = calc_determinant(A, A->columns);
            res = OK;
        } 
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}


double calc_determinant (matrix_t *A, int size) {
    double det = 0;
    int degree = 1;
    matrix_t mini_matrix = init_struct(); 

    if (size == 1) {
        det = A->matrix[0][0];
    } else if (size == 2) {
        det = second_order_determinant(A);
    } else {
        for (int col = 0; col < size; col++) {
            get_mini_matrix(A, &mini_matrix, 0, col);
            det = det + (degree * A->matrix[0][col] * calc_determinant(&mini_matrix, size - 1));
            degree = -degree;
        }
        s21_remove_matrix(&mini_matrix);
    }

    return det;
}


int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = CALC_ERROR;
    double det = 0;
    matrix_t tmp;
    matrix_t tmp1;
    *result = init_struct();

    if (matrix_is_exist(A)) {
        s21_determinant(A, &det);
        if (matrix_is_square(A) && det != 0) {
            res = OK;
            s21_calc_complements(A, &tmp);
            s21_transpose(&tmp, &tmp1);
            s21_mult_number(&tmp1, 1/det, result);
        }
    } else {
        res = INCORR_MATRIX;
    }

    return res;
}

