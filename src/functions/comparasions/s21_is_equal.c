#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_normalize(&value_1, &value_2);
  error_code_comparasion code = TRUE;
  for (int i = 0; i <= 127; i++) {
    if (s21_get_bit(value_1, i) != s21_get_bit(value_2, i)) {
      code = FALSE;
      break;
    }
  }
  return code;
}