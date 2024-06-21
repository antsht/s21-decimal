#include "s21_decimal.h"

#include <stdlib.h>


int s21_from_int_to_decimal(int src, s21_decimal *dst){
  int status = OK;
  if (dst == NULL) status = CALCULATION_ERROR;
  if (status == OK) {
    dst->bits[0] = abs(src);
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
  }
  if (src <  0  &&  status  == OK){
    dst->bits[3] = dst->bits[3] ^ (1 << 31);
  }
  return status;
}

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
