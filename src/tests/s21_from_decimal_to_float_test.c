#include <check.h>

#include "s21_test.h"

#define MAX 79228162514264337593543950335.0

START_TEST(dec_plus_0) {
  float dst = -1;
  s21_decimal src = {0};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(dec_minus_0) {
  float dst = -1;
  s21_decimal src = {{0x0, 0x0, 0x0, 0x80000000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(dec_max) {
  float dst = -1;
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, MAX);
}
END_TEST

START_TEST(dec_min) {
  float dst = -1;
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, -MAX);
}
END_TEST

START_TEST(dec_normal_value_positive) {
  float dst = -1;
  s21_decimal src = {{0x64, 0x0, 0x0, 0x0}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, 100);
}
END_TEST

START_TEST(dec_normal_value_negative) {
  float dst = -1;
  s21_decimal src = {{0x64, 0x0, 0x0, 0x80000000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, -100);
}
END_TEST

START_TEST(dec_max_scale_posi) {
  float dst = -1;
  s21_decimal src = {{1, 0x0, 0x0, 0x1c0000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, 1e-28);
}
END_TEST

START_TEST(dec_max_scale_neg) {
  float dst = -1;
  s21_decimal src = {{1, 0x0, 0x0, 0x801c0000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, -1e-28);
}
END_TEST

START_TEST(dec_normal_scale) {
  float dst = -1;
  s21_decimal src = {{1234, 0x0, 0x0, 0x30000}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert_float_eq(dst, 1.234);
}
END_TEST

START_TEST(dec_null) {
  s21_decimal src = {{1234, 0x0, 0x0, 0x30000}};
  int status = s21_from_decimal_to_float(src, NULL);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
}
END_TEST

START_TEST(wrong_dec) {
  float dst = -1;
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int status = s21_from_decimal_to_float(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s;
  s = suite_create("s21_from_decimal_to_float_test");
  TCase *tc;
  tc = tcase_create("from_decimal_to_float");
  tcase_add_test(tc, dec_plus_0);
  tcase_add_test(tc, dec_minus_0);
  tcase_add_test(tc, dec_max);
  tcase_add_test(tc, dec_min);
  tcase_add_test(tc, dec_normal_value_positive);
  tcase_add_test(tc, dec_normal_value_negative);
  tcase_add_test(tc, dec_max_scale_posi);
  tcase_add_test(tc, dec_max_scale_neg);
  tcase_add_test(tc, dec_normal_scale);
  tcase_add_test(tc, dec_null);
  tcase_add_test(tc, wrong_dec);

  suite_add_tcase(s, tc);
  return s;
}

int s21_from_decimal_to_float_test(void) {
  Suite *s = s21_from_decimal_to_float_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}