#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  error_code_convertation code = CONVERTATION_OK;

  if (s21_check_decimal(src) != 0 || !dst) {
    code = CONVERTATION_ERROR;
  } else {
    if (src.bits[1] != 0 || src.bits[2] != 0) {
      code = CONVERTATION_ERROR;
    }
    s21_decimal result = {{0, 0, 0, 0}};
    if (code == CONVERTATION_OK) code = s21_truncate(src, &result);
    if (result.bits[0] <= S21_MAX_INT32 && code == 0) {
      *dst = result.bits[0];
      if (s21_get_sign(src)) *dst *= -1;
    } else {
      code = CONVERTATION_ERROR;
    }
  }
  return code;
}