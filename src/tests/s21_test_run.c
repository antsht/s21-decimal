#include "s21_test.h"

int main(void) {
  int number_failed = 0;
  number_failed = s21_negate_test();
  number_failed += s21_sandbox_test();
  number_failed += s21_from_int_to_decimal_test();
  
  printf("====================\n\n");
  printf("Total errors: %d\n\n", number_failed);
  printf("====================\n\n");

  return number_failed > 0;
}