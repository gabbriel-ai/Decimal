#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  error_code_convertation code = CONVERTATION_OK;

  if (s21_check_decimal(src) != 0 || !dst) {
    code = CONVERTATION_ERROR;
  } else {
    double temp = 0.0;
    for (int i = 0; i <= 95; i++) {
      if (s21_get_bit(src, i)) {
        temp += pow(2.0, i);
      }
    }
    double power = pow(10.0, s21_get_scale(src));
    temp /= power;
    if (s21_get_bit(src, 127)) {
      temp = -temp;
    }
    *dst = temp;
  }

  return code;
}
