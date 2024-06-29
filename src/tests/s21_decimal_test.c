#include "../s21_decimal.h"

#include <check.h>

// #####################################################
// COMPARSION TESTS
// #####################################################

START_TEST(is_equal_test) {
  s21_decimal value1 = {{12, 0, 0, 0}};
  s21_decimal value2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(value1, value2), 0);

  value1 = (s21_decimal){{4, 0, 0, 0}};
  value2 = (s21_decimal){{4, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(value1, value2), 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_equal(value1, value2), 1);

  value1 = (s21_decimal){{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_equal(value1, value2), 0);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  ck_assert_int_eq(s21_is_equal(value1, value2), 0);
}

START_TEST(is_not_equal_test) {
  s21_decimal value1 = {{12, 0, 0, 0}};
  s21_decimal value2 = {{3, 0, 0, 0}};
  int result = s21_is_not_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{4, 0, 0, 0}};
  value2 = (s21_decimal){{4, 0, 0, 0}};
  result = s21_is_not_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  result = s21_is_not_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  result = s21_is_not_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  result = s21_is_not_equal(value1, value2);
  ck_assert_int_eq(result, 1);
}

START_TEST(is_less_test) {
  s21_decimal value1 = {{54, 0, 0, 0}};
  s21_decimal value2 = {{5, 0, 0, 0}};
  int result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{1, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{5, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 1, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 2, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 3, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{123, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  value2 = (s21_decimal){{1, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{123, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  value2 = (s21_decimal){{123, 0, 0, 0}};
  result = s21_is_less(value1, value2);
  ck_assert_int_eq(result, 1);
}

START_TEST(is_less_or_equal_test) {
  s21_decimal value1 = {{0xFFFFFFF, 0xFFFFFFF, 0, 0}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  int result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{1, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{5, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 1, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 2, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 3, 0, 0}};
  result = s21_is_less_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);
}

START_TEST(is_greater_test) {
  s21_decimal value1 = {{54, 0, 0, 0}};
  s21_decimal value2 = {{5, 0, 0, 0}};
  int result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{123, 0, 0, 0}};
  value2 = (s21_decimal){{1, 0, 0, 0}};
  s21_set_scale(&value2, 28);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{123, 0, 0, 0}};
  value2 = (s21_decimal){{1, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  s21_set_sign(&value2, 1);
  s21_set_scale(&value2, 28);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{1, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{5, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  s21_set_sign(&value2, 1);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{5, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFFF, 1, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 2, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 3, 0, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{52, 0, 0, 0}};
  value2 = (s21_decimal){{52, 0, 0, 0}};
  s21_set_scale(&value1, 1);
  s21_set_scale(&value2, 2);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{102, 0, 0, 0}};
  value2 = (s21_decimal){{104, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  s21_set_sign(&value2, 1);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{234, 0, 0, 0}};
  value2 = (s21_decimal){{2, 0, 0, 0}};
  s21_set_scale(&value1, 2);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{123457u, 654u, 0xFFFFFFFF, 0}};
  value2 = (s21_decimal){{123456u, 654u, 0xFFFFFFFF, 0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&value1, 0);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&value2, 1);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{2138, 0, 0, 0}};
  value2 = (s21_decimal){{1, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0x99999999, 0x99999999, 0x19999999, 0x0}};
  value2 = (s21_decimal){{0x1, 0x0, 0x0, 0x80000000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0x1, 0x0, 0x0, 0x80000000}};
  value2 = (s21_decimal){{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  value2 = (s21_decimal){{0x1, 0x0, 0x0, 0x80000000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0x1E078, 0x0, 0x0, 0x50000}};
  value2 = (s21_decimal){{0x1, 0x0, 0x0, 0x80000000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0x5554D320, 0x8235, 0x0, 0x80050000}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  value2 = (s21_decimal){{0x0, 0x0, 0x0, 0x1C0000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0x0, 0x0, 0x0, 0x1C0000}};
  value2 = (s21_decimal){{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0x1, 0x0, 0x0, 0x80000000}};
  value2 = (s21_decimal){{0x1, 0x0, 0x0, 0x1C0000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0xA, 0x0, 0x0, 0x10000}};
  value2 = (s21_decimal){{0x1, 0x0, 0x0, 0x1C0000}};
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  value2 = (s21_decimal){{2, 0, 0, 0}};
  s21_set_scale(&value2, 28);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{2, 0, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  s21_set_sign(&value2, 1);
  s21_set_scale(&value1, 28);
  result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);
}

START_TEST(is_greater_or_equal_test) {
  s21_decimal value1 = {{0xFFFF, 0, 0, 0}};
  s21_decimal value2 = {{0xFF, 0, 0, 0}};
  int result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{1, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{0, 0, 0, 0}};
  value2 = (s21_decimal){{0, 0, 0, 0}};
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{5, 0, 0, 0}};
  value2 = (s21_decimal){{5, 0, 0, 0}};
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 1, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);

  value1 = (s21_decimal){{0xFFFFFFFF, 2, 0, 0}};
  value2 = (s21_decimal){{0xFFFFFFFF, 3, 0, 0}};
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);

  value1 = (s21_decimal){{5125, 0, 0, 0}};
  value2 = (s21_decimal){{5125, 0, 0, 0}};
  s21_set_sign(&value1, 1);
  result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);
}

// #####################################################
// CONVERSION TESTS
// #####################################################

START_TEST(to_float_test) {
  s21_decimal decimal = {{1, 0, 0, 0}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 1);

  decimal = (s21_decimal){{15238, 0, 0, 0}};
  number = 0;
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 15238);

  s21_set_scale(&decimal, 3);
  number = 0;
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 15.238);

  decimal = (s21_decimal){{823589, 0, 0, 0}};
  s21_set_scale(&decimal, 3);
  s21_set_sign(&decimal, 1);
  number = 0;
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, -823.589);

  decimal = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  result = s21_from_decimal_to_float(decimal, NULL);
  ck_assert_int_eq(result, 1);

  decimal = (s21_decimal){{-1, 0, 0, 0x1D0000}};
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);

  decimal = (s21_decimal){{-1, 0, 0, 0x1C8000}};
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);

  decimal = (s21_decimal){{-1, 0, 0, 0x11C0000}};
  result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);
}

START_TEST(to_int_test) {
  s21_decimal decimal = {{1, 0, 0, 0}};
  int number = 0;
  int result = s21_from_decimal_to_int(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(number, 1);

  decimal = (s21_decimal){{15238, 0, 0, 0}};
  number = 0;
  result = s21_from_decimal_to_int(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(number, 15238);

  decimal = (s21_decimal){{828, 0, 0, 0}};
  s21_set_sign(&decimal, 1);
  number = 0;
  result = s21_from_decimal_to_int(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(number, -828);

  decimal = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  number = 0;
  result = s21_from_decimal_to_int(decimal, &number);
  ck_assert_int_eq(result, 1);
}

START_TEST(from_float_test) {
  float number = 1.0f;
  s21_decimal decimal;
  s21_decimal need_result = {{1, 0, 0, 0}};
  int result = s21_from_float_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = 5.245f;
  need_result = (s21_decimal){{5245000, 0, 0, 0}};
  s21_set_scale(&need_result, 6);
  result = s21_from_float_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = -352.785f;
  need_result = (s21_decimal){{3527850, 0, 0, 0}};
  s21_set_scale(&need_result, 4);
  s21_set_sign(&need_result, 1);
  result = s21_from_float_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = 52935856.0f;
  need_result = (s21_decimal){{52935860, 0, 0, 0}};
  result = s21_from_float_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = 21111111.0f;
  need_result = (s21_decimal){{21111110, 0, 0, 0}};
  result = s21_from_float_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);
}

START_TEST(from_int_test) {
  int number = 0;
  s21_decimal decimal;
  s21_decimal need_result = {{0, 0, 0, 0}};
  int result = s21_from_int_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = 5;
  need_result = (s21_decimal){{5, 0, 0, 0}};
  result = s21_from_int_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);

  number = -3529785;
  need_result = (s21_decimal){{3529785, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_from_int_to_decimal(number, &decimal);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(decimal, need_result), 1);
}

// #####################################################
// MATH TESTS
// #####################################################

START_TEST(add_test) {
  s21_decimal value_1 = {{0, 0, 0, 0}};  // 0 + 0
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal add_result = {{0, 0, 0, 0}};
  s21_decimal need_result = {{0, 0, 0, 0}};
  int result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{5, 0, 0, 0}};  // 5 + 2
  value_2 = (s21_decimal){{2, 0, 0, 0}};
  need_result = (s21_decimal){{7, 0, 0, 0}};
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{5, 0, 0, 0}};  // 5 + (-2)
  value_2 = (s21_decimal){{2, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  need_result = (s21_decimal){{3, 0, 0, 0}};
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{2478, 0, 0, 0}};  // 2.478 + 2
  value_2 = (s21_decimal){{2, 0, 0, 0}};
  need_result = (s21_decimal){{4478, 0, 0, 0}};
  s21_set_scale(&value_1, 3);
  s21_set_scale(&need_result, 3);
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{4, 0, 0, 0}};  // 4 + 12.45
  value_2 = (s21_decimal){{1245, 0, 0, 0}};
  need_result = (s21_decimal){{1645, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_set_scale(&need_result, 2);
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{250, 0, 0, 0}};  // -250 + (-24)
  value_2 = (s21_decimal){{24, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  need_result = (s21_decimal){{274, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{5, 0, 0, 0}};  // -5 + 3
  value_2 = (s21_decimal){{3, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  need_result = (s21_decimal){{2, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(add_result, need_result), 1);

  value_1 = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Краевое
  value_2 = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}};
  result = s21_add(value_1, value_2, &add_result);
  ck_assert_int_eq(result, 1);
}

START_TEST(div_test) {
  s21_decimal value_1 = {{15, 0, 0, 0}};  // 15 / 0 = ERROR DIV
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal div_result = {{0, 0, 0, 0}};
  s21_decimal need_result = {{0, 0, 0, 0}};
  int result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 3);

  value_1 = (s21_decimal){{260, 0, 0, 0}};  // 260 / 10
  value_2 = (s21_decimal){{10, 0, 0, 0}};
  need_result = (s21_decimal){{26, 0, 0, 0}};
  result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(div_result, need_result), 1);

  value_1 = (s21_decimal){{4829, 0, 0, 0}};  // 48.29 / -1
  value_2 = (s21_decimal){{1, 0, 0, 0}};
  s21_set_scale(&value_1, 2);
  s21_set_sign(&value_2, 1);
  need_result = (s21_decimal){{4829, 0, 0, 0}};
  s21_set_scale(&need_result, 2);
  s21_set_sign(&need_result, 1);
  result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(div_result, need_result), 1);

  value_1 = (s21_decimal){{2918, 0, 0, 0}};  // 2918 / 1
  value_2 = (s21_decimal){{1, 0, 0, 0}};
  need_result = (s21_decimal){{2918, 0, 0, 0}};
  result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(div_result, need_result), 1);

  value_1 = (s21_decimal){{14182, 0, 0, 0}};  // 14182 / 14182
  value_2 = (s21_decimal){{14182, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(div_result, need_result), 1);

  value_1 = (s21_decimal){{12, 0, 0, 0}};  // 0.12 / 0.003
  value_2 = (s21_decimal){{3, 0, 0, 0}};
  s21_set_scale(&value_1, 2);
  s21_set_scale(&value_2, 3);
  need_result = (s21_decimal){{40, 0, 0, 0}};
  result = s21_div(value_1, value_2, &div_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(div_result, need_result), 1);
}

START_TEST(mul_test) {
  s21_decimal value_1 = {{0, 0, 0, 0}};  // 0 * 0
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal mul_result = {{0, 0, 0, 0}};
  s21_decimal need_result = {{0, 0, 0, 0}};
  int result = s21_mul(value_1, value_2, &mul_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(mul_result, need_result), 1);

  value_1 = (s21_decimal){{26, 0, 0, 0}};  // 26 * 10
  value_2 = (s21_decimal){{10, 0, 0, 0}};
  need_result = (s21_decimal){{260, 0, 0, 0}};
  result = s21_mul(value_1, value_2, &mul_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(mul_result, need_result), 1);

  value_1 = (s21_decimal){{26, 0, 0, 0}};  // -26 * 10
  value_2 = (s21_decimal){{10, 0, 0, 0}};
  need_result = (s21_decimal){{260, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&need_result, 1);
  result = s21_mul(value_1, value_2, &mul_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(mul_result, need_result), 1);

  value_1 = (s21_decimal){{0, 0, 0, 0}};  // 0 * 10
  value_2 = (s21_decimal){{10, 0, 0, 0}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  result = s21_mul(value_1, value_2, &mul_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(mul_result, need_result), 1);
}

START_TEST(sub_test) {
  s21_decimal value_1 = {{15, 0, 0, 0}};  // 15 - 4
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal sub_result = {{0, 0, 0, 0}};
  s21_decimal need_result = {{11, 0, 0, 0}};
  int result = s21_sub(value_1, value_2, &sub_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(sub_result, need_result), 1);

  value_1 = (s21_decimal){{2, 0, 0, 0}};  // 2 - 59
  value_2 = (s21_decimal){{59, 0, 0, 0}};
  need_result = (s21_decimal){{57, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_sub(value_1, value_2, &sub_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(sub_result, need_result), 1);

  value_1 = (s21_decimal){{58294, 0, 0, 0}};  // 58.294 - 4
  value_2 = (s21_decimal){{4, 0, 0, 0}};
  need_result = (s21_decimal){{54294, 0, 0, 0}};
  s21_set_scale(&value_1, 3);
  s21_set_scale(&need_result, 3);
  result = s21_sub(value_1, value_2, &sub_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(sub_result, need_result), 1);

  value_1 = (s21_decimal){{5, 0, 0, 0}};  // -5 - 2
  value_2 = (s21_decimal){{2, 0, 0, 0}};
  need_result = (s21_decimal){{7, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&need_result, 1);
  result = s21_sub(value_1, value_2, &sub_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(sub_result, need_result), 1);

  value_1 = (s21_decimal){{5, 0, 0, 0}};  // 5 - (-2)
  value_2 = (s21_decimal){{2, 0, 0, 0}};
  need_result = (s21_decimal){{7, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  result = s21_sub(value_1, value_2, &sub_result);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(sub_result, need_result), 1);
}

// #####################################################
// OTHER TESTS
// #####################################################

START_TEST(floor_test) {
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_decimal value = {{512, 0, 0, 0}};
  s21_decimal need_result = {{51, 0, 0, 0}};
  s21_set_scale(&value, 1);
  int result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  s21_set_sign(&value, 1);
  need_result = (s21_decimal){{52, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{5106, 0, 0, 0}};
  need_result = (s21_decimal){{511, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  need_result = (s21_decimal){{75, 0, 0, 0}};
  value = (s21_decimal){{7444923, 0, 0, 0}};
  s21_set_scale(&value, 5);
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(s21_is_equal(need_result, floor), 1);
  ck_assert_int_eq(result, 0);

  value = (s21_decimal){{5101, 0, 0, 0}};
  need_result = (s21_decimal){{511, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{1246, 0, 0, 0}};
  need_result = (s21_decimal){{124, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{2, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{12, 0, 0, 0}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_scale(&value, 2);
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  need_result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  need_result = (s21_decimal){{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  need_result = (s21_decimal){{0xF485787B, 0x7F29ABCA, 0x1AD, 0x80000000}};
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  need_result = (s21_decimal){{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(floor, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  result = s21_floor(value, &floor);
  ck_assert_int_eq(result, 1);
}

START_TEST(negate_test) {
  s21_decimal negate = {{0, 0, 0, 0}};
  s21_decimal value = {{512, 0, 0, 0}};
  s21_decimal need_result = {{512, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  int result = s21_negate(value, &negate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(negate, need_result), 1);

  s21_set_sign(&need_result, 0);
  result = s21_negate(negate, &negate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(negate, need_result), 1);

  value = (s21_decimal){{0, 0, 0, 0}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_negate(value, &negate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(negate, need_result), 1);
}

START_TEST(round_test) {
  s21_decimal round = {{0, 0, 0, 0}};
  s21_decimal value = {{512, 0, 0, 0}};
  s21_decimal need_result = {{51, 0, 0, 0}};
  s21_set_scale(&value, 1);
  int result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{516, 0, 0, 0}};
  need_result = (s21_decimal){{52, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{568, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_scale(&value, 2);
  need_result = (s21_decimal){{6, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{516, 0, 0, 0}};
  need_result = (s21_decimal){{52, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{516, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_scale(&value, 1);
  need_result = (s21_decimal){{52, 0, 0, 0}};
  s21_set_sign(&need_result, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{5106, 0, 0, 0}};
  need_result = (s21_decimal){{511, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{5101, 0, 0, 0}};
  need_result = (s21_decimal){{510, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{1246, 0, 0, 0}};
  need_result = (s21_decimal){{125, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);

  value = (s21_decimal){{12, 0, 0, 0}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_scale(&value, 2);
  result = s21_round(value, &round);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(round, need_result), 1);
}

START_TEST(truncate_test) {
  s21_decimal truncate = {{0, 0, 0, 0}};
  s21_decimal value = {{512, 0, 0, 0}};
  s21_decimal need_result = {{51, 0, 0, 0}};
  s21_set_scale(&value, 1);
  int result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{516, 0, 0, 0}};
  need_result = (s21_decimal){{51, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{516, 0, 0, 0}};
  need_result = (s21_decimal){{51, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{5106, 0, 0, 0}};
  need_result = (s21_decimal){{510, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{5101, 0, 0, 0}};
  need_result = (s21_decimal){{510, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{1246, 0, 0, 0}};
  need_result = (s21_decimal){{124, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_sign(&need_result, 1);
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{11, 0, 0, 0}};
  need_result = (s21_decimal){{1, 0, 0, 0}};
  s21_set_scale(&value, 1);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{12, 0, 0, 0}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_scale(&value, 2);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  need_result = (s21_decimal){{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  need_result = (s21_decimal){{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};
  s21_set_scale(&value, 10);
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
  need_result = (s21_decimal){{0x68497681, 0x1C25C2, 0x0, 0x0}};
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_is_equal(truncate, need_result), 1);

  value = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  result = s21_truncate(value, NULL);
  ck_assert_int_eq(result, 1);

  value = (s21_decimal){{0, 0, 0, 0x1D0000}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 1);

  value = (s21_decimal){{-1, 0, 0, 0x11C0000}};
  need_result = (s21_decimal){{0, 0, 0, 0}};
  result = s21_truncate(value, &truncate);
  ck_assert_int_eq(result, 1);
}

Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("DECIMAL SUITE");
  tc_core = tcase_create("DECIMAL CORE");
  tcase_set_timeout(tc_core, 1000);
  tcase_add_test(tc_core, is_equal_test);
  tcase_add_test(tc_core, is_not_equal_test);
  tcase_add_test(tc_core, is_less_test);
  tcase_add_test(tc_core, is_less_or_equal_test);
  tcase_add_test(tc_core, is_greater_test);
  tcase_add_test(tc_core, is_greater_or_equal_test);

  tcase_add_test(tc_core, to_float_test);
  tcase_add_test(tc_core, to_int_test);
  tcase_add_test(tc_core, from_float_test);
  tcase_add_test(tc_core, from_int_test);

  tcase_add_test(tc_core, add_test);
  tcase_add_test(tc_core, div_test);
  tcase_add_test(tc_core, mul_test);
  tcase_add_test(tc_core, sub_test);

  tcase_add_test(tc_core, floor_test);
  tcase_add_test(tc_core, negate_test);
  tcase_add_test(tc_core, round_test);
  tcase_add_test(tc_core, truncate_test);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}