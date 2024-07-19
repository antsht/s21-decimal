#include <stdlib.h>

#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  if (result == NULL) return CALCULATION_ERROR;

  *result = (s21_decimal){0};

  // Check for division by zero
  if (s21_decimal_is_zero(&value_2)) return DIVISION_BY_ZERO;

  s21_long_decimal l_value_1, l_value_2, l_result;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);

  // normalize scale of both l_value_1 and l_value_2
  s21_long_decimal ten = LONG_TEN;
  status = s21_long_decimal_normalize_scale(&l_value_1, &l_value_2);

  if (status == OK) {
    s21_long_decimal l_remainder = {0};
    status |=
        s21_long_mantissa_div(l_value_1, l_value_2, &l_result, &l_remainder);

    int scale = 0;
    while (status == OK && !s21_long_decimal_is_zero(&l_remainder) &&
           scale <= MAX_DECIMAL_SCALE + 2) {
      status |= s21_long_mantissa_mul(l_value_1, ten, &l_value_1);
      status |= s21_set_scale_of_long_decimal(&l_value_1, ++scale);
      status |=
          s21_long_mantissa_div(l_value_1, l_value_2, &l_result, &l_remainder);
      status |= s21_set_scale_of_long_decimal(&l_result, scale);
    }
    status |= s21_set_scale_of_long_decimal(&l_result, scale);
    int value_1_sign, value_2_sign;
    s21_get_sign_of_decimal(&value_1, &value_1_sign);
    s21_get_sign_of_decimal(&value_2, &value_2_sign);
    if (status == OK) {
      s21_set_sign_of_long_decimal(&l_result, value_1_sign ^ value_2_sign);
      status |= s21_from_long_decimal_to_decimal(l_result, result);
    }
    if (status == OK) {
      s21_set_sign_of_decimal(result, value_1_sign ^ value_2_sign);
    }
  }
  return status;
}

int s21_long_mantissa_div(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result,
                          s21_long_decimal *remainder) {
  int status = OK;

  if (result == NULL || remainder == NULL) return CALCULATION_ERROR;

  // Check for division by zero
  if (s21_long_decimal_is_zero(&value_2)) return DIVISION_BY_ZERO;

  *result = (s21_long_decimal){{0, 0, 0, 0, 0, 0, 0, 0}};
  *remainder = (s21_long_decimal){{0, 0, 0, 0, 0, 0, 0, 0}};

  for (int i = (LONG_DECIMAL_MANTISSA_BITS - 1); i >= 0; i--) {
    // Left shift remainder by 1 bit
    s21_left_shift_long_decimal(remainder);

    // Add the current bit of l_value_1 to the remainder
    remainder->bits[0] |= ((value_1.bits[i / 32] >> (i % 32)) & 1);

    // Subtract divisor (value_2) from the remainder

    s21_long_decimal tmp = value_2;
    tmp.bits[7] = 0;
    int tmp_borrow = s21_long_decimal_is_greater(tmp, *remainder);

    // If there was no borrow, the divisor fits into the remainder
    if (tmp_borrow == 0) {
      s21_long_mantissa_sub(*remainder, value_2, remainder);
      result->bits[i / 32] |= (1U << (i % 32));
    }
  }

  return status;
}
