#include "../../s21_decimal.h"

int s21_check_nan(s21_decimal value) {
  int return_value = 1;
  for (int i = 111; i <= 118; i++) {
    if (s21_get_bit(value, i) == 0) return_value = 0;
  }
  return return_value;
}

int s21_check_inf(s21_decimal value) {
  int return_value = 1;
  for (int i = 111; i <= 118; i++) {
    if (s21_get_bit(value, i) == 0) return_value = 0;
  }
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(value, i) == 1) return_value = 0;
  }
  return return_value;
}

int s21_check_last_bit(s21_decimal value) {
  int return_value = 0;
  for (int i = 127; i >= 96; i--) {
    if (s21_get_bit(value, i)) {
      if (i != 127 && (i < 112 || i > 119)) {
        return_value = 1;
      }
    }
  }
  return return_value;
}

int s21_check_correct_power(s21_decimal value) {
  return s21_get_scale(value) < 0 || s21_get_scale(value) > 28;
}

int s21_check_decimal(s21_decimal value) {
  return s21_check_nan(value) || s21_check_correct_power(value) ||
         s21_check_inf(value) || s21_check_last_bit(value);
}

int s21_find_head(s21_decimal value) {
  int position_bit = -1;
  for (int i = 95; i >= 0 && position_bit == -1; i--) {
    if (s21_get_bit(value, i)) position_bit = i;
  }
  return position_bit;
}

void s21_decimal_reset(s21_decimal* value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

s21_decimal s21_shift(s21_decimal value, int shift_value) {
  s21_decimal temp = value;
  if (shift_value > 0) {
    while (shift_value != 0) {
      for (int i = 95; i >= 0; i--) {
        if (i != 0) {
          s21_set_bit(&temp, i, s21_get_bit(temp, i - 1));
        } else {
          s21_set_bit(&temp, i, 0);
        }
      }
      shift_value--;
    }
  } else {
    while (shift_value != 0) {
      for (int i = 95; i >= 0; i--) {
        if (i != 0) {
          s21_set_bit(&temp, i, s21_get_bit(temp, i + 1));
        } else {
          s21_set_bit(&temp, i, 0);
        }
      }
      shift_value--;
    }
  }
  return temp;
}

int s21_normalize(s21_decimal* value_1, s21_decimal* value_2) {
  error_code_arithmetic code = OK;
  int scale_1 = s21_get_scale(*value_1);
  int scale_2 = s21_get_scale(*value_2);
  if (scale_2 < scale_1) {
    s21_set_scale(value_2, 0);
    while (scale_2 != scale_1 && code == 0) {
      code = s21_mul(*value_2, (s21_decimal){{10, 0, 0, 0}}, value_2);
      scale_2++;
    }
    s21_set_scale(value_2, scale_1);
  } else {
    s21_set_scale(value_1, 0);
    while (scale_2 != scale_1 && code == 0) {
      code = s21_mul(*value_1, (s21_decimal){{10, 0, 0, 0}}, value_1);
      scale_1++;
    }
    s21_set_scale(value_1, scale_2);
  }
  return code;
}

int s21_check_float(float value) {
  int return_value = 0;

  if (isinf(value) || isnan(value)) {
    return_value = 1;
  }
  if (fabs(value) > S21_MAX_FLOAT) {
    return_value = 1;
  }
  if (fabs(value) < S21_MIN_FLOAT) {
    return_value = 1;
  }

  return return_value;
}

void s21_convert_float(float src, unsigned int* mantissa, int* scale) {
  char mas[S21_BUFFER] = {0}, temp[S21_BUFFER] = {0};
  sprintf(mas, "%.6E", src);
  temp[0] = mas[0];
  for (int i = 2; i <= 7; i++) {
    temp[i - 1] = mas[i];
  }
  *mantissa = atoi(temp);
  memset(temp, 0, S21_BUFFER);
  for (int i = 9; i <= 11; i++) {
    temp[i - 9] = mas[i];
  }
  temp[3] = '\0';
  *scale = atoi(temp) - 6;
}

int s21_check_scale(s21_decimal* dst, int scale) {
  int return_value = 0;
  if (scale < 0) {
    s21_set_scale(dst, -scale);
  } else {
    while (scale > 0) {
      s21_decimal temp = {{0, 0, 0, 0}};
      return_value = s21_mul(*dst, (s21_decimal){{10, 0, 0, 0}}, &temp);
      *dst = temp;
      scale--;
    }
  }
  return return_value;
}