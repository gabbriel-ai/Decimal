#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  error_code_comparasion code = FALSE;
  if (!s21_is_equal(value_1, value_2)) {
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      s21_normalize(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        if (s21_get_bit(value_1, i) ^ s21_get_bit(value_2, i)) {
          code = s21_get_bit(value_2, i);
          break;
        }
      }
    } else if (s21_get_sign(value_1) ^ s21_get_sign(value_2)) {
      code = s21_get_sign(value_1) ? FALSE : TRUE;

    } else {
      s21_normalize(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        if (s21_get_bit(value_1, i) ^ s21_get_bit(value_2, i)) {
          code = s21_get_bit(value_2, i);
          break;
        }
      }
      code = !code;
    }
  }

  return code;
}