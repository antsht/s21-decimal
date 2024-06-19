#include <check.h>

#include "s21_test.h"

START_TEST(s21_negate_test_1) {
  s21_decimal dec = {0};
  dec.bits[0] = 1U;
  s21_decimal result = {0};
  int status = 0;
  status = s21_negate(dec, &result);
  s21_print_decimal_as_binary(&dec);
  s21_print_decimal_as_binary(&result);
  printf("Status: %d\n", status);

  ck_assert(status == OK && result.bits[0] == 1U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (1U << 31));
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  s = suite_create("s21_negate() tests");
  TCase *tc;
  tc = tcase_create("negate");
  tcase_add_test(tc, s21_negate_test_1);
  suite_add_tcase(s, tc);
  return s;
}

int s21_negate_test(void) {
  Suite *s = s21_negate_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}