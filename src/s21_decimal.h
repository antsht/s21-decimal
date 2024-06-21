#ifndef _S21_DECIMAL_H_
#define _S21_DEСIMAL_H_

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

/* The binary representation of a Decimal number consists of a 1-bit sign, a
96-bit integer number, and a scaling factor used to divide the integer number
and specify what portion of it is a decimal fraction. The scaling factor is
implicitly the number 10, raised to an exponent ranging from 0 to 28.

Decimal number can be implemented as a four-element array of 32-bit signed
integers (int bits[4];).

bits[0], bits[1], and bits[2] contain the low, middle, and high 32 bits of the
96-bit integer number accordingly.

bits[3] contains the scale factor and sign, and consists of following parts:

Bits 0 to 15, the lower word, are unused and must be zero.
Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the
power of 10 to divide the integer number. Bits 24 to 30 are unused and must be
zero. Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative. Note
that the bit representation differentiates between negative and positive zero.
These values can be treated as being equal in all operations. */

#define POSITIVE 0
#define NEGATIVE 1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_long_decimal;

typedef enum {
  OK = 0,
  INF_PLUS = 1,
  INF_MINUS = 2,
  DIVISION_BY_ZERO = 3
} Arithmetic_operation_result;

// #define SUCCESS 1
// #define FAILURE 0
// #define EPSILON 1e-7L

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Note on the numbers that do not fit into the mantissa:

When getting numbers that do not fit into the mantissa during arithmetic
operations, use bank rounding (for example,
79,228,162,514,264,337,593,543,950,335 — 0.6 =
79,228,162,514,264,337,593,543,950,334) */

// Comparison Operators
/*
Return value:

0 — FALSE;
1 — TRUE.
*/

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

//To float	
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/* Return value — code error:

0 — OK;
1 — convertation error.
Note on the conversion of a float type number:

If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0.
If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error.
When processing a number with the float type, convert all the significant decimal digits contained in it. If there are more than 7 such digits, the number is rounded to the closest one that does not have more than 7 significant decimal digits.
Note on the conversion from decimal type to int:

If there is a fractional part in a decimal number, it should be discarded (for example, 0.9 is converted to 0). */

// Other functions

// Rounds a specified Decimal number to the closest integer toward negative infinity.	
int s21_floor(s21_decimal value, s21_decimal *result);

// Rounds a decimal value to the nearest integer.	
int s21_round(s21_decimal value, s21_decimal *result);

// Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes.	
int s21_truncate(s21_decimal value, s21_decimal *result);

// Returns the result of multiplying the specified Decimal value by negative one.	
int s21_negate(s21_decimal value, s21_decimal *result);

#define CALCULATION_ERROR 1
/* 
Return value — code error:

0 — OK;
1 — calculation error.
*/

/* Utility helper functions */

void s21_print_decimal_as_binary(s21_decimal *value);

int get_nth_bit_value(s21_decimal *value, int n, int *result);
int set_nth_bit_value(s21_decimal *value, int n, int value_to_set);

int get_sign_of_decimal(s21_decimal *value, int *result);
int set_sign_of_decimal(s21_decimal *value, int sign_to_set);

int get_exponent_of_decimal(s21_decimal  *value, int  *result);
int set_exponent_of_decimal(s21_decimal  *value, int exponent_to_set);

int s21_mantissa_add(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_mantissa_sub(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
#endif  // _S21_DEСIMAL_H_