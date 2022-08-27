#include "s21_decimal.h"

// Bit manipulators
void s21_set_bit(int arr[], int k) {
    int i = k / 32;            // i = array index (use: A[i])
    int pos = k % 32;          // pos = bit position in A[i]
    unsigned int flag = 1;   // flag = 0000.....00001
    flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
    arr[i] = arr[i] | flag;
}

void s21_clear_bit(int arr[], int k) {
    int i = k / 32;
    int pos = k % 32;
    unsigned int flag = 1;  // flag = 0000.....00001
    flag = flag << pos;  // flag = 0000...010...000   (shifted k positions)
    flag = ~flag;  // flag = 1111...101..111
    arr[i] = arr[i] & flag;  // RESET the bit at the k-th position in A[i]
}

int s21_test_bit(int arr[], int k) {
    int res = 0;

    int i = k/32;
    int pos = k%32;
    unsigned int flag = 1;  // flag = 0000.....00001
    flag = flag << pos;  // flag = 0000...010...000   (shifted k positions)
    if ( arr[i] & flag ) {  // Test the bit at the k-th position in A[i]
        res = 1;
    }

    return res;
}

// Additional functions
void s21_set_zero_for_result(s21_decimal *n) {
    for (int i = 0; i < 4; i++) {
        n->bits[i] = 0;
    }
}

int s21_get_scale(s21_decimal value) {
    int scale = 0;
    for (int i = 0; i < 8; i++) {
        if (s21_test_bit(value.bits, 112 + i)) {
            int mul = 1;
            for (int k = i; k > 0; k--) {
                mul *= 2;
            }
            scale += mul;
        }
    }

    return scale;
}

void s21_set_scale(s21_decimal *value, int scale) {
    for (int i = 0; i < 8; i++) {
        s21_clear_bit(value->bits, 112 + i);
    }

    for (int i = 0; i < 8 && scale; i++, scale /= 2) {
        if ((scale % 2) == 1) {
            s21_set_bit(value->bits, 112 + i);
        }
    }
}

void s21_set_positive(s21_decimal *value) {
    s21_clear_bit(value->bits, 127);
}

void s21_set_negative(s21_decimal *value) {
    s21_set_bit(value->bits, 127);
}

int s21_count_active_bits(int bits[], int size) {
    int i = size - 1;
    for (; i >= 0 && !s21_test_bit(bits, i); i--) {
    }
    i++;
    return i;
}

int s21_compare_bits(int bits_1[], int bits_2[], int size_1, int size_2) {
    int counter1 = s21_count_active_bits(bits_1, size_1);
    int counter2 = s21_count_active_bits(bits_2, size_2);
    int ret = -1;

    if (counter1 > counter2) {
        ret = 1;
    } else if (counter1 < counter2) {
        ret = 2;
    } else {
        for (int i = counter1 - 1; i >= 0; i--) {
            if (s21_test_bit(bits_1, i) != s21_test_bit(bits_2, i)) {
                ret = s21_test_bit(bits_1, i) ? 1 : 2;
                break;
            }
        }
        ret = (ret == -1) ? 0 : ret;
    }

    return ret;
}

void s21_trunc_last_digit(int bits[], int scale, int round) {
    int scale_bits[7];
    s21_clear_all_bits(scale_bits, 7);
    s21_set_bit(scale_bits, 0);
    for (int i = 0; i < scale; i++) {
        s21_mul_self_by_ten(scale_bits);
    }

    int tmp_res[7];
    int rem[7];
    s21_clear_all_bits(tmp_res, 7);
    s21_clear_all_bits(rem, 7);
    s21_buff_division(bits, 7 * 32, scale_bits, 7 * 32, tmp_res, 7 * 32, rem, 7 * 32);

    if (round) {
        int two[1];
        s21_clear_all_bits(two, 1);
        s21_set_bit(two, 1);
        int tmp_rem[1];
        s21_clear_all_bits(tmp_rem, 1);
        int half[7];
        s21_clear_all_bits(half, 7);
        s21_buff_division(scale_bits, 7 * 32, two, 32, half, 7 * 32, tmp_rem, 32);

        if (s21_compare_bits(rem, half, 32 * 7, 32 * 7) != 2) {
            int tmp[7];
            s21_clear_all_bits(tmp, 7);
            s21_bits_copy(tmp, tmp_res, 7 * 32);
            s21_clear_bit(two, 1);
            s21_set_bit(two, 0);
            s21_add_buffs(tmp, 7 * 32, two, 32, tmp_res, 7 * 32);
        }
    }

    s21_bits_copy(bits, tmp_res, 7 * 32);
}

void s21_buff_division(int divid[], int divid_len, int devis[],
                        int devis_len, int res[], int res_len, int rem[], int rem_len) {
    s21_clear_all_bits(res, res_len / 32);
    s21_clear_all_bits(rem, rem_len / 32);

    int tmp[7];

    int divid_start_pos = s21_count_active_bits(divid, divid_len);
    int on = 0;

    for (int i = divid_start_pos - 1; i >= 0; i--) {
        s21_right_shifter(rem, rem_len, 1);
        if (s21_test_bit(divid, i)) {
            s21_set_bit(rem, 0);
        }
        if (s21_compare_bits(rem, devis, rem_len, devis_len) != 2) {
            on = 1;
            s21_right_shifter(res, res_len, 1);
            s21_set_bit(res, 0);
            s21_clear_all_bits(tmp, 7);
            s21_bits_copy(tmp, rem, rem_len);
            s21_buff_sub(tmp, 7 * 32, devis, devis_len, rem, rem_len);
        } else {
            if (on) {
                s21_right_shifter(res, res_len, 1);
            }
        }
    }
}

void s21_buff_sub(int bits_1[], int size_1, int bits_2[], int size_2, int res[], int res_len) {
    s21_clear_all_bits(res, res_len / 32);

    int count_1 = s21_count_active_bits(bits_1, size_1);
    int count_2 = s21_count_active_bits(bits_2, size_2);

    if (!count_2) {
        s21_bits_copy(res, bits_1, res_len);
    }

    for (int i = 0; i < count_1; i++) {
        if (s21_test_bit(bits_1, i)) {
            if (!s21_test_bit(bits_2, i)) {
                s21_set_bit(res, i);
            }
        } else {
            if (i < count_2 && s21_test_bit(bits_2, i)) {
                for (int j = i + 1; j < count_1; j++) {
                    if (s21_test_bit(bits_1, j)) {
                        if (j == (count_1 - 1)) {
                            count_1--;
                        }
                        s21_clear_bit(bits_1, j);
                        break;
                    } else {
                        s21_set_bit(bits_1, j);
                    }
                }
                s21_set_bit(res, i);
            } else {
                if (s21_test_bit(bits_1, i)) {
                    s21_set_bit(res, i);
                }
            }
        }
    }
}

void s21_clear_all_bits(int bits[], int size) {
    for (int i = 0; i < size; i++) {
        bits[i] = 0;
    }
}

void s21_right_shifter(int bits[], int size, int by) {
    for (int k = 0; k < by; k++) {
        int buf = s21_test_bit(bits, 0);
        s21_clear_bit(bits, 0);
        for (int i = 0; i < size - 1; i++) {
            if (buf) {
                buf = s21_test_bit(bits, i + 1);
                s21_set_bit(bits, i + 1);
            } else {
                buf = s21_test_bit(bits, i + 1);
                s21_clear_bit(bits, i + 1);
            }
        }
    }
}

void s21_buf_multiplier(int bits_1[], int bits_2[], int mul_size, int res[], int size) {
    s21_clear_all_bits(res, size / 32);

    int bits_1_cpy[7];
    s21_bits_copy(bits_1_cpy, bits_1, 7 * 32);

    int tmp[7];
    s21_clear_all_bits(tmp, 7);
    for (int k = 0; k < s21_count_active_bits(bits_2, mul_size); k++) {
        if (s21_test_bit(bits_2, k)) {
            s21_add_buffs(res, 7 * 32, bits_1_cpy, 7 * 32, tmp, 7 * 32);
            s21_bits_copy(res, tmp, size);
        }
        s21_right_shifter(bits_1_cpy, 7 * 32, 1);
    }
    s21_bits_copy(res, tmp, size);
}

void s21_bits_copy(int bit_1[], int bit_2[], int size) {
    for (int i = 0; i < size; i++) {
        if (s21_test_bit(bit_2, i)) {
            s21_set_bit(bit_1, i);
        } else {
            s21_clear_bit(bit_1, i);
        }
    }
}

void s21_mul_self_by_ten(int bits[]) {
    int ten[1];
    s21_clear_all_bits(ten, 1);
    s21_set_bit(ten, 1);
    s21_set_bit(ten, 3);

    int res[7];
    s21_buf_multiplier(bits, ten, 32, res, 7 * 32);

    s21_bits_copy(bits, res, 7 * 32);
}

void s21_add_buffs(int val_1[], int size_1, int val_2[], int size_2, int result[], int size) {
    s21_clear_all_bits(result, size / 32);
    int rem = 0;
    int i = 0;
    for (; i < size; i++) {
        int a = (i >= size_1) ? 0 : s21_test_bit(val_1, i);
        int b = (i >= size_2) ? 0 : s21_test_bit(val_2, i);
        rem += (a + b);
        if (rem % 2) {
            s21_set_bit(result, i);
        }
        rem = (rem > 1) ? 1 : 0;
    }
}

void s21_bit_printer(int bits[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", s21_test_bit(bits, i));
    }
    printf("\n");
}

void s21_set_inf(s21_decimal *val) {
    for (int i = 0; i < 4; i++) {
        val->bits[i] = 0;
    }
    s21_set_scale(val, 28);
}

int s21_is_inf(s21_decimal val) {
    int ret = 1;
    for (int i = 0; i < 3; i++) {
        if (val.bits[i]) {
            ret = 0;
            break;
        }
    }
    if (ret && s21_get_scale(val) != 28) {
        ret = 0;
    }

    return ret;
}

void s21_filter_val(s21_decimal *val) {
    int is_zero = 1;
    for (int i = 0; i < 3; i++) {
        if (val->bits[i]) {
            is_zero = 0;
            break;
        }
    }
    if (is_zero && s21_get_scale(*val) != 28) {
        s21_set_zero_for_result(val);
    }
}
