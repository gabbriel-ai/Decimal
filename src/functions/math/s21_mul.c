#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  error_code_arithmetic code = 0;
  s21_decimal_reset(result);
  if (s21_find_head(value_1) >= s21_find_head(value_2)) {
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit(value_1, i) == 1)
        code = s21_add(*result, s21_shift(value_2, i), result);
    }
  } else {
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit(value_2, i) == 1)
        code = s21_add(*result, s21_shift(value_1, i), result);
    }
  }
  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);
  s21_set_sign(result, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  if (scale > 28) {
    code = NEGATIVE_INFINITY;
  } else {
    s21_set_scale(result, scale);
  }
  return code;
}