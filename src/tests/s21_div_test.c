#include <check.h>

#include "s21_test.h"

START_TEST(case_NULL_ref_result) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int return_s21 = s21_div(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_long_NULL_ref_result) {
  s21_long_decimal num_1 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal remainder = {0};
  int return_s21 = s21_long_mantissa_div(num_1, num_2, NULL, &remainder);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_long_NULL_ref_remainder) {
  s21_long_decimal num_1 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal res = {0};
  int return_s21 = s21_long_mantissa_div(num_1, num_2, &res, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_0_by_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(case_MAX_by_0) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(case_MIN_by_0) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(case_0_by_MAX) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_by_MIN) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_255_by_5) {
  s21_decimal num_1 = {{255, 0, 0, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 0}};
  s21_decimal orig_res = {{51, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_by_1_e_minus_28) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_1) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal orig_res = {{1, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_minus_1) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2147483648}};
  s21_decimal orig_res = {{1, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1_by_minus_1) {
  s21_decimal num_1 = {{1, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 2147483648}};
  s21_decimal orig_res = {{1, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_10) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal orig_res = {{1, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_1000000) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{1000000, 0, 0, 0}};
  s21_decimal orig_res = {{1, 0, 0, 393216}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_minus_1_by_2) {
  s21_decimal num_1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal orig_res = {{4294967295, 4294967295, 2147483647, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_by_4) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 1073741824, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1_by_3) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal orig_res = {{89478485, 347537611, 180700362, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_by_2) {
  s21_decimal num_1 = {{123, 0, 0, 0}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal orig_res = {{615, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_12345678_9_by_12345678_9) {
  s21_decimal num_1 = {{123456789, 0, 0, 65536}};
  s21_decimal num_2 = {{123456789, 0, 0, 65536}};
  s21_decimal orig_res = {{1, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_12345678_9123456789_by_2) {
  s21_decimal num_1 = {{2899336981, 28744523, 0, 655360}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal orig_res = {{1611783017, 143722618, 0, 720896}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123456789_by_0_00000000000000001) {
  s21_decimal num_1 = {{123456789, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1114112}};
  s21_decimal orig_res = {{777125888, 2552110037, 669260, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_by_0_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(return_s21, INF_PLUS);
}
END_TEST

START_TEST(case_MIN_by_0_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_by_minus_0_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MIN_by_minus_0_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);

  ck_assert_int_eq(return_s21, INF_PLUS);
}
END_TEST

START_TEST(case_0_123456789_by_10) {
  s21_decimal num_1 = {{123456789, 0, 0, 589824}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal orig_res = {{123456789, 0, 0, 655360}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_for_check) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2149318656}};
  s21_decimal num_2 = {{4, 0, 0, 917504}};
  s21_decimal orig_res = {{0, 0, 1073741824, 2148401152}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(s21_div_neg_0_00879_by_0_123456) {
  s21_decimal num_1 = {{879, 0, 0, 2147811328}};
  s21_decimal num_2 = {{123456, 0, 0, 393216}};
  s21_decimal orig_res = {{284834337, 1125849195, 38597302, 2149318656}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_div(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s;
  s = suite_create("s21_div() tests");
  TCase *tc;
  tc = tcase_create("div");
  tcase_add_test(tc, case_NULL_ref_result);
  tcase_add_test(tc, case_long_NULL_ref_result);
  tcase_add_test(tc, case_long_NULL_ref_remainder);
  tcase_add_test(tc, case_0_by_0);
  tcase_add_test(tc, case_MAX_by_0);
  tcase_add_test(tc, case_MIN_by_0);
  tcase_add_test(tc, case_0_by_MAX);
  tcase_add_test(tc, case_0_by_MIN);
  tcase_add_test(tc, case_minus_255_by_5);
  tcase_add_test(tc, case_0_by_1_e_minus_28);
  tcase_add_test(tc, case_1_by_1);
  tcase_add_test(tc, case_1_by_minus_1);
  tcase_add_test(tc, case_minus_1_by_minus_1);
  tcase_add_test(tc, case_1_by_10);
  tcase_add_test(tc, case_1_by_1000000);
  tcase_add_test(tc, case_MAX_minus_1_by_2);
  tcase_add_test(tc, case_MAX_by_4);
  tcase_add_test(tc, case_1_by_3);
  tcase_add_test(tc, case_123_by_2);
  tcase_add_test(tc, case_12345678_9_by_12345678_9);
  tcase_add_test(tc, case_12345678_9123456789_by_2);
  tcase_add_test(tc, case_123456789_by_0_00000000000000001);
  tcase_add_test(tc, case_MAX_by_0_1);
  tcase_add_test(tc, case_MAX_by_minus_0_1);
  tcase_add_test(tc, case_MIN_by_0_1);
  tcase_add_test(tc, case_MIN_by_minus_0_1);
  tcase_add_test(tc, case_0_123456789_by_10);
  tcase_add_test(tc, case_for_check);
  tcase_add_test(tc, s21_div_neg_0_00879_by_0_123456);

  suite_add_tcase(s, tc);
  return s;
}

int s21_div_test(void) {
  Suite *s = s21_div_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}