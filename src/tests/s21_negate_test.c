#include <check.h>

#include "s21_test.h"

START_TEST(s21_negate_test_to_neg) {
  s21_decimal dec = {0};
  dec.bits[0] = 1U;
  s21_decimal result = {0};
  int status = 0;
  status = s21_negate(dec, &result);
  ck_assert(status == OK && result.bits[0] == 1U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == (1U << 31));
}
END_TEST

START_TEST(s21_negate_test_to_pos) {
  s21_decimal dec = {0};
  dec.bits[0] = 1U;
  dec.bits[3] = 1U << 31;
  s21_decimal result = {0};
  int status = 0;
  status = s21_negate(dec, &result);
  ck_assert(status == OK && result.bits[0] == 1U && result.bits[1] == 0 &&
            result.bits[2] == 0 && result.bits[3] == 0);
}
END_TEST

START_TEST(s21_negate_test_null) {
  s21_decimal dec = {0};
  int status = s21_negate(dec, NULL);
  ck_assert(status == CALCULATION_ERROR);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  s = suite_create("s21_negate() tests");
  TCase *tc;
  tc = tcase_create("negate");
  tcase_add_test(tc, s21_negate_test_to_neg);
  tcase_add_test(tc, s21_negate_test_to_pos);
  tcase_add_test(tc, s21_negate_test_null);
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