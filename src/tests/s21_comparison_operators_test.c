#include <check.h>

#include "s21_test.h"

void compare(s21_decimal dec_1, s21_decimal dec_2) {
  int is_greater_t = s21_is_greater(dec_1, dec_2);
  int is_greater_f = s21_is_greater(dec_2, dec_1);
  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_2);
  int is_greater_or_equal_f = s21_is_greater_or_equal(dec_2, dec_1);
  int is_less_f = s21_is_less(dec_1, dec_2);
  int is_less_t = s21_is_less(dec_2, dec_1);
  int is_less_or_equal_f = s21_is_less_or_equal(dec_1, dec_2);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_2, dec_1);
  int is_equal = s21_is_equal(dec_1, dec_2);
  int is_not_equal = s21_is_not_equal(dec_1, dec_2);

  ck_assert(is_equal == FALSE);
  ck_assert(is_greater_or_equal_t == TRUE);
  ck_assert(is_greater_or_equal_f == FALSE);
  ck_assert(is_less_f == FALSE);
  ck_assert(is_less_t == TRUE);
  ck_assert(is_less_or_equal_f == FALSE);
  ck_assert(is_less_or_equal_t == TRUE);
  ck_assert(is_not_equal == TRUE);
  ck_assert(is_greater_f == FALSE);
  ck_assert(is_greater_t == TRUE);
}

START_TEST(case_12_00001_and_12) {
  s21_decimal dec_1 = {{1200001, 0, 0, 327680}};  // dec_1 = (12.00001)
  s21_decimal dec_2 = {{1200000, 0, 0, 327680}};  // dec_2 = (12.0)
  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_123_and_neg_123) {
  s21_decimal dec_1 = {{123, 0, 0, 0}};           // 123
  s21_decimal dec_2 = {{123, 0, 0, 2147483648}};  // -123
  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_123_and_zero) {
  s21_decimal dec_1 = {{123, 0, 0, 0}};        // 123
  s21_decimal dec_2 = {{0x0, 0x0, 0x0, 0x0}};  // 0

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_3e_minus_28_and_zero) {
  s21_decimal dec_1 = {{3, 0, 0, 1835008}};  // 3e-28
  s21_decimal dec_2 = {{0, 0, 0, 0}};        // 0

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_minus_3e_minus_28_and_zero) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};           // 0
  s21_decimal dec_2 = {{3, 0, 0, 2149318656}};  //-3e-28

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_max_and_max_low) {
  s21_decimal dec_1 = {{0xffffffff, 0xffffffff, 0xffffffff,
                        0x0}};  // 79228162514264337593543950335
  s21_decimal dec_2 = {{0xfffffffe, 0xffffffff, 0xffffffff,
                        0x0}};  // 79228162514264337593543950334

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_max_and_min) {
  s21_decimal dec_1 = {{0xffffffff, 0xffffffff, 0xffffffff,
                        0x0}};  // 79228162514264337593543950335
  s21_decimal dec_2 = {{0xffffffff, 0xffffffff, 0xffffffff,
                        0x80000000}};  // -79228162514264337593543950334

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_2e_28_and_1e_28) {
  s21_decimal dec_1 = {{0x2, 0x0, 0x0, 0x1c0000}};  // 2e-28
  s21_decimal dec_2 = {{0x1, 0x0, 0x0, 0x1c0000}};  // 1e-28

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_1e_28_and_minus_1e_28) {
  s21_decimal dec_1 = {{0x1, 0x0, 0x0, 0x1c0000}};    // 1e-28
  s21_decimal dec_2 = {{0x1, 0x0, 0x0, 0x801c0000}};  // -1e-28

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_123456789_123456789_and_123456789_123456788) {
  s21_decimal dec_1 = {
      {2899336981, 28744523, 0, 589824}};  // 123456789.123456789
  s21_decimal dec_2 = {
      {2899336980, 28744523, 0, 589824}};  // 123456789.123456788

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_0_499999999999999001_and_0_49999999999999001) {
  s21_decimal dec_1 = {
      {3551656985, 116415321, 0, 1179648}};  // 0.499999999999999001
  s21_decimal dec_2 = {
      {784661529, 11641532, 0, 1114112}};  // 0.49999999999999001

  compare(dec_1, dec_2);
}
END_TEST

START_TEST(case_plus_0_and_minus_0) {
  s21_decimal dec_1 = {{0x0, 0x0, 0x0, 0x00}};        // +0
  s21_decimal dec_2 = {{0x0, 0x0, 0x0, 0x80000000}};  // -0

  int is_greater_t = s21_is_greater(dec_1, dec_2);
  int is_greater_f = s21_is_greater(dec_2, dec_1);
  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_2);
  int is_greater_or_equal_f = s21_is_greater_or_equal(dec_2, dec_1);
  int is_less_f = s21_is_less(dec_1, dec_2);
  int is_less_t = s21_is_less(dec_2, dec_1);
  int is_less_or_equal_f = s21_is_less_or_equal(dec_1, dec_2);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_2, dec_1);
  int is_equal = s21_is_equal(dec_1, dec_2);
  int is_not_equal = s21_is_not_equal(dec_1, dec_2);

  ck_assert(is_equal == TRUE);
  ck_assert(is_greater_or_equal_t == TRUE);
  ck_assert(is_greater_or_equal_f == TRUE);
  ck_assert(is_less_f == FALSE);
  ck_assert(is_less_t == FALSE);
  ck_assert(is_less_or_equal_f == TRUE);
  ck_assert(is_less_or_equal_t == TRUE);
  ck_assert(is_not_equal == FALSE);
  ck_assert(is_greater_f == FALSE);
  ck_assert(is_greater_t == FALSE);
}
END_TEST

START_TEST(case_min_and_0) {
  s21_decimal dec_1 = {
      {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};  // min
  s21_decimal dec_2 = {{0x0, 0x0, 0x0, 0x0}};             // 0

  int is_greater_t = s21_is_greater(dec_1, dec_2);
  int is_greater_f = s21_is_greater(dec_2, dec_1);
  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_2);
  int is_greater_or_equal_f = s21_is_greater_or_equal(dec_2, dec_1);
  int is_less_f = s21_is_less(dec_1, dec_2);
  int is_less_t = s21_is_less(dec_2, dec_1);
  int is_less_or_equal_f = s21_is_less_or_equal(dec_1, dec_2);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_2, dec_1);
  int is_equal = s21_is_equal(dec_1, dec_2);
  int is_not_equal = s21_is_not_equal(dec_1, dec_2);

  ck_assert(is_equal == FALSE);
  ck_assert(is_greater_or_equal_t == FALSE);
  ck_assert(is_greater_or_equal_f == TRUE);
  ck_assert(is_less_f == TRUE);
  ck_assert(is_less_t == FALSE);
  ck_assert(is_less_or_equal_f == TRUE);
  ck_assert(is_less_or_equal_t == FALSE);
  ck_assert(is_not_equal == TRUE);
  ck_assert(is_greater_f == TRUE);
  ck_assert(is_greater_t == FALSE);
}
END_TEST

START_TEST(case_low_equals) {
  s21_decimal dec_1 = {{0x1, 0x0, 0x0, 0x1c0000}};  // 1e-28

  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_1);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_1, dec_1);
  int is_equal = s21_is_equal(dec_1, dec_1);
  int is_not_equal = s21_is_not_equal(dec_1, dec_1);

  ck_assert(is_greater_or_equal_t == TRUE);
  ck_assert(is_less_or_equal_t == TRUE);
  ck_assert(is_equal == TRUE);
  ck_assert(is_not_equal == FALSE);
}
END_TEST

START_TEST(case_max_equals) {
  s21_decimal dec_1 = {{0xffffffff, 0xffffffff, 0xffffffff,
                        0x0}};  // 79228162514264337593543950335

  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_1);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_1, dec_1);
  int is_equal = s21_is_equal(dec_1, dec_1);
  int is_not_equal = s21_is_not_equal(dec_1, dec_1);

  ck_assert(is_greater_or_equal_t == TRUE);
  ck_assert(is_less_or_equal_t == TRUE);
  ck_assert(is_equal == TRUE);
  ck_assert(is_not_equal == FALSE);
}
END_TEST

START_TEST(case_equals_diff_entry) {
  s21_decimal dec_1 = {{0x7b, 0x0, 0x0, 0x0}};          // 123
  s21_decimal dec_2 = {{0xbbaee0, 0x0, 0x0, 0x50000}};  // 12300000e-5

  int is_greater_or_equal_t = s21_is_greater_or_equal(dec_1, dec_2);
  int is_less_or_equal_t = s21_is_less_or_equal(dec_1, dec_2);
  int is_equal = s21_is_equal(dec_1, dec_2);
  int is_not_equal = s21_is_not_equal(dec_1, dec_2);

  ck_assert(is_greater_or_equal_t == TRUE);
  ck_assert(is_less_or_equal_t == TRUE);
  ck_assert(is_equal == TRUE);
  ck_assert(is_not_equal == FALSE);
}
END_TEST

START_TEST(case_is_less) {
  s21_decimal dec_1 = {{4294967295, 4294967295, 4294967295,
                        2148663296}};  // -79228162514.264337593543950335
  s21_decimal dec_2 = {{4294967295, 4294967295, 4294967295,
                        2148990976}};  // -792281.62514264337593543950335

  int is_less = s21_is_less(dec_1, dec_2);
  ck_assert(is_less == TRUE);
}
END_TEST

START_TEST(case_is_less_or_equal) {
  s21_decimal dec_1 = {{4294967295, 4294967295, 4294967295,
                        2148663296}};  // -79228162514.264337593543950335
  s21_decimal dec_2 = {{4294967295, 4294967295, 4294967295,
                        2148990976}};  // -792281.62514264337593543950335

  int is_less_or_equal_t = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert(is_less_or_equal_t == TRUE);
}
END_TEST

START_TEST(case_is_greater) {
  s21_decimal dec_1 = {{4294967295, 4294967295, 4294967295,
                        2148663296}};  // -79228162514.264337593543950335
  s21_decimal dec_2 = {{4294967295, 4294967295, 4294967295,
                        2148990976}};  // -792281.62514264337593543950335

  int is_greater = s21_is_greater(dec_1, dec_2);
  ck_assert(is_greater == FALSE);
}
END_TEST

START_TEST(case_is_greater_or_equal) {
  s21_decimal dec_1 = {{4294967295, 4294967295, 4294967295,
                        2148663296}};  // -79228162514.264337593543950335
  s21_decimal dec_2 = {{4294967295, 4294967295, 4294967295,
                        2148990976}};  // -792281.62514264337593543950335

  int is_greater_or_equal = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert(is_greater_or_equal == FALSE);
}
END_TEST

Suite *s21_comparison_operators_suite(void) {
  Suite *s;
  s = suite_create("s21_comparison_operators() tests");
  TCase *tc;
  tc = tcase_create("comparison_operators");
  tcase_add_test(tc, case_12_00001_and_12);
  tcase_add_test(tc, case_123_and_neg_123);
  tcase_add_test(tc, case_123_and_zero);
  tcase_add_test(tc, case_3e_minus_28_and_zero);
  tcase_add_test(tc, case_minus_3e_minus_28_and_zero);
  tcase_add_test(tc, case_max_and_max_low);
  tcase_add_test(tc, case_max_and_min);
  tcase_add_test(tc, case_2e_28_and_1e_28);
  tcase_add_test(tc, case_1e_28_and_minus_1e_28);
  tcase_add_test(tc, case_plus_0_and_minus_0);
  tcase_add_test(tc, case_low_equals);
  tcase_add_test(tc, case_max_equals);
  tcase_add_test(tc, case_equals_diff_entry);
  tcase_add_test(tc, case_min_and_0);
  tcase_add_test(tc, case_is_less);
  tcase_add_test(tc, case_is_less_or_equal);
  tcase_add_test(tc, case_is_greater);
  tcase_add_test(tc, case_is_greater_or_equal);
  tcase_add_test(tc, case_0_499999999999999001_and_0_49999999999999001);
  tcase_add_test(tc, case_123456789_123456789_and_123456789_123456788);

  suite_add_tcase(s, tc);
  return s;
}

int s21_comparison_operators_test(void) {
  Suite *s = s21_comparison_operators_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}