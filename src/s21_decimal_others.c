#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    s21_set_zero_for_result(result);
    int ret_value = 0;

    int scale = s21_get_scale(value);
    if (scale) {
        int bits[7];
        s21_clear_all_bits(bits, 7);
        s21_bits_copy(bits, value.bits, 96);
        s21_trunc_last_digit(bits, scale, 0);
        if (s21_test_bit(value.bits, 127)) {
            s21_set_negative(result);
            int one[1] = {0};
            s21_set_bit(one, 0);
            int tmp[7];
            s21_clear_all_bits(tmp, 7);
            s21_add_buffs(bits, 7 * 32, one, 32, tmp, 7 * 32);
            s21_bits_copy(bits, tmp, 7 * 32);
        }
        s21_bits_copy(result->bits, bits, 96);
    } else {
        s21_bits_copy(result->bits, value.bits, 128);
    }

    return ret_value;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    s21_set_zero_for_result(result);
    int ret_value = 0;

    int scale = s21_get_scale(value);
    if (scale) {
        int bits[7];
        s21_clear_all_bits(bits, 7);
        s21_bits_copy(bits, value.bits, 96);
        s21_trunc_last_digit(bits, scale, 1);
        if (s21_test_bit(value.bits, 127)) {
            s21_set_negative(result);
        }
        s21_bits_copy(result->bits, bits, 96);
    } else {
        s21_bits_copy(result->bits, value.bits, 128);
    }

    return ret_value;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_set_zero_for_result(result);
    int ret_value = 0;

    int scale = s21_get_scale(value);
    if (scale) {
        int bits[7];
        s21_clear_all_bits(bits, 7);
        s21_bits_copy(bits, value.bits, 96);
        s21_trunc_last_digit(bits, scale, 0);
        if (s21_test_bit(value.bits, 127)) {
            s21_set_negative(result);
        }
        s21_bits_copy(result->bits, bits, 96);
    } else {
        s21_bits_copy(result->bits, value.bits, 128);
    }

    return ret_value;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_set_zero_for_result(result);
    s21_bits_copy(result->bits, value.bits, 126);
    if (!s21_test_bit(value.bits, 127)) {
        s21_set_bit(result->bits, 127);
    }
    return 0;
}
