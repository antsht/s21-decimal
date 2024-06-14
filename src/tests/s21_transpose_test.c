#include <check.h>

#include "../s21_matrix.h"
#include "s21_test.h"
START_TEST(s21_transpose_test_1) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;
  matrix_t expected = {0};
  s21_create_matrix(1, 1, &expected);
  expected.matrix[0][0] = 1;
  matrix_t result = {0};
  Matrix_operation_result res = 0;
  res = s21_transpose(&A, &result);
  int comp_res = s21_eq_matrix(&expected, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  ck_assert(res == OK && comp_res == SUCCESS);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 4;
  matrix_t result = {0};
  Matrix_operation_result res = 0;
  res = s21_transpose(&A, &result);
  int comp_res = s21_eq_matrix(&expected, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  ck_assert(res == OK && comp_res == SUCCESS);
}
END_TEST

START_TEST(s21_transpose_test_3) {
  matrix_t A = {0};
  s21_create_matrix(2, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[1][3] = 8;

  matrix_t expected = {0};
  s21_create_matrix(4, 2, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 5;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 6;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 7;
  expected.matrix[3][0] = 4;
  expected.matrix[3][1] = 8;
  matrix_t result = {0};
  Matrix_operation_result res = 0;
  res = s21_transpose(&A, &result);
  int comp_res = s21_eq_matrix(&expected, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  ck_assert(res == OK && comp_res == SUCCESS);
}
END_TEST

START_TEST(s21_transpose_test_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.columns = -1;
  matrix_t result = {0};
  Matrix_operation_result res = 0;
  res = s21_transpose(&A, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  ck_assert(res == ERROR_INCORRECT_MATRIX);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s;
  s = suite_create("s21_transpose() tests");
  TCase *tc;
  tc = tcase_create("transpose");
  tcase_add_test(tc, s21_transpose_test_1);
  tcase_add_test(tc, s21_transpose_test_2);
  tcase_add_test(tc, s21_transpose_test_3);
  tcase_add_test(tc, s21_transpose_test_4);
  suite_add_tcase(s, tc);
  return s;
}

int s21_transpose_test(void) {
  Suite *s = s21_transpose_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}