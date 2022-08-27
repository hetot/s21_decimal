#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst)
{
    char *binary_string = generate_binary_string(abs(src));
    int length = 0;
    for (int i = 0; i < 4; i++)
        dst->bits[i] = 0;
    if (src < 0)
        s21_set_bit(dst->bits, 127);
    else
        s21_clear_bit(dst->bits, 127);
    while (*binary_string)
    {
        if (*binary_string == '1')
            s21_set_bit(dst->bits, length);
        else
            s21_clear_bit(dst->bits, length);
        binary_string++;
        length++;
    }
    binary_string = 0;
    return 1;
}

char *generate_binary_string(int src)
{
    static char tmp_bin_str[100];
    char *q = tmp_bin_str;

    int length = 0;
    while (src > 0)
    {
        *q = (char)(src % 2 + 48);
        q++;
        src /= 2;
        length++;
    }
    *q = '\0';
    return tmp_bin_str;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst)
{
    int length = 0;
    while (src != (int)src && length <= 5)
    {
        src *= 10;
        length++;
    }

    s21_from_int_to_decimal((int)src, dst);
    if (src < 0)
        s21_set_bit(dst->bits, 127);
    else
        s21_clear_bit(dst->bits, 127);

    char *binary_string = generate_binary_string(length);

    int index = 112;
    while (*binary_string)
    {
        if (*binary_string == '1')
            s21_set_bit(dst->bits, index);
        else
            s21_clear_bit(dst->bits, index);
        index++;
        binary_string++;
    }

    binary_string = 0;
    return 1;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst)
{
    *dst = 0;
    int multy = 0;
    for (int i = 0; i < 96; i++)
    {
        *dst += s21_test_bit(src.bits, i) * pow(2, multy);
        multy++;
    }

    int pointer = get_point_position(src);
    *dst /= pow(10, pointer);

    if (s21_test_bit(src.bits, 127))
        *dst *= -1;

    return 1;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst)
{
    double tmp = 0;
    int multy = 0;
    for (int i = 0; i < 96; i++)
    {
        tmp += s21_test_bit(src.bits, i) * pow(2, multy);
        multy++;
    }

    int pointer = get_point_position(src);
    tmp /= pow(10, pointer);
    if (s21_test_bit(src.bits, 127))
        tmp *= -1;

    *dst = (float)tmp;
    return 1;
}

int get_point_position(s21_decimal src)
{
    int multy = 0;
    int pointer = 0;
    for (int i = 112; i <= 119; i++)
    {
        pointer += s21_test_bit(src.bits, i) * pow(2, multy);
        multy++;
    }

    return pointer;
}

char *decimal_to_char(s21_decimal src)
{
    char *string = malloc(sizeof(char));
    char *q = string;
    for (int i = 0; i < 128; i++)
    {
        *q = s21_test_bit(src.bits, i) + 48;
        q++;
    }
    return string;
}

void printf_decimal(s21_decimal src)
{
    for (int i = 0; i < 128; i++)
    {
        if (i % 32 == 0 && i != 0)
            printf("%c", ' ');
        printf("%d", s21_test_bit(src.bits, i));
    }
}
