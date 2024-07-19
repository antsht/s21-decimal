#include <stdlib.h>

#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return CALCULATION_ERROR;

  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3] ^ (1U << 31);

  return OK;
}
