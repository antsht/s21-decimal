#include <check.h>

#include "s21_test.h"

START_TEST(case_NULL_result) {
  s21_decimal num_1 = {{1, 2, 3, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int return_s21 = s21_sub(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_long_NULL_result) {
  s21_long_decimal num_1 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  int return_s21 = s21_long_mantissa_sub(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_0_sub_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_sub_minus_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_sub_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_2, num_1, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_sub_0) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_0) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[1], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[2], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[3], 0x80000000);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_sub_MAX) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_sub_MIN) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_2, num_1, &s21_res);
  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_sub_MIN) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_PLUS);
}
END_TEST

START_TEST(case_MAX_sub_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_MIN) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};  //! 0?
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_sub_minus_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_PLUS);
}
END_TEST

START_TEST(case_MIN_sub_0_5) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_sub_minus_05) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{5, 0, 0, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_MAX_sub_0_6) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal orig_res = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_minus_0_6) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{6, 0, 0, 2147549184}};
  s21_decimal orig_res = {{4294967294, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_sub_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{0, 0, 0, 1835008}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1e_28_sub_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 2149318656}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{2, 0, 0, 2149318656}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_sub_minus_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 2149318656}};
  s21_decimal orig_res = {{2, 0, 0, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_sub_123) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{123, 0, 0, 0}};
  s21_decimal orig_res = {{2348810240, 337520979, 666784336, 2149187584}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_sub_1e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_sub_minus_5e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 2149318656}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_sub_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_sub_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_sub_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{2469135780, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_sub_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{2469135780, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_sub_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{0, 0, 0, 458752}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_sub_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_sub_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_sub_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_123_4567890_sub_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_sub_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_sub_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_555_sub_0_005) {
  s21_decimal num_1 = {{555, 0, 0, 196608}};
  s21_decimal num_2 = {{5, 0, 0, 196608}};
  s21_decimal orig_res = {{550, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_005_sub_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 2147680256}};
  s21_decimal num_2 = {{555, 0, 0, 196608}};
  s21_decimal orig_res = {{560, 0, 0, 2147680256}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_005_sub_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 196608}};
  s21_decimal num_2 = {{555, 0, 0, 2147680256}};
  s21_decimal orig_res = {{560, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_005_sub_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 2147680256}};
  s21_decimal num_2 = {{555, 0, 0, 2147680256}};
  s21_decimal orig_res = {{550, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_9_9_sub_0_0_1) {
  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{268435454, 1042612833, 542101086, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_999999999999999999999999999_sub_1) {
  s21_decimal num_1 = {{3892314111, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal orig_res = {{3892314110, 2681241660, 54210108, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1000000000000000000000000000_sub_0_1) {
  s21_decimal num_1 = {{3892314112, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal orig_res = {{268435455, 1042612833, 542101086, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1000000000000000000000000000_sub_0_0_1) {
  s21_decimal num_1 = {{3892314112, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{268435456, 1042612833, 542101086, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_sub(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s;
  s = suite_create("s21_sub() tests");
  TCase *tc;
  tc = tcase_create("sub");
  tcase_add_test(tc, case_NULL_result);
  tcase_add_test(tc, case_long_NULL_result);
  tcase_add_test(tc, case_0_sub_0);
  tcase_add_test(tc, case_0_sub_minus_0);
  tcase_add_test(tc, case_minus_0_sub_0);
  tcase_add_test(tc, case_MAX_sub_0);
  tcase_add_test(tc, case_MIN_sub_0);
  tcase_add_test(tc, case_0_sub_MAX);
  tcase_add_test(tc, case_0_sub_MIN);
  tcase_add_test(tc, case_MAX_sub_MIN);
  tcase_add_test(tc, case_MIN_sub_MAX);
  tcase_add_test(tc, case_MAX_sub_MAX);
  tcase_add_test(tc, case_MIN_sub_MIN);
  tcase_add_test(tc, case_MIN_sub_MIN);
  tcase_add_test(tc, case_MIN_sub_1);
  tcase_add_test(tc, case_MAX_sub_minus_1);
  tcase_add_test(tc, case_MAX_sub_minus_05);
  tcase_add_test(tc, case_MIN_sub_0_5);
  tcase_add_test(tc, case_MAX_sub_0_6);
  tcase_add_test(tc, case_MIN_sub_minus_0_6);
  tcase_add_test(tc, case_1e_28_sub_1e_28);
  tcase_add_test(tc, case_minus_1e_28_sub_1e_28);
  tcase_add_test(tc, case_1e_28_sub_minus_1e_28);
  tcase_add_test(tc, case_1e_28_sub_123);
  tcase_add_test(tc, case_MAX_sub_1e_28);
  tcase_add_test(tc, case_MIN_sub_minus_5e_28);
  tcase_add_test(tc, case_1234567890_sub_1234567890);
  tcase_add_test(tc, case_minus_1234567890_sub_minus_1234567890);
  tcase_add_test(tc, case_minus_1234567890_sub_1234567890);
  tcase_add_test(tc, case_1234567890_sub_minus_1234567890);
  tcase_add_test(tc, case_123_4567890_sub_123_4567890);
  tcase_add_test(tc, case_1234567890_sub_123_4567890);
  tcase_add_test(tc, case_minus_1234567890_sub_123_4567890);
  tcase_add_test(tc, case_1234567890_sub_minus_123_4567890);
  tcase_add_test(tc, case_minus_123_4567890_sub_minus_1234567890);
  tcase_add_test(tc, case_minus_1234567890_sub_minus_123_4567890);
  tcase_add_test(tc, case_123_4567890_sub_1234567890);
  tcase_add_test(tc, case_0_555_sub_0_005);
  tcase_add_test(tc, case_minus_0_005_sub_0_555);
  tcase_add_test(tc, case_0_005_sub_minus_0_555);
  tcase_add_test(tc, case_minus_0_005_sub_minus_0_555);
  tcase_add_test(tc, case_0_9_9_sub_0_0_1);
  tcase_add_test(tc, case_999999999999999999999999999_sub_1);
  tcase_add_test(tc, case_1000000000000000000000000000_sub_0_1);
  tcase_add_test(tc, case_minus_1000000000000000000000000000_sub_0_0_1);

  suite_add_tcase(s, tc);
  return s;
}

int s21_sub_test(void) {
  Suite *s = s21_sub_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}