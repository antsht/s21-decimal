#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || s21_decimal_is_correct(&value) != OK)
    return CALCULATION_ERROR;

  int status = OK;
  int value_scale = 0;
  int value_sign = 0;
  s21_long_decimal value_long = {0};
  s21_long_decimal value_long_remainder = {0};
  s21_long_decimal value_long_scale_divider = {{10, 0, 0, 0, 0, 0, 0, 0}};

  s21_from_decimal_to_long_decimal(value, &value_long);
  s21_get_scale_of_long_decimal(&value_long, &value_scale);
  s21_set_scale_of_long_decimal(&value_long, 0);
  s21_get_sign_of_long_decimal(&value_long, &value_sign);
  s21_set_sign_of_long_decimal(&value_long, POSITIVE);

  for (int i = 0; i < value_scale; i++) {
    s21_long_mantissa_div(value_long, value_long_scale_divider, &value_long,
                          &value_long_remainder);
  }

  if (value_sign == NEGATIVE) {
    s21_set_sign_of_long_decimal(&value_long, NEGATIVE);
  }
  s21_from_long_decimal_to_decimal(value_long, result);

  return status;
}