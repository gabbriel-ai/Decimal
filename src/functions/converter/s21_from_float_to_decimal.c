#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  error_code_convertation code = CONVERTATION_OK;

  if (!dst) {
    code = CONVERTATION_ERROR;
  } else {
    code = s21_check_float(src);
    s21_decimal_reset(dst);

    if (code == 0) {
      if (src < 0.0f) {
        s21_set_sign(dst, 1);
        src = -src;
      }
      unsigned int mantissa = 0;
      int scale = 0;
      s21_convert_float(src, &mantissa, &scale);
      dst->bits[0] = mantissa;
      s21_check_scale(dst, scale);
    }
  }

  return code;
}
