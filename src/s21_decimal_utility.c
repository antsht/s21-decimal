#include <stdlib.h>

#include "s21_decimal.h"

void s21_print_decimal_as_binary(s21_decimal *value) {
  for (int i = 3; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (value->bits[i] >> j) & 1);
    }
    printf(" ");
  }
  printf("\n");
}

int get_nth_bit_value(s21_decimal *value, int n, int *result) {
  int status = OK;
  if (n < 0 || n > 95) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    int byte = n / 32;
    int offset = n % 32;
    *result = (value->bits[byte] >> offset) & 1;
  }
  return status;
}

int set_nth_bit_value(s21_decimal *value, int n, int value_to_set) {
  int status = OK;
  if (value == NULL || n < 0 || n > 95 ||
      !(value_to_set == 0 || value_to_set == 1)) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    int byte = n / 32;
    int offset = n % 32;
    value->bits[byte] |= (1 << offset);
  }
  return status;
}

int get_sign_of_decimal(s21_decimal *value, int *result) {
  int status = OK;
  if (value == NULL || result == NULL) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    *result = (value->bits[3] >> 31) & 1;
  }
  return status;
}

int set_sign_of_decimal(s21_decimal *value, int sign_to_set) {
  int status = OK;
  if (value == NULL || !(sign_to_set == POSITIVE || sign_to_set == NEGATIVE)) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    value->bits[3] |= (sign_to_set << 31);
  }
  return status;
}

int get_exponent_of_decimal(s21_decimal *value, int *result) {
  int status = OK;
  if (value == NULL || result == NULL) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    *result = (value->bits[3] >> 16) & 31;
  }
  return status;
}
int set_exponent_of_decimal(s21_decimal *value, int exponent_to_set) {
  int status = OK;
  if (value == NULL || exponent_to_set < 0 || exponent_to_set > 28) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    value->bits[3] |= (exponent_to_set << 16);
  }
  return status;
}

int s21_mantissa_add(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int status = OK;
  if (result == NULL) status = CALCULATION_ERROR;
  if (status == OK) {
    int carry = 0;
    for (int i = 0; i < 96; i++) {
      int bit1 = (value_1.bits[i / 32] >> (i % 32)) & 1;
      int bit2 = (value_2.bits[i / 32] >> (i % 32)) & 1;
      int sum = bit1 + bit2 + carry;
      result->bits[i / 32] |= (sum % 2) << (i % 32);
      carry = sum / 2;
    }
    if (carry) {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}

int s21_mantissa_sub(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int status = OK;
  if (result == NULL) status = CALCULATION_ERROR;
  if (status == OK) {
    int carry = 0;
    for (int i = 0; i < 96; i++) {
      int bit1 = (value_1.bits[i / 32] >> (i % 32)) & 1;
      int bit2 = (value_2.bits[i / 32] >> (i % 32)) & 1;
      int sum = bit1 - bit2 - carry;
      result->bits[i / 32] |= (sum % 2) << (i % 32);
      carry = sum / 2;
    }
  }
  return status;
}