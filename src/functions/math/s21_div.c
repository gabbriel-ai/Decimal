#include "../../s21_decimal.h"

int s21_is_zero(s21_decimal value) {
  return value.bits[0] == value.bits[1] && value.bits[1] == value.bits[2] &&
         value.bits[2] == value.bits[3];
}

int s21_check_specific_values(s21_decimal value_1, s21_decimal value_2,
                              s21_decimal *result) {
  int return_value = 0;
  if (s21_is_equal(value_1, value_2)) {
    result->bits[0] = 1;
    return_value = 1;
  } else if (s21_is_equal(value_2, (s21_decimal){{1, 0, 0, 0}})) {
    result->bits[0] = value_1.bits[0];
    result->bits[1] = value_1.bits[1];
    result->bits[2] = value_1.bits[2];
    s21_set_scale(result, s21_get_scale(value_1));
    return_value = 1;
  }
  return return_value;
}

int s21_check_div_sign(s21_decimal value_1, s21_decimal value_2) {
  return s21_get_bit(value_1, 127) ^ s21_get_bit(value_2, 127);
}

void s21_div_mantiss(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;

  int count_used_numbers = 0;
  s21_decimal divider_decimal = value_2;
  int shift = 0, temp = 0;
  while (s21_is_greater(value_1, value_2)) {
    shift = 0;
    while (s21_is_greater(value_1, divider_decimal) &&
           s21_find_head(divider_decimal) != s21_find_head(value_1)) {
      shift++;
      divider_decimal = s21_shift(value_2, shift);
      if (s21_is_less(value_1, divider_decimal)) {
        shift--;
        divider_decimal = s21_shift(value_2, shift);
        break;
      }
    }
    while (temp - shift > 1) {
      *result = s21_shift(*result, 1);
      s21_set_bit(result, 0, 0);
      temp--;
    }
    temp = shift;
    s21_decimal sub_result = {{0, 0, 0, 0}};
    s21_sub(value_1, divider_decimal, &sub_result);
    count_used_numbers = shift;
    *result = s21_shift(*result, 1);
    s21_set_bit(result, 0, 1);
    value_1 = sub_result;
    divider_decimal = value_2;
  }
  *result = s21_shift(*result, count_used_numbers);
}

int s21_count_scale(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  int code = 0;
  int scale = s21_get_scale(value_1) - s21_get_scale(value_2);
  if (scale < 0) {
    scale = -scale;
    while (scale > 0) {
      s21_decimal temp = {{0, 0, 0, 0}};
      code = s21_mul(*result, (s21_decimal){{10, 0, 0, 0}}, &temp);
      *result = temp;
      scale--;
    }
  }
  s21_set_scale(result, scale);
  return code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  error_code_arithmetic code = OK;
  if (s21_is_zero(value_2)) {
    code = DIVISION_ZERO;
  } else {
    s21_decimal_reset(result);
    s21_set_sign(result, (s21_check_div_sign(value_1, value_2)));
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    if (s21_check_specific_values(value_1, value_2, result) == 0) {
      s21_div_mantiss(value_1, value_2, result);
      code = s21_count_scale(value_1, value_2, result);
    }
  }
  return code;
}