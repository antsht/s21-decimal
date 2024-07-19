#include <stdlib.h>

#include "s21_decimal.h"

int s21_get_nth_bit_value(s21_decimal *value, int n, int *result) {
  if (value == NULL || result == NULL || n < 0 ||
      n > (DECIMAL_MANTISSA_BITS - 1))
    return CALCULATION_ERROR;

  int byte = n / 32;
  int offset = n % 32;
  *result = (value->bits[byte] >> offset) & 1;

  return OK;
}

int s21_set_nth_bit_value(s21_decimal *value, int n, int value_to_set) {
  if (value == NULL || n < 0 || n > (DECIMAL_MANTISSA_BITS - 1) ||
      !(value_to_set == 0 || value_to_set == 1))
    return CALCULATION_ERROR;

  int byte = n / 32;
  int offset = n % 32;
  value->bits[byte] &= ~(1U << offset);
  value->bits[byte] |= ((unsigned int)value_to_set << offset);

  return OK;
}

int s21_get_sign_of_decimal(s21_decimal *value, int *result) {
  if (value == NULL || result == NULL) return CALCULATION_ERROR;

  *result = (value->bits[(DECIMAL_SIZE - 1)] >> 31) & 1;

  return OK;
}

int s21_set_sign_of_decimal(s21_decimal *value, int sign_to_set) {
  if (value == NULL || !(sign_to_set == POSITIVE || sign_to_set == NEGATIVE))
    return CALCULATION_ERROR;

  value->bits[(DECIMAL_SIZE - 1)] &= (0x00FFFFFF);
  value->bits[(DECIMAL_SIZE - 1)] |= ((unsigned int)sign_to_set << 31);

  return OK;
}

int s21_get_sign_of_long_decimal(s21_long_decimal *value, int *result) {
  if (value == NULL || result == NULL) return CALCULATION_ERROR;

  *result = (value->bits[(LONG_DECIMAL_SIZE - 1)] >> 31) & 1U;

  return OK;
}

int s21_set_sign_of_long_decimal(s21_long_decimal *value, int sign_to_set) {
  if (value == NULL || !(sign_to_set == POSITIVE || sign_to_set == NEGATIVE))
    return CALCULATION_ERROR;

  value->bits[(LONG_DECIMAL_SIZE - 1)] &= (0x00FFFFFF);
  value->bits[(LONG_DECIMAL_SIZE - 1)] |= ((unsigned int)sign_to_set << 31);

  return OK;
}

int s21_get_scale_of_decimal(s21_decimal *value, int *result) {
  if (value == NULL || result == NULL) return CALCULATION_ERROR;

  *result = (value->bits[(DECIMAL_SIZE - 1)] >> 16) & 0xFF;

  return OK;
}
int s21_set_scale_of_decimal(s21_decimal *value, int exponent_to_set) {
  if (value == NULL || exponent_to_set < 0 ||
      exponent_to_set > MAX_DECIMAL_SCALE)
    return CALCULATION_ERROR;

  value->bits[(DECIMAL_SIZE - 1)] &= (0x80000000);
  value->bits[(DECIMAL_SIZE - 1)] |= (exponent_to_set << 16);

  return OK;
}

int s21_get_scale_of_long_decimal(s21_long_decimal *value, int *result) {
  if (value == NULL || result == NULL) return CALCULATION_ERROR;

  *result = (value->bits[(LONG_DECIMAL_SIZE - 1)] >> 16) & 63;

  return OK;
}
int s21_set_scale_of_long_decimal(s21_long_decimal *value,
                                  int exponent_to_set) {
  if (value == NULL || exponent_to_set < 0 ||
      exponent_to_set > MAX_DECIMAL_SCALE * 2)
    return CALCULATION_ERROR;

  value->bits[(LONG_DECIMAL_SIZE - 1)] &= (0x80000000);
  value->bits[(LONG_DECIMAL_SIZE - 1)] |= (exponent_to_set << 16);

  return OK;
}

int s21_from_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *dst) {
  if (dst == NULL) return CALCULATION_ERROR;

  dst->bits[0] = value.bits[0];
  dst->bits[1] = value.bits[1];
  dst->bits[2] = value.bits[2];
  dst->bits[3] = 0;
  dst->bits[4] = 0;
  dst->bits[5] = 0;
  dst->bits[6] = 0;
  dst->bits[7] = value.bits[3];

  return OK;
}

int s21_from_long_decimal_to_decimal(s21_long_decimal value, s21_decimal *dst) {
  if (dst == NULL) return CALCULATION_ERROR;

  int status = OK;
  int value_sign, value_scale;
  status |= s21_get_sign_of_long_decimal(&value, &value_sign);
  status |= s21_get_scale_of_long_decimal(&value, &value_scale);
  if (value_scale > 0)
    status |= s21_long_decimal_round_to_decimal(value, &value);

  // If long mantissa greater then 79228162514264337593543950335
  if (s21_long_decimal_fit_into_decimal(&value) == FALSE) {
    if (value_sign == POSITIVE) {
      status = INF_PLUS;
    } else {
      status = INF_MINUS;
    }
  }

  dst->bits[0] = value.bits[0];
  dst->bits[1] = value.bits[1];
  dst->bits[2] = value.bits[2];
  dst->bits[DECIMAL_SIZE - 1] = value.bits[LONG_DECIMAL_SIZE - 1];

  return status;
}

int s21_left_shift_long_decimal(s21_long_decimal *value) {
  if (value == NULL) return CALCULATION_ERROR;

  int status = OK;
  for (int i = (LONG_DECIMAL_SIZE - 1); i >= 0; i--) {
    int carry = (value->bits[i] >> 31) & 1;
    value->bits[i] = value->bits[i] << 1;
    if (i < (LONG_DECIMAL_SIZE - 2)) {
      value->bits[i + 1] = value->bits[i + 1] | carry;
    } else if (carry)
      status = CALCULATION_ERROR;
  }
  return status;
}

int s21_left_n_shift_long_decimal(s21_long_decimal *value, int n) {
  if (value == NULL || n < 0 || n > (LONG_DECIMAL_MANTISSA_BITS - 1))
    return CALCULATION_ERROR;

  int status = OK;
  s21_long_decimal result = {0};
  result.bits[(LONG_DECIMAL_SIZE - 1)] = value->bits[(LONG_DECIMAL_SIZE - 1)];
  for (int i = (LONG_DECIMAL_MANTISSA_BITS - 1); i >= 0; i--) {
    int j = i + n;
    if ((value->bits[i / 32] >> (i % 32)) & 1) {
      if (j < (LONG_DECIMAL_MANTISSA_BITS)) {
        result.bits[j / 32] |= 1U << (j % 32);
      } else {
        status |= CALCULATION_ERROR;
      }
    }
  }
  *value = result;

  return status;
}

int s21_long_decimal_is_zero(s21_long_decimal *value) {
  int status = TRUE;

  if (value)
    for (int i = 0; i < (LONG_DECIMAL_SIZE - 1); i++)
      if (value->bits[i]) status = FALSE;

  return status;
}

int s21_decimal_is_zero(s21_decimal *value) {
  int status = TRUE;

  if (value)
    for (int i = 0; i < (DECIMAL_SIZE - 1); i++)
      if (value->bits[i]) status = FALSE;

  return status;
}

int s21_long_decimal_normalize_scale(s21_long_decimal *value_1,
                                     s21_long_decimal *value_2) {
  int status = OK;

  int scale_1 = 0;
  int scale_2 = 0;
  status |= s21_get_scale_of_long_decimal(value_1, &scale_1);
  status |= s21_get_scale_of_long_decimal(value_2, &scale_2);

  if (status == OK) {
    int scale_diff = abs(scale_1 - scale_2);
    s21_long_decimal l_v_10 = LONG_TEN;
    if (scale_1 > scale_2) {
      for (int i = 0; i < scale_diff; i++) {
        status |= s21_long_mantissa_mul(*value_2, l_v_10, value_2);
      }
      status |= s21_set_scale_of_long_decimal(value_2, scale_1);
    } else if (scale_1 < scale_2) {
      for (int i = 0; i < scale_diff; i++) {
        status |= s21_long_mantissa_mul(*value_1, l_v_10, value_1);
      }
      status |= s21_set_scale_of_long_decimal(value_1, scale_2);
    }
  }

  return status;
}

int s21_get_nth_digit_from_long_decimal(s21_long_decimal l_value, int n,
                                        int *result) {
  if (result == NULL) return CALCULATION_ERROR;

  int status = OK;
  s21_long_decimal l_v_10 = LONG_TEN;
  s21_long_decimal l_remainder = {0};
  int i = 0;

  while (i++ < n)
    status |= s21_long_mantissa_div(l_value, l_v_10, &l_value, &l_remainder);

  *result = l_remainder.bits[0];
  return status;
}

int s21_decimal_is_correct(s21_decimal *value) {
  if (value == NULL) return CALCULATION_ERROR;
  int status = OK;
  int scale = 0;
  s21_get_scale_of_decimal(value, &scale);

  if (scale < 0 || scale > 28) status = CALCULATION_ERROR;
  if (value->bits[DECIMAL_SIZE - 1] & 0x7F00FFFF) status = CALCULATION_ERROR;
  return status;
}

int s21_long_decimal_fit_into_decimal(s21_long_decimal *l_value) {
  int result = TRUE;
  int value_scale;
  s21_get_scale_of_long_decimal(l_value, &value_scale);
  if (value_scale > 28) {
    result = FALSE;
  } else {
    for (int i = DECIMAL_SIZE - 1; i < LONG_DECIMAL_SIZE - 1; i++) {
      if (l_value->bits[i]) result = FALSE;
    }
  }
  return result;
}

int s21_long_decimal_round_to_decimal(s21_long_decimal l_value,
                                      s21_long_decimal *result) {
  int status = OK;
  if (result == NULL) return CALCULATION_ERROR;

  int value_sign, value_scale;
  status |= s21_get_sign_of_long_decimal(&l_value, &value_sign);
  status |= s21_get_scale_of_long_decimal(&l_value, &value_scale);

  int fit = s21_long_decimal_fit_into_decimal(&l_value);
  if (value_scale > 0 && fit == FALSE) {
    s21_long_decimal l_v_10 = {0};
    l_v_10.bits[0] = 10U;
    s21_long_decimal l_remainder = {0};

    do {
      status |= s21_long_mantissa_div(l_value, l_v_10, &l_value, &l_remainder);
      value_scale--;
      status |= s21_set_scale_of_long_decimal(&l_value, value_scale);
      fit = s21_long_decimal_fit_into_decimal(&l_value);
    } while (fit == FALSE && value_scale > 0);

    // Use bank rounding
    int last_digit;
    status |= s21_get_nth_digit_from_long_decimal(l_value, 1, &last_digit);
    int last_digit_is_odd = last_digit % 2;
    if (l_remainder.bits[0] > 5 ||
        (l_remainder.bits[0] == 5 && last_digit_is_odd)) {
      s21_long_decimal l_v_1 = {0};
      l_v_1.bits[0] = 1U;
      status |= s21_long_mantissa_add(l_value, l_v_1, &l_value);
    }

    status |= s21_set_sign_of_long_decimal(&l_value, value_sign);
    status |= s21_set_scale_of_long_decimal(&l_value, value_scale);
  }
  *result = l_value;
  return status;
}

/*void s21_print_decimal_as_binary(s21_decimal *value) {
  for (int i = (DECIMAL_SIZE - 1); i >= 0; i--) {
    printf("%d: ", i);
    for (int j = 31; j >= 0; j--) {
      printf("%d", (value->bits[i] >> j) & 1);
      if (j % 8 == 0) printf(" ");
    }
    printf("\n");
  }
}

void s21_print_decimal(s21_decimal value) {
  s21_long_decimal l_value;
  s21_from_decimal_to_long_decimal(value, &l_value);
  s21_print_long_decimal(l_value);
}

void s21_print_long_decimal_as_binary(s21_long_decimal *value) {
  for (int i = (LONG_DECIMAL_SIZE - 1); i >= 0; i--) {
    printf("%d: ", i);
    for (int j = 31; j >= 0; j--) {
      printf("%d", (value->bits[i] >> j) & 1);
      if (j % 8 == 0) printf(" ");
    }
    printf("\n");
  }
}

void s21_print_long_decimal(s21_long_decimal l_value) {
  char str[256] = {0};
  int i = 254;
  int status = OK;
  int value_sign, value_scale;
  status |= s21_get_sign_of_long_decimal(&l_value, &value_sign);
  status |= s21_get_scale_of_long_decimal(&l_value, &value_scale);
  s21_long_decimal l_v_10 = {0};
  l_v_10.bits[0] = 10U;
  s21_long_decimal l_remainder = {0};
  int d = 0;
  while (!s21_long_decimal_is_zero(&l_value) || value_scale >= d) {
    if (value_scale > 0 && d == value_scale) str[i--] = '.';
    status |= s21_long_mantissa_div(l_value, l_v_10, &l_value, &l_remainder);
    str[i--] = l_remainder.bits[0] + 48;
    d++;
  }
  if (value_sign == NEGATIVE) str[i--] = '-';
  printf("%s\n", str + i + 1);
}*/