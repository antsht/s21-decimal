#include <check.h>

#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(s21_create_matrix_test_1) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(1, 1, &A);
  ck_assert(res == OK && A.rows == 1 && A.columns == 1 && A.matrix != NULL);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(10000, 10000, &A);
  ck_assert(res == OK && A.rows == 10000 && A.columns == 10000 &&
            A.matrix != NULL);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_3) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(0, 0, &A);
  ck_assert(res == ERROR_INCORRECT_MATRIX && A.matrix == NULL);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_4) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(-1, -1, &A);
  ck_assert(res == ERROR_INCORRECT_MATRIX && A.matrix == NULL);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s;
  s = suite_create("s21_create_matrix() tests");
  TCase *tc;
  tc = tcase_create("create_matrix");
  tcase_add_test(tc, s21_create_matrix_test_1);
  tcase_add_test(tc, s21_create_matrix_test_2);
  tcase_add_test(tc, s21_create_matrix_test_3);
  tcase_add_test(tc, s21_create_matrix_test_4);
  suite_add_tcase(s, tc);
  return s;
}

int s21_create_matrix_test(void) {
  Suite *s = s21_create_matrix_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}