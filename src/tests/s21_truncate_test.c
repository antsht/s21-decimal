#include <check.h>
#include <string.h>

#include "s21_test.h"

START_TEST(s21_truncate_test_1) {
  s21_decimal test_decimal = {0};
  int test_result = 0;

  test_result = s21_truncate(test_decimal, NULL);

  ck_assert(test_result == CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal test_decimal = {{12345, 0, 0, 0}};
  s21_decimal expected_decimal = {{123, 0, 0, 0}};
  int test_result = 0;

  s21_set_scale_of_decimal(&test_decimal, 2);
  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal test_decimal = {{12345, 0, 0, 0}};
  s21_decimal expected_decimal = {{12345, 0, 0, 0}};
  int test_result = 0;

  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_4) {
  s21_decimal test_decimal = {{12345, 0, 0, 0}};
  s21_decimal expected_decimal = {{1, 0, 0, -2147483648}};
  int test_result = 0;

  s21_set_sign_of_decimal(&test_decimal, NEGATIVE);
  s21_set_scale_of_decimal(&test_decimal, 4);
  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_5) {
  s21_decimal test_decimal = {{12345, 0, 0, 0}};
  s21_decimal expected_decimal = {0};
  int test_result = 0;

  s21_set_scale_of_decimal(&test_decimal, 20);
  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_6) {
  s21_decimal test_decimal = {0};
  s21_decimal expected_decimal = {0};
  int test_result = 0;

  s21_set_scale_of_decimal(&test_decimal, 20);
  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_7) {
  s21_decimal test_decimal = {0};
  s21_decimal expected_decimal = {0};
  int test_result = 0;

  test_result = s21_truncate(test_decimal, &test_decimal);

  ck_assert(test_result == OK &&
            memcmp(&test_decimal, &expected_decimal, sizeof(s21_decimal)) == 0);
}
END_TEST

START_TEST(s21_truncate_test_8) {
  s21_decimal dec = {{1661992959, 1808227885, 5, 1310720}};
  s21_decimal dec_res;
  // 0.99999999999999999999 -> 0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_9) {
  s21_decimal dec = {{4294967295, 4294967295, 4294967295, 1835008}};
  s21_decimal dec_res;
  // 7.9228162514264337593543950335 -> 7
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 7 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_10) {
  s21_decimal dec = {{4294967295, 4294967295, 4294967295, 65536}};
  s21_decimal dec_res;
  // 7922816251426433759354395033.5 -> 7922816251426433759354395033
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 2576980377 &&
            dec_res.bits[1] == 2576980377 && dec_res.bits[2] == 429496729 &&
            dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_11) {
  s21_decimal dec = {{4294967295, 4294967295, 4294967295, 2147549184}};
  s21_decimal dec_res;
  // -7922816251426433759354395033.5 -> -7922816251426433759354395033
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 2576980377 &&
            dec_res.bits[1] == 2576980377 && dec_res.bits[2] == 429496729 &&
            dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_truncate_test_12) {
  s21_decimal dec = {{1661992959, 1808227885, 5, 2148794368}};
  s21_decimal dec_res;
  // -0.99999999999999999999 -> -0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);  //! -0
}
END_TEST

START_TEST(s21_truncate_test_13) {
  s21_decimal dec = {{9, 0, 0, 65536}};
  s21_decimal dec_res;
  // 0.9 -> 0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_14) {
  s21_decimal dec = {{9, 0, 0, 2147549184}};
  s21_decimal dec_res;
  // -0.9 -> -0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_truncate_test_15) {
  s21_decimal dec = {{268435457, 1042612833, 542101086, 1835008}};
  s21_decimal dec_res;
  // 1.0000000000000000000000000001 -> 0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_16) {
  s21_decimal dec = {{1, 0, 0, 851968}};
  s21_decimal dec_res;
  // 0.0000000000001 -> 0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_truncate_test_17) {
  s21_decimal dec = {{1, 0, 0, 2148401152}};
  s21_decimal dec_res;
  // -0.00000000000001 -> -0
  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_truncate_test_18) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal dec_res;

  int res = s21_truncate(dec, &dec_res);

  ck_assert(res == CALCULATION_ERROR);
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s;
  s = suite_create("s21_truncate() tests");
  TCase *tc;
  tc = tcase_create("truncate");
  tcase_add_test(tc, s21_truncate_test_1);
  tcase_add_test(tc, s21_truncate_test_2);
  tcase_add_test(tc, s21_truncate_test_3);
  tcase_add_test(tc, s21_truncate_test_4);
  tcase_add_test(tc, s21_truncate_test_5);
  tcase_add_test(tc, s21_truncate_test_6);
  tcase_add_test(tc, s21_truncate_test_7);
  tcase_add_test(tc, s21_truncate_test_8);
  tcase_add_test(tc, s21_truncate_test_9);
  tcase_add_test(tc, s21_truncate_test_10);
  tcase_add_test(tc, s21_truncate_test_11);
  tcase_add_test(tc, s21_truncate_test_12);
  tcase_add_test(tc, s21_truncate_test_13);
  tcase_add_test(tc, s21_truncate_test_14);
  tcase_add_test(tc, s21_truncate_test_15);
  tcase_add_test(tc, s21_truncate_test_16);
  tcase_add_test(tc, s21_truncate_test_17);
  tcase_add_test(tc, s21_truncate_test_18);
  suite_add_tcase(s, tc);
  return s;
}

int s21_truncate_test(void) {
  Suite *s = s21_truncate_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}