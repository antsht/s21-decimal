#include "s21_decimal.h"

#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  s21_remove_matrix(result);
  result->rows = rows;
  result->columns = columns;
  result->matrix = NULL;
  if (rows < 1 || columns < 1) return ERROR_INCORRECT_MATRIX;
  Matrix_operation_result status = OK;
  result->matrix = (double**)malloc(rows * sizeof(double*));
  if (result->matrix == NULL) status = ERROR_INCORRECT_MATRIX;

  for (int i = 0; i < rows && status == OK; i++) {
    result->matrix[i] = (double*)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) status = ERROR_INCORRECT_MATRIX;
  }
  if (status != OK) s21_remove_matrix(result);
  return status;
}


void s21_print_matrix(matrix_t* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}

bool s21_is_valid_matrix(matrix_t* A) {
  return A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0;
}