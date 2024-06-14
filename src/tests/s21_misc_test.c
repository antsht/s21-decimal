#include <check.h>

#include "../s21_matrix.h"
#include "s21_test.h"

START_TEST(s21_print_matrix_test_1) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  s21_print_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert(res == OK);
}
END_TEST

START_TEST(s21_is_valid_matrix_test_1) {
  matrix_t A = {0};
  Matrix_operation_result res = 0;
  res = s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  bool is_valid = s21_is_valid_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert(res == OK && is_valid);
}
END_TEST

START_TEST(s21_is_valid_matrix_test_2) {
  matrix_t A = {0};
  bool is_valid = s21_is_valid_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert(!is_valid);
}
END_TEST

Suite *s21_misc_suite(void) {
  Suite *s;
  s = suite_create("s21_miscellaneous tests");
  TCase *tc;
  tc = tcase_create("miscellaneous");
  tcase_add_test(tc, s21_print_matrix_test_1);
  tcase_add_test(tc, s21_is_valid_matrix_test_1);
  tcase_add_test(tc, s21_is_valid_matrix_test_2);
  suite_add_tcase(s, tc);
  return s;
}

int s21_misc_test(void) {
  Suite *s = s21_misc_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}