#include <check.h>

#include "s21_test.h"

START_TEST(s21_sandbox_1) {
  s21_decimal dec = {0};
  dec.bits[0] = 1U;
  s21_decimal result = {0};
  int status = 0;
  status = s21_negate(dec, &result);
  s21_print_decimal_as_binary(&dec);
  s21_print_decimal_as_binary(&result);
  set_sign_of_decimal(&result, POSITIVE);
  s21_print_decimal_as_binary(&result);

  set_nth_bit_value(&result, 31, 1);
  set_nth_bit_value(&result, 32, 1);

  set_nth_bit_value(&result, 63, 1);
  set_nth_bit_value(&result, 64, 1);
  set_nth_bit_value(&result, 95, 1);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(1 == 1);
}
END_TEST

Suite *s21_sandbox_suite(void) {
  Suite *s;
  s = suite_create("s21_sandbox()");
  TCase *tc;
  tc = tcase_create("sandbox");
  tcase_add_test(tc, s21_sandbox_1);
  suite_add_tcase(s, tc);
  return s;
}

int s21_sandbox_test(void) {
  Suite *s = s21_sandbox_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}