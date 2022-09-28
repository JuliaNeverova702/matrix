#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORR_MATRIX 1
#define CALC_ERROR 2

#define EPS 1e-6


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void print_matrix(matrix_t *A);

double **memory_allocation(int rows, int columns);
int calc_sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int factor);
int size_is_eq(matrix_t *A, matrix_t *B);
int matrix_is_exist(matrix_t *A);
int matrices_exist_and_eq(matrix_t *A, matrix_t *B);
void mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int second_order_determinant(matrix_t *A);
void get_mini_matrix(matrix_t *A, matrix_t *result, int row, int column);
int matrix_is_square (matrix_t *A);