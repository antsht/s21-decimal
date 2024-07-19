#ifndef _S21_DECIMAL_H_
#define _S21_DECIMAL_H_
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define POSITIVE 0
#define NEGATIVE 1

#define DECIMAL_SIZE 4
#define DECIMAL_MANTISSA_BITS 96
#define LONG_DECIMAL_SIZE 8
#define LONG_DECIMAL_MANTISSA_BITS 224
#define MAX_DECIMAL_SCALE 28
#define LONG_TEN                 \
  {                              \
    { 10U, 0, 0, 0, 0, 0, 0, 0 } \
  }

typedef struct {
  unsigned int bits[DECIMAL_SIZE];
} s21_decimal;

typedef struct {
  unsigned int bits[LONG_DECIMAL_SIZE];
} s21_long_decimal;

typedef enum {
  OK = 0,
  INF_PLUS = 1,
  INF_MINUS = 2,
  DIVISION_BY_ZERO = 3
} Arithmetic_operation_result;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
#define FALSE 0
#define TRUE 1

// Less than	<
int s21_is_less(s21_decimal, s21_decimal);

// Less than or equal to	<=
int s21_is_less_or_equal(s21_decimal, s21_decimal);

// Greater than	>
int s21_is_greater(s21_decimal, s21_decimal);

// Greater than or equal to	>=
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

// Equal to	==
int s21_is_equal(s21_decimal, s21_decimal);

// Not equal to	!=
int s21_is_not_equal(s21_decimal, s21_decimal);

// Convertors and parsers

// From int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// From float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// To int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
/* check if exp > 0 divide by 10^exp then convert */

// To float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#define CONVERTATION_ERROR 1

// Other functions

// Rounds a specified Decimal number to the closest integer toward negative
// infinity.
int s21_floor(s21_decimal value, s21_decimal *result);

// Rounds a decimal value to the nearest integer.
int s21_round(s21_decimal value, s21_decimal *result);

// Returns the integral digits of the specified Decimal; any fractional digits
// are discarded, including trailing zeroes.
int s21_truncate(s21_decimal value, s21_decimal *result);

// Returns the result of multiplying the specified Decimal value by negative
// one.
int s21_negate(s21_decimal value, s21_decimal *result);

#define CALCULATION_ERROR 1

// Utility helper functions
/* for debug */
// void s21_print_decimal_as_binary(s21_decimal *value);
// void s21_print_decimal(s21_decimal value);
// void s21_print_long_decimal_as_binary(s21_long_decimal *value);
// void s21_print_long_decimal(s21_long_decimal l_value);

int s21_get_nth_bit_value(s21_decimal *value, int n, int *result);
int s21_set_nth_bit_value(s21_decimal *value, int n, int value_to_set);

int s21_get_sign_of_decimal(s21_decimal *value, int *result);
int s21_set_sign_of_decimal(s21_decimal *value, int sign_to_set);

int s21_get_sign_of_long_decimal(s21_long_decimal *value, int *result);
int s21_set_sign_of_long_decimal(s21_long_decimal *value, int sign_to_set);

int s21_get_scale_of_decimal(s21_decimal *value, int *result);
int s21_set_scale_of_decimal(s21_decimal *value, int exponent_to_set);

int s21_get_scale_of_long_decimal(s21_long_decimal *value, int *result);
int s21_set_scale_of_long_decimal(s21_long_decimal *value, int exponent_to_set);

int s21_long_mantissa_add(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result);
int s21_long_mantissa_sub(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result);
int s21_long_mantissa_mul(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result);
int s21_long_mantissa_div(s21_long_decimal value_1, s21_long_decimal value_2,
                          s21_long_decimal *result,
                          s21_long_decimal *remainder);
int s21_from_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *dst);

int s21_from_long_decimal_to_decimal(s21_long_decimal value, s21_decimal *dst);

int s21_left_shift_long_decimal(s21_long_decimal *value);

int s21_left_n_shift_long_decimal(s21_long_decimal *value, int n);

int s21_long_decimal_is_zero(s21_long_decimal *value);

int s21_decimal_is_zero(s21_decimal *value);

int s21_long_decimal_normalize_scale(s21_long_decimal *value_1,
                                     s21_long_decimal *value_2);

int s21_long_decimal_is_less(s21_long_decimal l_value_1,
                             s21_long_decimal l_value_2);

int s21_long_decimal_is_less_or_equal(s21_long_decimal l_value_1,
                                      s21_long_decimal l_value_2);

int s21_long_decimal_is_greater(s21_long_decimal l_value_1,
                                s21_long_decimal l_value_2);

int s21_long_decimal_is_greater_or_equal(s21_long_decimal l_value_1,
                                         s21_long_decimal l_value_2);

int s21_long_decimal_is_equal(s21_long_decimal l_value_1,
                              s21_long_decimal l_value_2);

int s21_long_decimal_is_not_equal(s21_long_decimal l_value_1,
                                  s21_long_decimal l_value_2);

int s21_get_nth_digit_from_long_decimal(s21_long_decimal l_value, int n,
                                        int *result);

int s21_decimal_is_correct(s21_decimal *dst);

int s21_long_decimal_fit_into_decimal(s21_long_decimal *l_value);

int s21_long_decimal_round_to_decimal(s21_long_decimal l_value,
                                      s21_long_decimal *result);

#endif