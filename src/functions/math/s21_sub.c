#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal_reset(result);
  error_code_arithmetic code = s21_normalize(&value_1, &value_2);

  if (s21_get_bit(value_1, 127) == s21_get_bit(value_2, 127)) {
    int max_bit = fmax(s21_find_head(value_1), s21_find_head(value_2));
    if (s21_is_less(value_1, value_2) && !s21_get_bit(value_1, 127)) {
      s21_decimal temp = value_2;
      value_2 = value_1;
      value_1 = temp;
      s21_set_sign(result, 1);
    } else {
      s21_set_sign(result, s21_get_sign(value_1));
    }
    int carry = 0, diff = 0;
    for (int i = 0; i <= max_bit; i++) {
      if (s21_get_bit(value_1, i) >= s21_get_bit(value_2, i) + carry) {
        diff = s21_get_bit(value_1, i) - s21_get_bit(value_2, i) - carry;
        carry = 0;
      } else {
        diff = s21_get_bit(value_1, i) + 2 - s21_get_bit(value_2, i) - carry;
        carry = 1;
      }
      if (diff) {
        s21_set_bit(result, i, 1);
      }
    }
    if (carry) {
      code = NEGATIVE_INFINITY;
    }
    s21_set_scale(result, s21_get_scale(value_1));
  } else {
    if (s21_get_bit(value_1, 127)) {
      s21_set_bit(&value_2, 127, 1);
      code = s21_add(value_1, value_2, result);
    } else {
      s21_set_bit(&value_2, 127, 0);
      code = s21_add(value_1, value_2, result);
    }
  }

  return code;
}
