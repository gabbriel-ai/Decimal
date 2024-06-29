#include "../../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  error_code_arithmetic code = 0;
  s21_decimal_reset(result);
  code = s21_normalize(&value_1, &value_2);
  int carry = 0;
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    for (int i = 0; i < 96; i++) {
      s21_set_bit(
          result, i,
          (s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + carry) % 2);
      carry = (s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + carry) / 2;
    }
    s21_set_sign(result, s21_get_sign(value_1));
    if (carry != 0) {
      code = POSITIVE_INFINITY;
    }
  } else {
    if (s21_get_sign(value_1)) {
      s21_set_sign(&value_1, 0);
      code = s21_sub(value_2, value_1, result);
    } else {
      s21_set_sign(&value_2, 0);
      code = s21_sub(value_1, value_2, result);
    }
  }
  s21_set_scale(result, s21_get_scale(value_2));
  return code;
}