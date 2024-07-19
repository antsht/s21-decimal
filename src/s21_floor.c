#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL || s21_decimal_is_correct(&value) != OK)
    return CALCULATION_ERROR;
  int status = OK;

  s21_long_decimal l_value;
  status |= s21_from_decimal_to_long_decimal(value, &l_value);

  int value_sign, value_scale;
  status |= s21_get_sign_of_long_decimal(&l_value, &value_sign);
  status |= s21_get_scale_of_long_decimal(&l_value, &value_scale);

  if (value_scale > 0) {
    int frac_digit;
    status |=
        s21_get_nth_digit_from_long_decimal(l_value, value_scale, &frac_digit);
    s21_long_decimal l_v_10 = {0};
    l_v_10.bits[0] = 10U;
    s21_long_decimal l_remainder = {0};

    do {
      status |= s21_long_mantissa_div(l_value, l_v_10, &l_value, &l_remainder);
      value_scale--;
    } while (value_scale > 0);

    if (value_sign == NEGATIVE) {
      s21_long_decimal l_v_1 = {0};
      l_v_1.bits[0] = 1U;
      status |= s21_long_mantissa_add(l_value, l_v_1, &l_value);
    }
    status |= s21_set_sign_of_long_decimal(&l_value, value_sign);
    status |= s21_set_scale_of_long_decimal(&l_value, value_scale);
  }
  status |= s21_from_long_decimal_to_decimal(l_value, result);

  return status;
}