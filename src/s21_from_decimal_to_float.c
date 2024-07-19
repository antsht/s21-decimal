#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = OK;
  if (dst == NULL || s21_decimal_is_correct(&src) != OK)
    status = CONVERTATION_ERROR;
  else {
    int exponent = 0, sign = 0, byte = 0;
    double res = 0.0;
    for (int i = 0; i < 96; i++) {
      status = s21_get_nth_bit_value(&src, i, &byte);
      if (byte == 1 && status == 0) res = res + pow(2, i);
    }
    status = s21_get_scale_of_decimal(&src, &exponent);
    while (status == 0 && 0 < exponent--) res /= 10;
    status = s21_get_sign_of_decimal(&src, &sign);
    if (status == 0) *dst = (float)(res * (sign == 1 ? -1 : 1));
  }
  return status;
}