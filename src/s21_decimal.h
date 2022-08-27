#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int bits[4];
} s21_decimal;

// Arithmetic operations
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  // done
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  // done
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  // done
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  // done
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison operators
int s21_is_less(s21_decimal val_1, s21_decimal val_2);
int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_greater(s21_decimal val_1, s21_decimal val_2);
int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Additional functions
int s21_get_scale(s21_decimal value);
void s21_set_zero_for_result(s21_decimal *n);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_positive(s21_decimal *value);
void s21_set_negative(s21_decimal *value);
int s21_count_active_bits(int bits[], int size);
int s21_compare_bits(int bits_1[], int bits_2[], int size_1, int size_2);
void s21_buf_multiplier(int bits_1[], int bits_2[], int mul_size, int res[], int size);
void s21_clear_all_bits(int bits[], int size);
void s21_mul_self_by_ten(int bits[]);
void s21_add_buffs(int val_1[], int size_1, int val_2[], int size_2, int result[], int size);
void s21_bits_copy(int bit_1[], int bit_2[], int size);
void s21_right_shifter(int bits[], int size, int by);
void s21_trunc_last_digit(int bits[], int scale, int round);  // only for bits >= 10
void s21_buff_division(int divid[], int divid_len, int devis[],
                        int devis_len, int res[], int res_len, int rem[], int rem_len);
char *generate_binary_string(int src);
int get_point_position(s21_decimal src);
void s21_buff_sub(int bits_1[], int size_1, int bits_2[], int size_2, int res[], int res_len);
void s21_bit_printer(int bits[], int size);
void s21_set_inf(s21_decimal *val);
int s21_is_inf(s21_decimal val);
void s21_filter_val(s21_decimal *val);

// Bit manipulators
void s21_set_bit(int arr[], int k);
void s21_clear_bit(int arr[], int k);
int s21_test_bit(int arr[], int k);

#endif  // SRC_S21_DECIMAL_H_
