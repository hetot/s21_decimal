#include "s21_decimal.h"

int s21_is_less(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (s21_is_inf(val_2)) {
        if (!s21_is_inf(val_1)) {
            ret_val = second_pos;
        } else if (!first_pos && second_pos) {
            ret_val = 0;
        }
    } else if (s21_is_inf(val_1)) {
        ret_val = !first_pos;
    }

    if (first_pos) {
        if (!second_pos) {
            ret_val = 0;
        }
    } else {
        if (second_pos) {
            ret_val = 1;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }

        ret_val = (s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32) == 2) ? 1 : 0;
        if (!first_pos) {
            ret_val = !ret_val;
        }
    }

    return ret_val;
}

int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (s21_is_inf(val_2)) {
        if (!s21_is_inf(val_1)) {
            ret_val = second_pos;
        } else if (first_pos && second_pos) {
            ret_val = 0;
        }
    } else if (s21_is_inf(val_1)) {
        ret_val = !first_pos;
    }

    if (first_pos) {
        if (!second_pos) {
            ret_val = 0;
        }
    } else {
        if (second_pos) {
            ret_val = 1;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }
        int a = s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32);
        ret_val = ((a == 2) || !a) ? 1 : 0;
        if (!first_pos && a) {
            ret_val = !ret_val;
        }
    }

    return ret_val;
}

int s21_is_greater(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (s21_is_inf(val_1)) {
        if (!s21_is_inf(val_2)) {
            ret_val = first_pos;
        } else if (first_pos && !second_pos) {
            ret_val = 0;
        }
    } else if (s21_is_inf(val_2)) {
        ret_val = !second_pos;
    }

    if (first_pos) {
        if (!second_pos) {
            ret_val = 1;
        }
    } else {
        if (second_pos) {
            ret_val = 0;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }
        int a = s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32);
        ret_val = (a == 1) ? 1 : 0;
        if (!first_pos && a) {
            ret_val = !ret_val;
        }
    }

    return ret_val;
}

int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (s21_is_inf(val_1)) {
        if (!s21_is_inf(val_2)) {
            ret_val = first_pos;
        } else if (first_pos && !second_pos) {
            ret_val = 0;
        }
    } else if (s21_is_inf(val_2)) {
        ret_val = !second_pos;
    }

    if (first_pos) {
        if (!second_pos) {
            ret_val = 1;
        }
    } else {
        if (second_pos) {
            ret_val = 0;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }
        int a = s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32);
        ret_val = ((a == 1) || !a) ? 1 : 0;
        if (!first_pos && a) {
            ret_val = !ret_val;
        }
    }

    return ret_val;
}

int s21_is_equal(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    if (s21_is_inf(val_1) || s21_is_inf(val_2)) {
        ret_val = 0;
    }

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (first_pos) {
        if (!second_pos) {
            ret_val = 0;
        }
    } else {
        if (second_pos) {
            ret_val = 0;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }
        int a = s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32);
        ret_val = (!a) ? 1 : 0;
    }

    return ret_val;
}

int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2) {
    s21_filter_val(&val_1);
    s21_filter_val(&val_2);
    int ret_val = -1;

    if (s21_is_inf(val_1) || s21_is_inf(val_2)) {
        ret_val = 1;
    }

    int first_pos = !s21_test_bit(val_1.bits, 127);
    int second_pos = !s21_test_bit(val_2.bits, 127);

    if (first_pos) {
        if (!second_pos) {
            ret_val = 1;
        }
    } else {
        if (second_pos) {
            ret_val = 1;
        }
    }

    if (ret_val == -1) {
        int bits_1[7];
        int bits_2[7];
        s21_clear_all_bits(bits_1, 7);
        s21_clear_all_bits(bits_2, 7);
        s21_bits_copy(bits_1, val_1.bits, 96);
        s21_bits_copy(bits_2, val_2.bits, 96);

        int scale_1 = s21_get_scale(val_1);
        int scale_2 = s21_get_scale(val_2);
        while (scale_1 != scale_2) {
            if (scale_1 > scale_2) {
                s21_mul_self_by_ten(bits_2);
                scale_2++;
            } else {
                s21_mul_self_by_ten(bits_1);
                scale_1++;
            }
        }
        int a = s21_compare_bits(bits_1, bits_2, 7 * 32, 7 * 32);
        ret_val = (a) ? 1 : 0;
    }

    return ret_val;
}
