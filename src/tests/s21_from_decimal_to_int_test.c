#include <check.h>

#include "s21_test.h"

START_TEST(s21_from_decimal_to_int_test_1) {
  s21_decimal test_decimal = {0};
  int test_int = 0;
  int result = 0;

  s21_from_int_to_decimal(12345678, &test_decimal);
  s21_set_scale_of_decimal(&test_decimal, 2);
  result = s21_from_decimal_to_int(test_decimal, &test_int);

  ck_assert(result == OK && test_int == 123456);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  s21_decimal test_decimal = {0};
  int test_int = 0;
  int result = 0;

  s21_from_int_to_decimal(12345678, &test_decimal);
  s21_set_scale_of_decimal(&test_decimal, 2);
  s21_negate(test_decimal, &test_decimal);
  result = s21_from_decimal_to_int(test_decimal, &test_int);

  ck_assert(result == OK && test_int == -123456);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  s21_decimal test_decimal = {{2147483647, 2147483647, 2147483647, 0}};
  int test_int = 0;
  int result = 0;

  result = s21_from_decimal_to_int(test_decimal, &test_int);

  ck_assert(result == CONVERTATION_ERROR && test_int == 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  s21_decimal test_decimal = {0};
  int test_int = 0;
  int result = 0;

  s21_from_int_to_decimal(12345678, &test_decimal);
  result = s21_from_decimal_to_int(test_decimal, &test_int);

  ck_assert(result == OK && test_int == 12345678);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
  s21_decimal test_decimal = {0};
  int test_int = 0;
  int result = 0;

  s21_from_int_to_decimal(-12345678, &test_decimal);
  result = s21_from_decimal_to_int(test_decimal, &test_int);

  ck_assert(result == OK && test_int == -12345678);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;
  s = suite_create("s21_from_decimal_to_int() tests");
  TCase *tc;
  tc = tcase_create("from_decimal_to_int");
  tcase_add_test(tc, s21_from_decimal_to_int_test_1);
  tcase_add_test(tc, s21_from_decimal_to_int_test_2);
  tcase_add_test(tc, s21_from_decimal_to_int_test_3);
  tcase_add_test(tc, s21_from_decimal_to_int_test_4);
  tcase_add_test(tc, s21_from_decimal_to_int_test_5);
  suite_add_tcase(s, tc);
  return s;
}

int s21_from_decimal_to_int_test(void) {
  Suite *s = s21_from_decimal_to_int_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}