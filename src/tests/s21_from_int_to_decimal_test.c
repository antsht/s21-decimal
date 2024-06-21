#include <check.h>

#include "s21_test.h"

START_TEST(s21_from_int_to_decimal_test_1) {
int src_int = 0;
  s21_decimal result = {0};
  int status = 0;
  status = s21_from_int_to_decimal(src_int, &result);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == 0U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (0U << 31));
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
int src_int = 666;
  s21_decimal result = {0};
  int status = 0;
  status = s21_from_int_to_decimal(src_int, &result);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == 666U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (0U << 31));
}
END_TEST


START_TEST(s21_from_int_to_decimal_test_3) {
int src_int = -666;
  s21_decimal result = {0};
  int status = 0;
  status = s21_from_int_to_decimal(src_int, &result);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == 666U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (1U << 31));
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
int src_int = INT_MAX;
  s21_decimal result = {0};
  int status = 0;
  status = s21_from_int_to_decimal(src_int, &result);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == (unsigned int)INT_MAX && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (0U << 31));
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
int src_int = INT_MIN;
  s21_decimal result = {0};
  int status = 0;
  status = s21_from_int_to_decimal(src_int, &result);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == ((unsigned int)INT_MAX)+1 && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (1U << 31));
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  s = suite_create("s21_from_int_to_decimal() tests");
  TCase *tc;
  tc = tcase_create("from_int_to_decimal");
  tcase_add_test(tc, s21_from_int_to_decimal_test_1);
  tcase_add_test(tc, s21_from_int_to_decimal_test_2);
  tcase_add_test(tc, s21_from_int_to_decimal_test_3);
  tcase_add_test(tc, s21_from_int_to_decimal_test_4);
  tcase_add_test(tc, s21_from_int_to_decimal_test_5);
  suite_add_tcase(s, tc);
  return s;
}

int s21_from_int_to_decimal_test(void) {
  Suite *s = s21_from_int_to_decimal_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}