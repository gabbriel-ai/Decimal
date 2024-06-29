#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  error_code_additional code = CALCULATION_OK;
  if (s21_check_decimal(value) || !result) {
    code = CALCULATION_ERROR;
  } else {
    s21_decimal_reset(result);
    *result = value;
    for (int i = 0; i < s21_get_scale(value); i++) {
      unsigned long long overflow = result->bits[2];
      for (int j = 2; j >= 0; j--) {
        result->bits[j] = overflow / 10;
        overflow %= 10;
        overflow *= S21_MAX_UINT + 1;
        overflow += result->bits[j ? j - 1 : j];
      }
    }
    result->bits[3] = 0;
    s21_set_sign(result, s21_get_sign(value));
  }

  return code;
}