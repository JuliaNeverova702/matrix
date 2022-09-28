#include "s21_matrix.h"


int main() {
    matrix_t matrix_1;
    matrix_t matrix_2;
    matrix_t result;
    int n = 1, m = 1;

    s21_create_matrix(5, 5, &matrix_1);
    s21_create_matrix(3, 2, &matrix_2);

    for (int i = 0; i < matrix_1.rows; i++) {
        for (int j = 0; j < matrix_1.columns; j++) {
            matrix_1.matrix[i][j] = n;
            n++;
        }
    }
    printf("matrix_1: \n");
    print_matrix(&matrix_1);


    // for (int i = 0; i < matrix_2.rows; i++) {
    //     for (int j = 0; j < matrix_2.columns; j++) {
    //         matrix_2.matrix[i][j] = m;
    //         m++;
    //     }
    // }
    // printf("\nmatrix_2: \n");
    // print_matrix(&matrix_2);

    get_mini_matrix(&matrix_1, &result, 1, 1);
    printf("\nresult: \n");
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

    *A = init_struct();
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


int s21_calc_complements(matrix_t *A, matrix_t *result) {

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


int second_order_determinant(matrix_t *A) {
    // Определитель второго порядка (на вход матрица 2х2)

    return A->matrix[1][1] * A->matrix[2][2] - A->matrix[1][2] * A->matrix[2][1];
}


int matrix_is_square(matrix_t *A) {
    //  Возвращает 1, если матрциа квадратная и существует

    return matrix_is_exist(A) && A->columns == A->columns;
}


void matrix_of_minors(matrix_t *A, matrix_t *result) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                get_mini_matrix(A, )
            }
        }
    
}


int s21_determinant(matrix_t *A, double *result) {
    if (matrix_is_square) {
}
