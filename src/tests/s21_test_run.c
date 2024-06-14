#include "s21_test.h"

int main(void) {
  int number_failed = 0;
  number_failed = s21_create_matrix_test();
  number_failed += s21_misc_test();
  printf("====================\n\n");
  printf("Total errors: %d\n\n", number_failed);
  printf("====================\n\n");

  return number_failed > 0;
}