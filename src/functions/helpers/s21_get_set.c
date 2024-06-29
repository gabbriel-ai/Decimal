#include "../../s21_decimal.h"

int s21_get_bit(s21_decimal value, int index) {
  return (value.bits[index / 32] >> (index % 32)) & 1;
}

void s21_set_bit(s21_decimal* value, int index, int number) {
  int array_position = index / 32;
  int bit_position = index % 32;

  if (number == 1) {
    value->bits[array_position] |= (1 << bit_position);
  } else {
    value->bits[array_position] &= ~(1 << bit_position);
  }
}

int s21_get_sign(s21_decimal value) { return s21_get_bit(value, 127); }

void s21_set_sign(s21_decimal* value, int sign) {
  s21_set_bit(value, 127, sign);
}

int s21_get_scale(s21_decimal value) { return (value.bits[3] << 1) >> 17; }

void s21_set_scale(s21_decimal* value, int scale) {
  int sign = s21_get_sign(*value);
  value->bits[3] = 0;
  value->bits[3] |= scale << 16;
  s21_set_sign(value, sign);
}