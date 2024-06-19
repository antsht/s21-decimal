#include "s21_decimal.h"

#include <stdlib.h>

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = OK;
  if (result == NULL) status = CALCULATION_ERROR;
  if (status == OK) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3] ^ (1 << 31);
  }
  return status;
}
