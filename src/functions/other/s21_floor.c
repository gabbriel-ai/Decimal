#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  error_code_additional code = CALCULATION_OK;
  if (s21_check_decimal(value) || !result) {
    code = CALCULATION_ERROR;
  } else {
    s21_decimal_reset(result);
    s21_decimal truncate;
    s21_decimal fractional;
    code = s21_truncate(value, &truncate);
    code = s21_sub(value, truncate, &fractional);
    if (s21_get_bit(value, 127)) {
      if (fractional.bits[0] != 0 || fractional.bits[1] != 0 ||
          fractional.bits[2] != 0) {
        s21_decimal negative_one = (s21_decimal){{1, 0, 0, 0}};
        s21_set_sign(&negative_one, 1);
        code = s21_add(truncate, negative_one, result);
      }
    } else {
      *result = truncate;
    }
  }

  return code;
}