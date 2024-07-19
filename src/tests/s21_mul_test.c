#include <check.h>

#include "s21_test.h"

START_TEST(case_NULL_result) {
  s21_decimal num_1 = {{1, 2, 3, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int return_s21 = s21_mul(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_long_NULL_result) {
  s21_long_decimal num_1 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  s21_long_decimal num_2 = {{1, 2, 3, 0, 0, 0, 0, 0}};
  int return_s21 = s21_long_mantissa_mul(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, CALCULATION_ERROR);
}
END_TEST

START_TEST(case_0_mul_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_mul_minus_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_mul_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_2, num_1, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_mul_0) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_mul_0) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_mul_MAX) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_mul_MIN) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_mul_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_mul_MIN) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_2, num_1, &s21_res);
  ck_assert_int_eq(return_s21, INF_MINUS);
}
END_TEST

START_TEST(case_MAX_mul_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, INF_PLUS);
}
END_TEST

START_TEST(case_MIN_mul_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_mul_minus_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 2147483648}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_mul_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_mul_minus_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2147483648}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_mul_minus_0_5) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 2147549184}};
  s21_decimal orig_res = {{0, 0, 2147483648, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_mul_05) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal orig_res = {{0, 0, 2147483648, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_mul_1e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_mul_1e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2149318656}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_mul_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_mul_0) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 1835008}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1e_28_mul_0) {
  s21_decimal num_1 = {{1, 0, 0, 2149318656}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 2149318656}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_mul_1e_28) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{0, 0, 0, 1835008}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_mul_minus_1e_28) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2149318656}};
  s21_decimal orig_res = {{0, 0, 0, 2149318656}};  //! 0
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_mul_10) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal orig_res = {{10, 0, 0, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_mul_1e_plus_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{268435456, 1042612833, 542101086, 0}};
  s21_decimal orig_res = {{268435456, 1042612833, 542101086, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_mul_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_mul_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 917504}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_mul_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_mul_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_mul_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_123_4567890_mul_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_mul_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_mul_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{304084036, 354870659, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_001_mul_2) {
  s21_decimal num_1 = {{1, 0, 0, 196608}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal orig_res = {{2, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_9_9_mul_0_0_1) {
  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{1, 0, 0, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_mul(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s;
  s = suite_create("s21_mul() tests");
  TCase *tc;
  tc = tcase_create("mul");
  tcase_add_test(tc, case_NULL_result);
  tcase_add_test(tc, case_long_NULL_result);
  tcase_add_test(tc, case_0_mul_0);
  tcase_add_test(tc, case_0_mul_minus_0);
  tcase_add_test(tc, case_minus_0_mul_0);
  tcase_add_test(tc, case_MAX_mul_0);
  tcase_add_test(tc, case_MIN_mul_0);
  tcase_add_test(tc, case_0_mul_MAX);
  tcase_add_test(tc, case_0_mul_MIN);
  tcase_add_test(tc, case_MAX_mul_MIN);
  tcase_add_test(tc, case_MIN_mul_MAX);
  tcase_add_test(tc, case_MAX_mul_MAX);
  tcase_add_test(tc, case_MIN_mul_1);
  tcase_add_test(tc, case_MIN_mul_minus_1);
  tcase_add_test(tc, case_MAX_mul_minus_1);
  tcase_add_test(tc, case_MAX_mul_1);
  tcase_add_test(tc, case_MAX_mul_05);
  tcase_add_test(tc, case_MIN_mul_minus_0_5);
  tcase_add_test(tc, case_MAX_mul_1e_28);
  tcase_add_test(tc, case_MIN_mul_1e_28);
  tcase_add_test(tc, case_MAX_mul_1e_28);
  tcase_add_test(tc, case_1e_28_mul_1e_28);
  tcase_add_test(tc, case_1e_28_mul_0);
  tcase_add_test(tc, case_minus_1e_28_mul_0);
  tcase_add_test(tc, case_0_mul_1e_28);
  tcase_add_test(tc, case_1e_28_mul_1e_plus_28);
  tcase_add_test(tc, case_1234567890_mul_1234567890);
  tcase_add_test(tc, case_1e_28_mul_10);
  tcase_add_test(tc, case_0_mul_minus_1e_28);
  tcase_add_test(tc, case_123_4567890_mul_123_4567890);
  tcase_add_test(tc, case_1234567890_mul_123_4567890);
  tcase_add_test(tc, case_minus_1234567890_mul_123_4567890);
  tcase_add_test(tc, case_1234567890_mul_minus_123_4567890);
  tcase_add_test(tc, case_minus_123_4567890_mul_minus_1234567890);
  tcase_add_test(tc, case_minus_1234567890_mul_minus_123_4567890);
  tcase_add_test(tc, case_123_4567890_mul_1234567890);
  tcase_add_test(tc, case_0_001_mul_2);
  tcase_add_test(tc, case_0_9_9_mul_0_0_1);

  suite_add_tcase(s, tc);
  return s;
}

int s21_mul_test(void) {
  Suite *s = s21_mul_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}