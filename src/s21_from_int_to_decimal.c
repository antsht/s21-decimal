#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  *dst = (s21_decimal){{0, 0, 0, 0}};
  if (src == INT_MIN) {
    dst->bits[0] = (1U << 31);
  } else
    dst->bits[0] = abs(src);

  if (src < 0) {
    dst->bits[3] = dst->bits[3] ^ (1U << 31);
  }
  return OK;
}