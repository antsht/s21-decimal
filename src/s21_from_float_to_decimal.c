#include "s21_decimal.h"

#define MAX_ABS_FLOAT_TO_CONVERT 7.922817e+28

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = OK;
  float modul_float = fabsf(src);
  if (dst == NULL || modul_float >= MAX_ABS_FLOAT_TO_CONVERT || isinf(src) ||
      isnan(src))
    return CONVERTATION_ERROR;
  *dst = (s21_decimal){{0, 0, 0, 0}};
  if (src != 0 && 0 < modul_float && modul_float < 1e-28) {
    status = CONVERTATION_ERROR;
  } else if (src != 0) {
    if (src < 0) status = s21_set_sign_of_decimal(dst, 1);
    char str_float[128] = {0};
    sprintf(str_float, "%E", modul_float);
    int count = 1;
    unsigned int mantissa = 0;
    for (int i = 7; i >= 0; i--)
      if (str_float[i] != '.') {
        mantissa += (str_float[i] - '0') * count;
        count *= 10;
      }
    int exponent = (str_float[10] - '0') * 10 + (str_float[11] - '0');
    if (str_float[9] == '-') exponent *= -1;
    exponent = (exponent - 6) * -1;
    if (exponent > MAX_DECIMAL_SCALE) {
      mantissa /= pow(10, exponent - MAX_DECIMAL_SCALE);
      exponent = MAX_DECIMAL_SCALE;
    }
    for (int i = 0; i <= 31; i++) {
      if (mantissa % 2) s21_set_nth_bit_value(dst, i, 1);
      mantissa /= 2;
    }
    s21_decimal dec_10 = {{10U, 0, 0, 0}};
    while (exponent < 0) {
      s21_mul(*dst, dec_10, dst);
      exponent++;
    }
    status |= s21_set_scale_of_decimal(dst, exponent);
  }
  return status;
}