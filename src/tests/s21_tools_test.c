#include <check.h>

#include "s21_test.h"

START_TEST(s21_tools_s21_get_nth_bit_value_n_overflow) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int n = 99;
  int res = 0;
  int return_s21 = s21_get_nth_bit_value(&dec, n, &res);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_nth_bit_value_NULL) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int n = 15;
  int return_s21 = s21_get_nth_bit_value(&dec, n, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_nth_bit_value_n_overflow) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int n = 99;
  int return_s21 = s21_set_nth_bit_value(&dec, n, 1);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_nth_bit_value_NULL) {
  int n = 15;
  int return_s21 = s21_set_nth_bit_value(NULL, n, 1);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_nth_bit_value_wrong_value) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int n = 15;
  int return_s21 = s21_set_nth_bit_value(&dec, n, 5);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_sign_of_decimal_sign_NULL) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int return_s21 = s21_get_sign_of_decimal(&dec, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_sign_of_decimal_value_NULL) {
  int sign = 0;
  int return_s21 = s21_get_sign_of_decimal(NULL, &sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_sign_of_decimal_value_NULL) {
  int sign = POSITIVE;
  int return_s21 = s21_set_sign_of_decimal(NULL, sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_sign_of_decimal_wrong_sign) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int sign = 2;
  int return_s21 = s21_set_sign_of_decimal(&dec, sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_scale_of_decimal_scale_NULL) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int return_s21 = s21_get_scale_of_decimal(&dec, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_scale_of_decimal_value_NULL) {
  int scale = 0;
  int return_s21 = s21_get_scale_of_decimal(NULL, &scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_scale_of_decimal_value_NULL) {
  int scale = 15;
  int return_s21 = s21_set_scale_of_decimal(NULL, scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_scale_of_decimal_wrong_scale) {
  s21_decimal dec = {{123, 123, 123, 0}};
  int scale = -1;
  int return_s21 = s21_set_scale_of_decimal(&dec, scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_sign_of_long_decimal_sign_NULL) {
  s21_long_decimal dec = {{123, 123, 123, 0, 0, 0, 0, 0}};
  int return_s21 = s21_get_sign_of_long_decimal(&dec, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_sign_of_long_decimal_value_NULL) {
  int sign = 0;
  int return_s21 = s21_get_sign_of_long_decimal(NULL, &sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_sign_of_long_decimal_value_NULL) {
  int sign = POSITIVE;
  int return_s21 = s21_set_sign_of_long_decimal(NULL, sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_sign_of_long_decimal_wrong_sign) {
  s21_long_decimal dec = {{123, 123, 123, 0, 0, 0, 0, 0}};
  int sign = 2;
  int return_s21 = s21_set_sign_of_long_decimal(&dec, sign);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_scale_of_long_decimal_scale_NULL) {
  s21_long_decimal dec = {{123, 123, 123, 0, 0, 0, 0, 0}};
  int return_s21 = s21_get_scale_of_long_decimal(&dec, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_get_scale_of_long_decimal_value_NULL) {
  int scale = 0;
  int return_s21 = s21_get_scale_of_long_decimal(NULL, &scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_scale_of_long_decimal_value_NULL) {
  int scale = 15;
  int return_s21 = s21_set_scale_of_long_decimal(NULL, scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_set_scale_of_long_decimal_wrong_scale) {
  s21_long_decimal dec = {{123, 123, 123, 0, 0, 0, 0, 0}};
  int scale = -1;
  int return_s21 = s21_set_scale_of_long_decimal(&dec, scale);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_left_shift_long_decimal_NULL) {
  int return_s21 = s21_left_shift_long_decimal(NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_left_shift_long_decimal_overleft) {
  s21_long_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                           0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int return_s21 = s21_left_shift_long_decimal(&dec);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_left_n_shift_long_decimal_NULL) {
  int return_s21 = s21_left_n_shift_long_decimal(NULL, 5);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_tools_s21_left_n_shift_long_decimal_overleft) {
  s21_long_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                           0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int return_s21 = s21_left_n_shift_long_decimal(&dec, 16);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

Suite *s21_tools_suite(void) {
  Suite *s;
  s = suite_create("s21_tools() tests");
  TCase *tc;
  tc = tcase_create("tools");
  tcase_add_test(tc, s21_tools_s21_get_nth_bit_value_n_overflow);
  tcase_add_test(tc, s21_tools_s21_get_nth_bit_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_nth_bit_value_n_overflow);
  tcase_add_test(tc, s21_tools_s21_set_nth_bit_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_nth_bit_value_wrong_value);
  tcase_add_test(tc, s21_tools_s21_get_sign_of_decimal_sign_NULL);
  tcase_add_test(tc, s21_tools_s21_get_sign_of_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_sign_of_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_sign_of_decimal_wrong_sign);
  tcase_add_test(tc, s21_tools_s21_get_scale_of_decimal_scale_NULL);
  tcase_add_test(tc, s21_tools_s21_get_scale_of_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_scale_of_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_scale_of_decimal_wrong_scale);
  tcase_add_test(tc, s21_tools_s21_get_sign_of_long_decimal_sign_NULL);
  tcase_add_test(tc, s21_tools_s21_get_sign_of_long_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_sign_of_long_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_sign_of_long_decimal_wrong_sign);
  tcase_add_test(tc, s21_tools_s21_get_scale_of_long_decimal_scale_NULL);
  tcase_add_test(tc, s21_tools_s21_get_scale_of_long_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_scale_of_long_decimal_value_NULL);
  tcase_add_test(tc, s21_tools_s21_set_scale_of_long_decimal_wrong_scale);
  tcase_add_test(tc, s21_tools_s21_left_shift_long_decimal_NULL);
  tcase_add_test(tc, s21_tools_s21_left_shift_long_decimal_overleft);
  tcase_add_test(tc, s21_tools_s21_left_n_shift_long_decimal_NULL);
  tcase_add_test(tc, s21_tools_s21_left_n_shift_long_decimal_overleft);
  suite_add_tcase(s, tc);
  return s;
}

int s21_tools_test(void) {
  Suite *s = s21_tools_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}