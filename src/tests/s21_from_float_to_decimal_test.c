#include <check.h>

#include "s21_test.h"

#define MAX powl(2.0, 96)

START_TEST(float_0) {
  float src = 0;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0 && dst.bits[1] == 0 && dst.bits[2] == 0 &&
            dst.bits[3] == 0);
}
END_TEST

START_TEST(float_max) {
  float src = MAX;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x20000000 && dst.bits[1] == 0xB392B21A &&
            dst.bits[2] == 0xFFFFFF77 && dst.bits[3] == 0);
}
END_TEST

START_TEST(float_min) {
  float src = -MAX;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x20000000 && dst.bits[1] == 0xB392B21A &&
            dst.bits[2] == 0xFFFFFF77 && dst.bits[3] == 0x80000000);
}
END_TEST

START_TEST(float_too_big) {
  float src = powl(2.0, 97);
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0x0 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_too_small) {
  float src = -powl(2.0, 97);
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0x0 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_near_null_pos) {
  float src = 0.9e-28;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0 && dst.bits[1] == 0 && dst.bits[2] == 0 &&
            dst.bits[3] == 0);
}
END_TEST

START_TEST(float_near_null_neg) {
  float src = -0.9e-28;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0 && dst.bits[1] == 0 && dst.bits[2] == 0 &&
            dst.bits[3] == 0);
}
END_TEST

START_TEST(float_normal_posi) {
  float src = 100;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0xf4240 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x40000);
}
END_TEST

START_TEST(float_normal_neg) {
  float src = -100;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0xf4240 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x80040000);
}
END_TEST

START_TEST(float_NaN) {
  float src = NAN;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0x0 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_pos_infinity) {
  float src = INFINITY;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0x0 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_neg_infinity) {
  float src = -INFINITY;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
  ck_assert(dst.bits[0] == 0x0 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_max_scale) {
  float src = 3e-28;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x3 && dst.bits[1] == 0x0 && dst.bits[2] == 0x0 &&
            dst.bits[3] == 0x1c0000);
}
END_TEST

START_TEST(float_0_123) {
  float src = 0.123;  // 1230000 -7
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12c4b0 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x70000);
}
END_TEST

START_TEST(float_1_23) {
  float src = 1.23;  // 1230000 -6
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12c4b0 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x60000);
}
END_TEST

START_TEST(float_12_3) {
  float src = 12.3;  // 1230000 -5
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12c4b0 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x50000);
}
END_TEST

START_TEST(float_12_0000000003) {
  float src = 12.0000000003;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x124f80 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x50000);
}
END_TEST

START_TEST(float_1234567) {
  float src = 1234567;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12d687 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_123456_7) {
  float src = 123456.7;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12d687 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x10000);
}
END_TEST

START_TEST(float_1234567_5) {
  float src = 1234567.5;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12d688 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_1234567_1) {
  float src = 1234567.2;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x12d687 && dst.bits[1] == 0x0 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x0);
}
END_TEST

START_TEST(float_1234567890123456) {
  float src = 1234567890123456;  // 1234567948140544
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, OK);
  ck_assert(dst.bits[0] == 0x43175000 && dst.bits[1] == 0x462d5 &&
            dst.bits[2] == 0x0 && dst.bits[3] == 0x0);
}
END_TEST

START_TEST(dest_is_null) {
  float src = 123;
  int status = s21_from_float_to_decimal(src, NULL);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
}
END_TEST

START_TEST(float_7_922817e_plus_28) {
  float src = 7.922817e+28;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
}
END_TEST

START_TEST(float_neg_7_922817e_plus_28) {
  float src = -7.922817e+28;
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CONVERTATION_ERROR);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  s = suite_create("s21_from_float_to_decimal() tests");
  TCase *tc;
  tc = tcase_create("from_float_to_decimal");
  tcase_add_test(tc, float_0);
  tcase_add_test(tc, float_max);
  tcase_add_test(tc, float_min);
  tcase_add_test(tc, float_neg_infinity);
  tcase_add_test(tc, float_pos_infinity);
  tcase_add_test(tc, float_NaN);
  tcase_add_test(tc, float_normal_neg);
  tcase_add_test(tc, float_normal_posi);
  tcase_add_test(tc, float_too_big);
  tcase_add_test(tc, float_too_small);
  tcase_add_test(tc, float_max_scale);
  tcase_add_test(tc, float_near_null_pos);
  tcase_add_test(tc, float_near_null_neg);
  tcase_add_test(tc, float_12_0000000003);
  tcase_add_test(tc, float_1_23);
  tcase_add_test(tc, float_0_123);
  tcase_add_test(tc, float_12_3);
  tcase_add_test(tc, float_1234567890123456);
  tcase_add_test(tc, float_1234567_1);
  tcase_add_test(tc, float_1234567_5);
  tcase_add_test(tc, float_1234567);
  tcase_add_test(tc, float_123456_7);
  tcase_add_test(tc, dest_is_null);
  tcase_add_test(tc, float_7_922817e_plus_28);
  tcase_add_test(tc, float_neg_7_922817e_plus_28);

  suite_add_tcase(s, tc);
  return s;
}

int s21_from_float_to_decimal_test(void) {
  Suite *s = s21_from_float_to_decimal_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}