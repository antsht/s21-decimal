#include "s21_test.h"

int main(void) {
  int number_failed = 0;

  number_failed += s21_tools_test();
  number_failed += s21_negate_test();
  number_failed += s21_from_int_to_decimal_test();
  number_failed += s21_from_decimal_to_float_test();
  number_failed += s21_long_mantissa_div_test();
  number_failed += s21_comparison_operators_test();
  number_failed += s21_from_decimal_to_int_test();
  number_failed += s21_from_float_to_decimal_test();
  number_failed += s21_truncate_test();
  number_failed += s21_add_test();
  number_failed += s21_sub_test();
  number_failed += s21_mul_test();
  number_failed += s21_round_test();
  number_failed += s21_floor_test();
  number_failed += s21_div_test();

  printf("====================\n\n");
  printf("Total errors: %d\n\n", number_failed);
  printf("====================\n\n");

  return 0;
}