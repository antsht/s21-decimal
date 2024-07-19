#include "s21_decimal.h"

// #include <stdlib.h>

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  if (result == NULL || s21_decimal_is_correct(&value_1) != OK ||
      s21_decimal_is_correct(&value_2) != OK)
    return CALCULATION_ERROR;

  *result = (s21_decimal){0};

  s21_long_decimal l_value_1, l_value_2, l_result = {0};

  status |= s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  status |= s21_from_decimal_to_long_decimal(value_2, &l_value_2);

  int value_1_sign, value_2_sign, value_1_scale, value_2_scale;

  if (s21_decimal_is_zero(&value_1) || s21_decimal_is_zero(&value_2)) {
    value_1_scale = 0;
    value_2_scale = 0;
    s21_get_scale_of_decimal(&value_1, &value_1_scale);
    s21_get_scale_of_decimal(&value_2, &value_2_scale);
    s21_set_scale_of_decimal(result, (value_1_scale > value_2_scale)
                                         ? value_1_scale
                                         : value_2_scale);
    s21_get_sign_of_decimal(&value_1, &value_1_sign);
    s21_get_sign_of_decimal(&value_2, &value_2_sign);
    s21_set_sign_of_decimal(result, value_1_sign ^ value_2_sign);

  } else {
    status |= s21_long_mantissa_mul(l_value_1, l_value_2, &l_result);

    status |= s21_get_sign_of_long_decimal(&l_value_1, &value_1_sign);
    status |= s21_get_sign_of_long_decimal(&l_value_2, &value_2_sign);
    status |=
        s21_set_sign_of_long_decimal(&l_result, value_1_sign ^ value_2_sign);
    status |= s21_get_scale_of_long_decimal(&l_value_1, &value_1_scale);
    status |= s21_get_scale_of_long_decimal(&l_value_2, &value_2_scale);
    status |=
        s21_set_scale_of_long_decimal(&l_result, value_1_scale + value_2_scale);

    if (status == OK) {
      status = s21_from_long_decimal_to_decimal(l_result, result);
    }
    if (s21_decimal_is_zero(result)) s21_set_scale_of_decimal(result, 0);
  }

  return status;
}

int s21_long_mantissa_mul(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result) {
  int status = OK;
  if (result == NULL) {
    return CALCULATION_ERROR;
  }

  *result = (s21_long_decimal){{0, 0, 0, 0, 0, 0, 0, 0}};
  result->bits[LONG_DECIMAL_SIZE - 1] = value_1.bits[LONG_DECIMAL_SIZE - 1];

  s21_long_decimal calc_result = {0};
  int shift_n = 0;
  for (int i = 0; i < LONG_DECIMAL_MANTISSA_BITS; i++) {
    if ((value_2.bits[i / 32] >> (i % 32)) & 1) {
      status |= s21_left_n_shift_long_decimal(&value_1, shift_n);
      shift_n = 0;
      status |= s21_long_mantissa_add(calc_result, value_1, &calc_result);
    }
    shift_n++;
  }
  *result = calc_result;

  return status;
}