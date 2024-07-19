#include <limits.h>

#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  int status = OK;
  s21_decimal int_min = {0};
  s21_from_int_to_decimal(INT_MIN, &int_min);
  s21_decimal int_max = {0};
  s21_from_int_to_decimal(INT_MAX, &int_max);

  s21_truncate(src, &src);

  if (s21_is_less(src, int_min) || s21_is_greater(src, int_max)) {
    status = CONVERTATION_ERROR;
  }
  if (status == OK) {
    int sign = 0;
    s21_get_sign_of_decimal(&src, &sign);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 32; j++) {
        int bit = 0;
        s21_get_nth_bit_value(&src, j + i * 31, &bit);
        *dst += bit * pow(2, j + i * 32);
      }
    }
    if (sign) *dst *= -1;
  }

  return status;
}