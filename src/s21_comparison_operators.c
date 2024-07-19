#include "s21_decimal.h"

// Comparison Operators
/*
Return value:

0 — FALSE;
1 — TRUE.
*/

#define FALSE 0
#define TRUE 1

// Less than	<
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_less(l_value_1, l_value_2);
}

// Less than or equal to	<=
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_less_or_equal(l_value_1, l_value_2);
}

// Greater than	>
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_greater(l_value_1, l_value_2);
}

// Greater than or equal to	>=
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_greater_or_equal(l_value_1, l_value_2);
}

// Equal to	==
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_equal(l_value_1, l_value_2);
}

// Not equal to	!=
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal l_value_1, l_value_2;
  s21_from_decimal_to_long_decimal(value_1, &l_value_1);
  s21_from_decimal_to_long_decimal(value_2, &l_value_2);
  return s21_long_decimal_is_not_equal(l_value_1, l_value_2);
}

int s21_long_decimal_is_less(s21_long_decimal l_value_1,
                             s21_long_decimal l_value_2) {
  if (s21_long_decimal_is_equal(l_value_1, l_value_2)) return FALSE;
  int sign_1 = 0, sign_2 = 0;
  int result = FALSE;
  s21_get_sign_of_long_decimal(&l_value_1, &sign_1);
  s21_get_sign_of_long_decimal(&l_value_2, &sign_2);
  s21_long_decimal_normalize_scale(&l_value_1, &l_value_2);

  if (sign_1 == NEGATIVE && sign_2 == POSITIVE) {
    result = FALSE;
    for (int i = (LONG_DECIMAL_SIZE - 2); i >= 0; i--)
      if (l_value_1.bits[i] || l_value_2.bits[i]) result = TRUE;
  } else if (sign_1 == POSITIVE && sign_2 == NEGATIVE) {
    result = FALSE;
  } else if (sign_1 == NEGATIVE && sign_2 == NEGATIVE) {
    result = TRUE;
    for (int i = (LONG_DECIMAL_SIZE - 2); i >= 0; i--) {
      if (l_value_1.bits[i] == 0 && l_value_2.bits[i] == 0) continue;
      ;
      if (l_value_1.bits[i] < l_value_2.bits[i]) result = FALSE;
      if (l_value_1.bits[i] > l_value_2.bits[i]) break;
    }
  } else if (sign_1 == POSITIVE && sign_2 == POSITIVE) {
    result = TRUE;

    for (int i = (LONG_DECIMAL_SIZE - 2); i >= 0; i--) {
      if (l_value_1.bits[i] == 0 && l_value_2.bits[i] == 0) continue;
      if (l_value_1.bits[i] > l_value_2.bits[i]) result = FALSE;
      if (l_value_1.bits[i] < l_value_2.bits[i]) break;
    }
  }
  return result;
}

int s21_long_decimal_is_less_or_equal(s21_long_decimal l_value_1,
                                      s21_long_decimal l_value_2) {
  return s21_long_decimal_is_less(l_value_1, l_value_2) ||
         s21_long_decimal_is_equal(l_value_1, l_value_2);
}

int s21_long_decimal_is_greater(s21_long_decimal l_value_1,
                                s21_long_decimal l_value_2) {
  return !s21_long_decimal_is_less_or_equal(l_value_1, l_value_2);
}

int s21_long_decimal_is_greater_or_equal(s21_long_decimal l_value_1,
                                         s21_long_decimal l_value_2) {
  return !s21_long_decimal_is_less(l_value_1, l_value_2);
}

int s21_long_decimal_is_equal(s21_long_decimal l_value_1,
                              s21_long_decimal l_value_2) {
  int sign_1 = 0, sign_2 = 0;
  int result = TRUE;
  s21_get_sign_of_long_decimal(&l_value_1, &sign_1);
  s21_get_sign_of_long_decimal(&l_value_2, &sign_2);
  s21_long_decimal_normalize_scale(&l_value_1, &l_value_2);
  if (sign_1 != sign_2 && !s21_long_decimal_is_zero(&l_value_1) &&
      !s21_long_decimal_is_zero(&l_value_2))
    result = FALSE;
  if (result == TRUE) {
    for (int i = 0; i < (LONG_DECIMAL_SIZE - 1); i++) {
      if (l_value_1.bits[i] != l_value_2.bits[i]) result = FALSE;
    }
  }
  return result;
}

int s21_long_decimal_is_not_equal(s21_long_decimal l_value_1,
                                  s21_long_decimal l_value_2) {
  return !s21_long_decimal_is_equal(l_value_1, l_value_2);
}
