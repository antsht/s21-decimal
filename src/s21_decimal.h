#ifndef _S21_DECIMAL_H_
#define _S21_DESIMAL_H_

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum {
  OK = 0,
  ERROR_INCORRECT_MATRIX = 1,
  CALCULATION_ERROR = 2
} Matrix_operation_result;

int s21_create_matrix(int rows, int columns, matrix_t *result);

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-7L

void s21_print_matrix(matrix_t *A);

bool s21_is_valid_matrix(matrix_t *A);

#endif