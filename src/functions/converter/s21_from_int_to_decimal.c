#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  error_code_convertation code = CONVERTATION_OK;

  if (!dst) {
    code = CONVERTATION_ERROR;
  } else {
    s21_decimal_reset(dst);
    if (src < 0) {
      src = src * (-1);
      s21_set_sign(dst, 1);
    }
    dst->bits[0] = src;
  }

  return code;
}