#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_filter_val(&value_1);
    s21_filter_val(&value_1);
    s21_set_zero_for_result(result);
    int first_pos = !s21_test_bit(value_1.bits, 127);
    int second_pos = !s21_test_bit(value_2.bits, 127);
    int ret_val = -1;

    if (first_pos) {
        if (!second_pos) {
            s21_decimal tmp_val;
            s21_clear_bit(tmp_val.bits, 127);
            s21_bits_copy(tmp_val.bits, value_2.bits, 127);
            ret_val = s21_sub(value_1, tmp_val, result);
        }
    } else {
        if (second_pos) {
            s21_decimal tmp_val;
            s21_clear_bit(tmp_val.bits, 127);
            s21_bits_copy(tmp_val.bits, value_1.bits, 127);
            ret_val = s21_sub(value_2, tmp_val, result);
        } else {
            s21_set_negative(result);
        }
    }

    if (ret_val == -1) {
        int scale1 = s21_get_scale(value_1);
        int scale2 = s21_get_scale(value_2);
        int val_1[7];
        int val_2[7];
        int add_res[7];
        s21_clear_all_bits(add_res, 7);
        s21_clear_all_bits(val_1, 7);
        s21_clear_all_bits(val_2, 7);
        s21_bits_copy(val_1, value_1.bits, 96);
        s21_bits_copy(val_2, value_2.bits, 96);

        while (scale1 != scale2) {
            if (scale1 > scale2) {
                s21_mul_self_by_ten(val_2);
                scale2++;
            } else {
                s21_mul_self_by_ten(val_1);
                scale1++;
            }
        }

        s21_add_buffs(val_1, 7 * 32, val_2, 7 * 32, add_res, 7 * 32);

        if (s21_count_active_bits(add_res, 7 * 32) > 96) {
            int count = 0;
            int tmp_add_res[7];
            s21_clear_all_bits(tmp_add_res, 7);
            s21_bits_copy(tmp_add_res, add_res, 7 * 32);
            while (s21_count_active_bits(tmp_add_res, 7 * 32) > 96) {
                s21_trunc_last_digit(tmp_add_res, 1, 1);
                count++;
            }
            if (count <= scale1) {
                if (count) {
                    s21_trunc_last_digit(add_res, count, 1);
                    scale1 -= count;
                }
            } else {
                ret_val = 1 + s21_test_bit(result->bits, 127);
                s21_set_scale(result, 28);
            }
        }

        if (ret_val == -1) {
            ret_val = 0;
            s21_set_scale(result, scale1);
            s21_bits_copy(result->bits, add_res, 3 * 32);
        }
    }

    return ret_val;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_filter_val(&value_1);
    s21_filter_val(&value_1);
    s21_set_zero_for_result(result);
    int ret = 0;

    int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

    int result_sign = (s21_test_bit(value_1.bits, 127) != s21_test_bit(value_2.bits, 127));

    int res_buff[7];
    s21_clear_all_bits(res_buff, 7);

    int val_1[7];
    s21_clear_all_bits(val_1, 7);
    s21_bits_copy(val_1, value_1.bits, 96);

    s21_buf_multiplier(val_1, value_2.bits, 96, res_buff, 7 * 32);

    if (s21_count_active_bits(res_buff, 7 * 32) > 96) {
        int count = 0;
        int tmp_res_buff[7];
        s21_clear_all_bits(tmp_res_buff, 7);
        s21_bits_copy(tmp_res_buff, res_buff, 7 * 32);
        while (s21_count_active_bits(tmp_res_buff, 7 * 32) > 96) {
            s21_trunc_last_digit(tmp_res_buff, 1, 1);
            count++;
        }
        if (count <= scale) {
            if (count) {
                s21_trunc_last_digit(res_buff, count, 1);
                scale -= count;
            }
        } else {
            ret = 1 + s21_test_bit(result->bits, 127);
            s21_set_scale(result, 28);
        }
    }

    if (!ret) {
        s21_bits_copy(result->bits, res_buff, 96);
        s21_set_scale(result, scale);
        if (result_sign) {
            s21_set_negative(result);
        }
    }

    return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_filter_val(&value_1);
    s21_filter_val(&value_1);
    s21_set_zero_for_result(result);
    int first_pos = !s21_test_bit(value_1.bits, 127);
    int second_pos = !s21_test_bit(value_2.bits, 127);
    int ret_val = -1;

    if (first_pos) {
        if (!second_pos) {
            s21_set_positive(&value_2);
            ret_val = s21_add(value_1, value_2, result);
        }
    } else {
        if (!second_pos) {
            s21_decimal tmp_1;
            s21_clear_bit(tmp_1.bits, 127);
            s21_bits_copy(tmp_1.bits, value_1.bits, 127);
            s21_set_positive(&tmp_1);

            s21_decimal tmp_2;
            s21_clear_bit(tmp_2.bits, 127);
            s21_bits_copy(tmp_2.bits, value_2.bits, 127);
            s21_set_positive(&tmp_2);

            ret_val = s21_sub(tmp_2, tmp_1, result);
        } else {
            s21_decimal tmp_val;
            s21_clear_bit(tmp_val.bits, 127);
            s21_bits_copy(tmp_val.bits, value_2.bits, 127);
            s21_set_negative(&tmp_val);
            ret_val = s21_add(value_1, tmp_val, result);
        }
    }

    if (ret_val == -1) {
        if (first_pos) {
            s21_set_positive(result);
        }
        int scale1 = s21_get_scale(value_1);
        int scale2 = s21_get_scale(value_2);
        int val_1[7];
        int val_2[7];
        int sub_res[7];
        s21_clear_all_bits(sub_res, 7);
        s21_clear_all_bits(val_1, 7);
        s21_clear_all_bits(val_2, 7);
        s21_bits_copy(val_1, value_1.bits, 96);
        s21_bits_copy(val_2, value_2.bits, 96);

        while (scale1 != scale2) {
            if (scale1 > scale2) {
                s21_mul_self_by_ten(val_2);
                scale2++;
            } else {
                s21_mul_self_by_ten(val_1);
                scale1++;
            }
        }

        int comp = s21_compare_bits(val_1, val_2, 7 * 32, 7 * 32);
        if (comp == 1) {
            s21_buff_sub(val_1, 7 * 32, val_2, 7 * 32, sub_res, 7 * 32);
        } else if (comp == 2) {
            s21_buff_sub(val_2, 7 * 32, val_1, 7 * 32, sub_res, 7 * 32);
            if (first_pos) {
                s21_set_negative(result);
            } else {
                s21_set_positive(result);
            }
        } else {
            s21_set_positive(result);
        }

        int count = 0;
        int tmp_sub_res[7];
        s21_clear_all_bits(tmp_sub_res, 7);
        s21_bits_copy(tmp_sub_res, sub_res, 7 * 32);
        while (s21_count_active_bits(tmp_sub_res, 7 * 32) > 96) {
            s21_trunc_last_digit(tmp_sub_res, 1, 1);
            count++;
        }
        if (count <= scale1) {
            if (count) {
                s21_trunc_last_digit(sub_res, count, 1);
                scale1 -= count;
            }
        } else {
            ret_val = 1 + s21_test_bit(result->bits, 127);
            s21_set_scale(result, 28);
        }

        if (ret_val == -1) {
            ret_val = 0;
            s21_set_scale(result, scale1);
            s21_bits_copy(result->bits, sub_res, 3 * 32);
        }
    }

    return ret_val;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_filter_val(&value_1);
    s21_filter_val(&value_2);
    s21_set_zero_for_result(result);

    int ret_val = -1;

    if (s21_is_inf(value_2)) {
        ret_val = 0;
    } else if (!s21_count_active_bits(value_2.bits, 96)) {
        ret_val = 3;
    }

    if (ret_val == -1) {
        int result_sign = (s21_test_bit(value_1.bits, 127) != s21_test_bit(value_2.bits, 127));
        int scale = s21_get_scale(value_1) - s21_get_scale(value_2);

        int res_buff[7];
        s21_clear_all_bits(res_buff, 7);

        int val_1[7];
        s21_clear_all_bits(val_1, 7);
        s21_bits_copy(val_1, value_1.bits, 96);

        int val_2[3];
        s21_clear_all_bits(val_2, 3);
        s21_bits_copy(val_2, value_2.bits, 96);

        while (scale < 0) {
            s21_mul_self_by_ten(val_1);
            scale++;
        }

        int rem[7];
        s21_clear_all_bits(rem, 7);

        s21_buff_division(val_1, 7 * 32, val_2, 96, res_buff, 7 * 32, rem, 7 * 32);

        while (s21_count_active_bits(rem, 7 * 32) > 0 && scale < 28) {
            s21_mul_self_by_ten(val_1);
            s21_buff_division(val_1, 7 * 32, val_2, 96, res_buff, 7 * 32, rem, 7 * 32);
            scale++;
        }

        int count = 0;
        int tmp_res_buff[7];
        s21_clear_all_bits(tmp_res_buff, 7);
        s21_bits_copy(tmp_res_buff, res_buff, 7 * 32);
        while (s21_count_active_bits(tmp_res_buff, 7 * 32) > 96) {
            s21_trunc_last_digit(tmp_res_buff, 1, 1);
            count++;
        }
        if (count <= scale) {
            if (count) {
                s21_trunc_last_digit(res_buff, count, 1);
                scale -= count;
            }
        } else {
            ret_val = 1 + s21_test_bit(result->bits, 127);
            s21_set_scale(result, 28);
        }

        if (ret_val == -1) {
            s21_bits_copy(result->bits, res_buff, 96);
            s21_set_scale(result, scale);
            if (result_sign) {
                s21_set_negative(result);
            }
        }
    }

    return ret_val;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_filter_val(&value_1);
    s21_filter_val(&value_1);
    s21_set_zero_for_result(result);
    int ret_val = -1;

    int first_pos = !s21_test_bit(value_1.bits, 127);

    int val_1[7];
    s21_clear_all_bits(val_1, 7);
    s21_bits_copy(val_1, value_1.bits, 96);

    int val_2[7];
    s21_clear_all_bits(val_2, 7);
    s21_bits_copy(val_2, value_2.bits, 96);

    int scale_1 = s21_get_scale(value_1);
    int scale_2 = s21_get_scale(value_2);

    while (scale_1 != scale_2) {
        if (scale_1 > scale_2) {
            s21_mul_self_by_ten(val_2);
            scale_2++;
        } else {
            s21_mul_self_by_ten(val_1);
            scale_1++;
        }
    }

    int res[7];
    s21_clear_all_bits(res, 7);

    int rem[7];
    s21_clear_all_bits(rem, 7);

    s21_buff_division(val_1, 7 * 32, val_2, 7 * 32, res, 7 * 32, rem, 7 * 32);

    int tmp[7];
    if (!first_pos) {
        s21_bits_copy(tmp, res, 7 * 32);

        int one[1];
        s21_clear_all_bits(one, 1);
        s21_set_bit(one, 0);

        s21_add_buffs(tmp, 7 * 32, one, 32, res, 7 * 32);
    }

    s21_bits_copy(tmp, res, 7 * 32);
    s21_buf_multiplier(val_2, tmp, 7 * 32, res, 7 * 32);
    s21_bits_copy(tmp, res, 7 * 32);

    if (first_pos) {
        s21_buff_sub(val_1, 7 * 32, tmp, 7 * 32, res, 7 * 32);
    } else {
        s21_buff_sub(tmp, 7 * 32, val_1, 7 * 32, res, 7 * 32);
    }

    int count = 0;
    int tmp_res_buff[7];
    s21_clear_all_bits(tmp_res_buff, 7);
    s21_bits_copy(tmp_res_buff, res, 7 * 32);
    while (s21_count_active_bits(tmp_res_buff, 7 * 32) > 96) {
        s21_trunc_last_digit(tmp_res_buff, 1, 1);
        count++;
    }
    if (count <= scale_1) {
        if (count) {
            s21_trunc_last_digit(res, count, 1);
            scale_1 -= count;
        }
    } else {
        ret_val = 1;
        s21_set_scale(result, 28);
    }

    if (ret_val == -1) {
        s21_bits_copy(result->bits, res, 96);
        s21_set_scale(result, scale_1);
    }

    return ret_val;
}
