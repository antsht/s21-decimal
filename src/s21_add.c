#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  if (result == NULL) return CALCULATION_ERROR;

  *result = (s21_decimal){0};

  s21_long_decimal l_value_1, l_value_2, l_result;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  int sign_1 = 0, sign_2 = 0;

  s21_get_sign_of_long_decimal(&l_value_1, &sign_1);
  s21_get_sign_of_long_decimal(&l_value_2, &sign_2);
  s21_set_sign_of_long_decimal(&l_value_1, POSITIVE);
  s21_set_sign_of_long_decimal(&l_value_2, POSITIVE);

  s21_long_decimal_normalize_scale(&l_value_1, &l_value_2);

  if (sign_1 == NEGATIVE && sign_2 == NEGATIVE) {
    s21_long_mantissa_add(l_value_1, l_value_2, &l_result);
    s21_set_sign_of_long_decimal(&l_result, NEGATIVE);
  } else if (sign_1 == NEGATIVE && sign_2 == POSITIVE) {
    if (s21_long_decimal_is_greater_or_equal(l_value_2, l_value_1)) {
      s21_long_mantissa_sub(l_value_2, l_value_1, &l_result);
      s21_set_sign_of_long_decimal(&l_result, POSITIVE);
    } else {
      s21_long_mantissa_sub(l_value_1, l_value_2, &l_result);
      s21_set_sign_of_long_decimal(&l_result, NEGATIVE);
    }
  } else if (sign_1 == POSITIVE && sign_2 == NEGATIVE) {
    if (s21_long_decimal_is_greater_or_equal(l_value_1, l_value_2)) {
      s21_long_mantissa_sub(l_value_1, l_value_2, &l_result);
      s21_set_sign_of_long_decimal(&l_result, POSITIVE);
    } else {
      s21_long_mantissa_sub(l_value_2, l_value_1, &l_result);
      s21_set_sign_of_long_decimal(&l_result, NEGATIVE);
    }
  } else if (sign_1 == POSITIVE && sign_2 == POSITIVE) {
    s21_long_mantissa_add(l_value_1, l_value_2, &l_result);
    s21_set_sign_of_long_decimal(&l_result, POSITIVE);
  }

  status = s21_from_long_decimal_to_decimal(l_result, result);

  if (s21_decimal_is_zero(result)) s21_set_sign_of_decimal(result, sign_1);

  return status;
}

int s21_long_mantissa_add(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result) {
  if (result == NULL) return CALCULATION_ERROR;

  int status = OK;
  *result = (s21_long_decimal){{0, 0, 0, 0, 0, 0, 0, 0}};
  result->bits[LONG_DECIMAL_SIZE - 1] = value_1.bits[LONG_DECIMAL_SIZE - 1];
  int carry = 0;

  for (int i = 0; i < LONG_DECIMAL_MANTISSA_BITS; i++) {
    int bit1 = (value_1.bits[i / 32] >> (i % 32)) & 1;
    int bit2 = (value_2.bits[i / 32] >> (i % 32)) & 1;
    int sum = bit1 + bit2 + carry;
    result->bits[i / 32] |= ((unsigned int)(sum % 2)) << (i % 32);
    carry = sum / 2;
  }

  if (carry) status = CALCULATION_ERROR;

  return status;
}
