#ifndef s21_DECIMAL_H
#define s21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_BUFFER 64
#define S21_MAX_FLOAT 79228162514264337593543950335.0F
#define S21_MIN_FLOAT 1E-28
#define S21_MAX_INT32 2147483647
#define S21_MAX_UINT 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef enum {
  OK = 0,
  POSITIVE_INFINITY = 1,
  NEGATIVE_INFINITY = 2,
  DIVISION_ZERO = 3
} error_code_arithmetic;

typedef enum { FALSE = 0, TRUE = 1 } error_code_comparasion;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} error_code_convertation;

typedef enum {
  CALCULATION_OK = 0,
  CALCULATION_ERROR = 1
} error_code_additional;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_sign(s21_decimal value);
void s21_decimal_reset(s21_decimal *value);
void s21_set_scale(s21_decimal *value, int scale);
int s21_get_scale(s21_decimal value);
int s21_get_bit(s21_decimal value, int index);
void s21_set_bit(s21_decimal *value, int index, int number);
s21_decimal s21_shift(s21_decimal value, int shift_value);
int s21_check_decimal(s21_decimal value);
int s21_find_head(s21_decimal value);
int s21_check_nan(s21_decimal value);
int s21_check_inf(s21_decimal value);
int s21_check_last_bit(s21_decimal value);
int s21_check_correct_power(s21_decimal value);
int s21_check_decimal(s21_decimal value);
int s21_check_float(float value);
void s21_convert_float(float src, unsigned int *mantissa, int *scale);
int s21_check_scale(s21_decimal *dst, int scale);
#endif