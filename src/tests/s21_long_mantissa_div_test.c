#include <check.h>

#include "s21_test.h"

START_TEST(case_NULL_ref_result) {
  s21_long_decimal num_1 = {
      {4294967295, 4294967295, 4294967295, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  int return_s21 = s21_long_mantissa_div(num_1, num_2, NULL, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_0_by_0) {
  s21_long_decimal num_1 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  ck_assert_int_eq(return_s21, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(case_MAX_by_0) {
  s21_long_decimal num_1 = {
      {4294967295, 4294967295, 4294967295, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  ck_assert_int_eq(return_s21, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(case_0_by_MAX) {
  s21_long_decimal num_1 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {
      {4294967295, 4294967295, 4294967295, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_255_by_5) {
  s21_long_decimal num_1 = {{255, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{5, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{51, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_1) {
  s21_long_decimal num_1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_10) {
  s21_long_decimal num_1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_1000000) {
  s21_long_decimal num_1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1000000, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_by_4) {
  s21_long_decimal num_1 = {
      {4294967295, 4294967295, 4294967295, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{4, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {
      {4294967295, 4294967295, 1073741823, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{3, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_minus_3_by_4) {
  s21_long_decimal num_1 = {
      {4294967292, 4294967295, 4294967295, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{4, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {
      {4294967295, 4294967295, 1073741823, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_3) {
  s21_long_decimal num_1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{3, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_by_2) {
  s21_long_decimal num_1 = {{123, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{2, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_res = {{61, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal orig_remainder = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal s21_remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int return_s21 =
      s21_long_mantissa_div(num_1, num_2, &s21_res, &s21_remainder);
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(s21_res.bits[i], orig_res.bits[i]);
    ck_assert_int_eq(s21_remainder.bits[i], orig_remainder.bits[i]);
  }
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

Suite *s21_long_mantissa_div_suite(void) {
  Suite *s;
  s = suite_create("s21_long_mantissa_div() tests");
  TCase *tc;
  tc = tcase_create("div");
  tcase_add_test(tc, case_NULL_ref_result);
  tcase_add_test(tc, case_0_by_0);
  tcase_add_test(tc, case_MAX_by_0);
  tcase_add_test(tc, case_0_by_MAX);
  tcase_add_test(tc, case_255_by_5);
  tcase_add_test(tc, case_1_by_1);
  tcase_add_test(tc, case_1_by_10);
  tcase_add_test(tc, case_1_by_1000000);
  tcase_add_test(tc, case_MAX_by_4);
  tcase_add_test(tc, case_MAX_minus_3_by_4);
  tcase_add_test(tc, case_1_by_3);
  tcase_add_test(tc, case_123_by_2);

  suite_add_tcase(s, tc);
  return s;
}

int s21_long_mantissa_div_test(void) {
  Suite *s = s21_long_mantissa_div_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}