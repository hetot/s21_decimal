#include <check.h>
#include "s21_decimal.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

START_TEST(test_mod)
{
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(100000, &test_value_1);
    s21_from_int_to_decimal(1000, &test_value_2);
    s21_mod(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (100000 % 1000));

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(3, &test_value_2);
    s21_mod(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (1 % 3));

    s21_from_int_to_decimal(3, &test_value_1);
    s21_from_int_to_decimal(3, &test_value_2);
    s21_mod(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (3 % 3));
}
END_TEST

START_TEST(test_add)
{
    s21_decimal src1, src2;
    int a_int = -1234;
    float b_float = 1.234;
    float a_float;
    int b_int;
    float res_our_dec;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    float res_origin = -1232.766;
    s21_decimal res_od;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_int = -1234;
    b_float = -1.234;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -1235.234;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_float = -1234;
    b_float = -221.234;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -1455.234;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_float = -9403;
    b_float = 0.00234;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -9402.99766;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_int = -1234;
    b_float = -221.234;
    s21_from_float_to_decimal(a_int, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -1455.234;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_int = -9403;
    b_int = 234;
    int res_our_dec_int = 0;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_int_to_decimal(b_int, &src2);
    int res_origin_int = -9169;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec_int);
    ck_assert_int_eq(res_our_dec_int, res_origin_int);

    a_float = -940.3;
    b_float = 0.000234;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -940.299766;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_float = -0.9403;
    b_float = 0.000234;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -0.940066;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_float = -0.9403;
    b_float = 2.0234;
    res_origin = 1.0831;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_float = -0.94e03;
    b_float = -112.0e2;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin = -12140;
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    a_int = 9403;
    b_int = 202;
    res_origin_int = 9605;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_int_to_decimal(b_int, &src2);
    s21_add(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec_int);
    ck_assert_int_eq(res_our_dec_int, res_origin_int);

    src1.bits[3] = 0x300000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xF;
    src1.bits[0] = 0x67E4FEEF;
    src2.bits[3] = 0x300000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFF;
    src2.bits[0] = 0x67E4FFFF;
    s21_decimal result_origin;
    result_origin.bits[3] = 0x300000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x10E;
    result_origin.bits[0] = 0xCFC9FEEE;
    s21_add(src1, src2, &res_od);
    ck_assert_int_eq(result_origin.bits[3], res_od.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], res_od.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], res_od.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], res_od.bits[0]);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    float result_float;

    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.021, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_uint_eq(result_float, 1899.999 + 100.021);

    s21_from_int_to_decimal(-467, &test_value_1);
    s21_from_int_to_decimal(3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -467 + 3668);

    s21_from_int_to_decimal(467, &test_value_1);
    s21_from_int_to_decimal(-3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 467 + (-3668));

    s21_from_int_to_decimal(-199421, &test_value_1);
    s21_from_int_to_decimal(4433, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -199421 + 4433);

    s21_from_int_to_decimal(199421, &test_value_1);
    s21_from_int_to_decimal(-4433, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 199421 + (-4433));

    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 2000000);

    s21_from_int_to_decimal(-199421, &test_value_1);
    s21_from_int_to_decimal((-4433), &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-199421) + (-4433));

    s21_from_int_to_decimal(467, &test_value_1);
    s21_from_int_to_decimal(3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 467 + 3668);

    s21_from_int_to_decimal(-467, &test_value_1);
    s21_from_int_to_decimal(-3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-467) + (-3668));

    s21_decimal a_dec, b_dec, res_dec;
    int ret, res_int;
    float res_fl;

    for (int i = 0; i < 1000; i++)
    {
        s21_from_int_to_decimal(i, &a_dec);
        s21_from_int_to_decimal(1000 - i, &b_dec);
        ret = s21_add(a_dec, b_dec, &res_dec);
        s21_from_decimal_to_int(res_dec, &res_int);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(res_int, 1000);
    }

    s21_set_zero_for_result(&a_dec);
    for (int i = 0; i < 96; i++)
    {
        s21_set_bit(a_dec.bits, i);
    }
    ret = s21_add(a_dec, b_dec, &res_dec);
    ck_assert_int_eq(ret, 1);

    s21_set_negative(&a_dec);
    s21_set_negative(&b_dec);
    ret = s21_add(a_dec, b_dec, &res_dec);
    ck_assert_int_eq(ret, 2);

    s21_from_float_to_decimal(1.5787, &a_dec);
    s21_from_float_to_decimal(451.577, &b_dec);
    ret = s21_add(a_dec, b_dec, &res_dec);
    s21_from_decimal_to_float(res_dec, &res_fl);
    ck_assert_uint_eq(res_fl, 1.5787 + 451.577);

    s21_set_zero_for_result(&a_dec);
    for (int i = 0; i < 96; i++)
    {
        s21_set_bit(a_dec.bits, i);
    }
    s21_from_float_to_decimal(0.8, &b_dec);
    ret = s21_add(a_dec, b_dec, &res_dec);
    ck_assert_int_eq(28, s21_get_scale(res_dec));
    ck_assert_int_eq(ret, 1);

    s21_set_zero_for_result(&a_dec);
    for (int i = 0; i < 96; i++)
    {
        s21_set_bit(a_dec.bits, i);
    }
    s21_from_float_to_decimal(0.3, &b_dec);
    ret = s21_add(a_dec, b_dec, &res_dec);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_get_scale(a_dec), s21_get_scale(res_dec));
}
END_TEST

START_TEST(test_sub)
{
    s21_decimal src1, src2;
    int a_int = 9403;
    int b_int = 202;
    int res_our_dec_int;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_int_to_decimal(b_int, &src2);
    int res_origin_int = 9201;
    s21_decimal res_od;
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec_int);
    ck_assert_int_eq(res_our_dec_int, res_origin_int);

    a_int = 9403;
    float b_float = 202.098;
    float res_our_dec_float = 0.0;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    float res_origin_float = 9200.902;
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec_float);
    ck_assert_uint_eq(res_our_dec_float, res_origin_float);

    float a_float = -9403;
    b_float = 202.098;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin_float = a_float - b_float;
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec_float);
    ck_assert_uint_eq(res_our_dec_float, res_origin_float);

    a_float = -94;
    b_float = -202;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin_float = a_float - b_float;
    s21_sub(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec_float);
    ck_assert_uint_eq(res_our_dec_float, res_origin_float);

    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin, result_our;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1899999 - 100001);

    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(-100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1899999 - (-100001));

    s21_from_int_to_decimal(-1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1899999) - 100001);

    s21_from_int_to_decimal(-1899999, &test_value_1);
    s21_from_int_to_decimal(-100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1899999) - (-100001));

    s21_from_int_to_decimal(1994214, &test_value_1);
    s21_from_int_to_decimal(77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1994214 - 77443333);

    s21_from_int_to_decimal(1994214, &test_value_1);
    s21_from_int_to_decimal(-77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1994214 - (-77443333));

    s21_from_int_to_decimal(-1994214, &test_value_1);
    s21_from_int_to_decimal(77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -1994214 - 77443333);

    s21_from_int_to_decimal(-1994214, &test_value_1);
    s21_from_int_to_decimal(-77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1994214) - (-77443333));

    s21_from_int_to_decimal(19999445, &test_value_1);
    s21_from_int_to_decimal(6, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 19999445 - 6);

    float result_float;
    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.021, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_uint_eq(result_float, 1899.999 - 100.021);
}
END_TEST

START_TEST(test_mul)
{
    s21_decimal src1, src2;
    float a_float = 9403.0e2;
    int b_int = 202;
    float res_our_dec_float;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_int_to_decimal(b_int, &src2);
    float res_origin_float = 189940600;
    s21_decimal res_od;
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec_float);
    ck_assert_uint_eq(res_our_dec_float, res_origin_float);

    a_float = 9403.0e2;
    float b_float = 9403.0e2;
    s21_from_float_to_decimal(a_float, &src1);
    s21_from_float_to_decimal(b_float, &src2);
    res_origin_float = 884164090000;
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec_float);
    ck_assert_uint_eq(res_our_dec_float, res_origin_float);

    int a_int = 9403;
    b_int = 202;
    int res_our_dec_int;
    s21_from_int_to_decimal(a_int, &src1);
    s21_from_int_to_decimal(b_int, &src2);
    int res_origin_int = 1899406;
    s21_mul(src1, src2, &res_od);
    s21_from_decimal_to_int(res_od, &res_our_dec_int);
    ck_assert_int_eq(res_our_dec_int, res_origin_int);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(18999, &test_value_1);
    s21_from_int_to_decimal(1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (18999 * 1001));

    s21_from_int_to_decimal(18999, &test_value_1);
    s21_from_int_to_decimal(-1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (18999 * (-1001)));

    s21_from_int_to_decimal(-18999, &test_value_1);
    s21_from_int_to_decimal(1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-18999 * 1001));

    s21_from_int_to_decimal(-18999, &test_value_1);
    s21_from_int_to_decimal(-1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, ((-18999) * (-1001)));

    s21_from_int_to_decimal(191, &test_value_1);
    s21_from_int_to_decimal(57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 191 * 57443);

    s21_from_int_to_decimal(191, &test_value_1);
    s21_from_int_to_decimal(-57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 191 * (-57443));

    s21_from_int_to_decimal(-191, &test_value_1);
    s21_from_int_to_decimal(57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -191 * 57443);

    s21_from_int_to_decimal(-191, &test_value_1);
    s21_from_int_to_decimal(-57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, ((-191) * (-57443)));

    float result_float;
    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_int_eq(result_float, 1899.999 * 100.001);
}
END_TEST

START_TEST(test_div)
{
    s21_decimal src1, src2;
    float a = 9403.0e2;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = 4654.950495049504950495049505;
    s21_decimal res_od;
    s21_div(src1, src2, &res_od);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_uint_eq(res_our_dec, res_origin);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;

    s21_from_int_to_decimal(100000, &test_value_1);
    s21_from_int_to_decimal(1000, &test_value_2);
    s21_div(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (100000 / 1000));

    s21_from_int_to_decimal(456800, &test_value_1);
    s21_from_int_to_decimal(456800, &test_value_2);
    s21_div(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (456800 / 456800));

    // s21_from_int_to_decimal(8900, &test_value_1);
    // s21_from_int_to_decimal(2, &test_value_2);
    // s21_div(test_value_1, test_value_2, &result_dec);
    // s21_from_decimal_to_int(result_dec, &result_int);
    // ck_assert_int_eq(result_int, (8900 / 2));
}
END_TEST

START_TEST(test_is_less)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE); // 1.2345 < 1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);  // 1.2 < 1.2345

    s21_set_negative(&dst1);
    s21_set_negative(&dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);  // -1.2345 < -1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE); // -1.2 < -1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE); // 0 < 0

    s21_set_inf(&dst1);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE); // +INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);  // 0 < +INFINITY

    s21_set_negative(&dst1);
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);  // -INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE); // 0 < -INFINITY

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_is_less_or_equal)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), FALSE); // 1.2345 <= 1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);  // 1.2 <= 1.2345

    s21_set_negative(&dst1);
    s21_set_negative(&dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE); // -1.2345 <= -1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE); // -1.2 <= 1.2345

    s21_set_positive(&dst1);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE); //  1.2345 <= -1.2 // fail
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE); //  -1.2 <= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE); // 0 <= 0

    s21_set_inf(&dst1);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);                                  // +INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE); // 0 <= +INFINITY

    s21_set_inf(&dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE); // +INFINITY <= +INFINITY

    s21_set_negative(&dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE); // -INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE); // 0 <= -INFINITY

    s21_from_float_to_decimal(1726.73, &dst1);
    s21_from_float_to_decimal(1726.73, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE); // 1726.73 <= 1726.73

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(111, &test_value_1);
    s21_from_int_to_decimal(111, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(711995, &test_value_1);
    s21_from_int_to_decimal(711996, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_is_greater)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);  // 1.2345 > 1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE); // 1.2 > 1.2345

    s21_set_negative(&dst1);
    s21_set_negative(&dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE); // -1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);  // -1.2 > 1.2345

    s21_set_positive(&dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);  //  1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE); //  -1.2 > 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE); // 0 > 0

    s21_set_inf(&dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);  // +INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE); // 0 > +INFINITY

    s21_set_negative(&dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE); // -INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);  // 0 > -INFINITY

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(111, &test_value_1);
    s21_from_int_to_decimal(111, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(711995, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_is_greater_or_equal)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE); // 1.2345 >= 1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE); // 1.2 >= 1.2345

    s21_set_negative(&dst1);
    s21_set_negative(&dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE); // -1.2345 >= -1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE); // -1.2 >= 1.2345

    s21_set_positive(&dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE); //  1.2345 >= -1.2 // fail
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE); //  -1.2 >= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), TRUE); // 0 >= 0

    s21_set_inf(&dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE); // +INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE); // 0 >= +INFINITY

    s21_set_negative(&dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE); // -INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE); // 0 >= -INFINITY

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(0, &test_value_1);
    s21_from_int_to_decimal(0, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(239, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_is_equal)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE); // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE); // 1.2 = 1.2

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);

    s21_set_inf(&dst1);
    s21_set_inf(&dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE); // +INFINITY = +INFINITY

    s21_from_int_to_decimal(0, &dst1); // -0 == 0
    s21_from_int_to_decimal(0, &dst2);
    s21_set_negative(&dst1);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(0, &test_value_1);
    s21_from_int_to_decimal(0, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_is_not_equal)
{
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), TRUE); // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE); // 1.2 = 1.2

    s21_set_inf(&dst1);
    s21_set_inf(&dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), TRUE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_floor)
{
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;

    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 5);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 6);

    s21_from_int_to_decimal(-2744406, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -275);
}
END_TEST

START_TEST(test_round)
{
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;

    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 5);
    s21_round(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 7);

    s21_from_int_to_decimal(19993, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -2);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal)
{
    s21_decimal X;
    int Y;
    s21_from_int_to_decimal(100, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(100, Y);

    s21_from_int_to_decimal(6.5, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(6, Y);

    s21_from_int_to_decimal(0.123, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(0, Y);

    s21_from_int_to_decimal(123456789, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(123456789, Y);

    s21_from_int_to_decimal(-94, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(-94, Y);

    s21_from_int_to_decimal(-4.31, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(-4, Y);

    s21_from_int_to_decimal(-0.13, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(0, Y);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal)
{
    s21_decimal X;
    float Y;
    s21_from_float_to_decimal(10.53, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(10.53, Y);

    // s21_from_float_to_decimal(-4.48, &X);
    // s21_from_decimal_to_float(X, &Y);
    // ck_assert_uint_eq(-4.48, Y);

    s21_from_float_to_decimal(0.123, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(0.123, Y);

    s21_from_float_to_decimal(100, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(100, Y);

    s21_from_float_to_decimal(-49, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(-49, Y);

    s21_from_float_to_decimal(2e-3, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(2e-3, Y);

    s21_from_float_to_decimal(2e5, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(2e5, Y);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int)
{
    s21_decimal X;
    int Y;
    s21_from_int_to_decimal(100, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(100, Y);

    s21_from_int_to_decimal(6.5, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(6, Y);

    s21_from_int_to_decimal(0.123, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(0, Y);

    s21_from_int_to_decimal(123456789, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(123456789, Y);

    s21_from_int_to_decimal(-94, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(-94, Y);

    s21_from_int_to_decimal(-4.31, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(-4, Y);

    s21_from_int_to_decimal(-0.13, &X);
    s21_from_decimal_to_int(X, &Y);
    ck_assert_int_eq(0, Y);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float)
{
    s21_decimal X;
    float Y;
    s21_from_float_to_decimal(10.53, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(10.53, Y);

    // s21_from_float_to_decimal(-4.48, &X);
    // s21_from_decimal_to_float(X, &Y);
    // ck_assert_uint_eq(-4.48, Y);

    s21_from_float_to_decimal(0.123, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(0.123, Y);

    s21_from_float_to_decimal(100, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(100, Y);

    s21_from_float_to_decimal(-49, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(-49, Y);

    s21_from_float_to_decimal(2e-3, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(2e-3, Y);

    s21_from_float_to_decimal(2e5, &X);
    s21_from_decimal_to_float(X, &Y);
    ck_assert_uint_eq(2e5, Y);
}
END_TEST

START_TEST(test_truncate)
{
    s21_decimal src1;
    src1.bits[3] = 0x000A0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    s21_decimal res_od;
    s21_truncate(src1, &res_od);
    ck_assert_uint_eq(res_od.bits[0], result.bits[0]);
    ck_assert_uint_eq(res_od.bits[1], result.bits[1]);
    ck_assert_uint_eq(res_od.bits[2], result.bits[2]);
    ck_assert_uint_eq(res_od.bits[3], result.bits[3]);

    src1.bits[0] = 0b11011110101001001000000010110110;
    src1.bits[1] = 0b01011111101001011101111110100000;
    src1.bits[2] = 0b00011111111010011010111101100000;
    src1.bits[3] = 0b00000000000010010000000000000000;
    result.bits[0] = 0b00110100101011011100000100111110;
    result.bits[1] = 0b10001001000100001000011110111001;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_truncate(src1, &res_od);
    ck_assert_uint_eq(res_od.bits[0], result.bits[0]);
    ck_assert_uint_eq(res_od.bits[1], result.bits[1]);
    ck_assert_uint_eq(res_od.bits[2], result.bits[2]);
    ck_assert_uint_eq(res_od.bits[3], result.bits[3]);

    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int res;
    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_truncate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &res);
    ck_assert_int_eq(res, 67);

    s21_from_int_to_decimal(-2744406, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_truncate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &res);
    ck_assert_int_eq(res, -274);
}
END_TEST

START_TEST(test_negate)
{
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_negate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -711996);

    s21_from_int_to_decimal(-279, &test_value_1);
    s21_negate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 279);
}
END_TEST

Suite *s21_decimal_test_suite()
{
    Suite *s = suite_create("s21_decimal_test_suite");

    TCase *s21_mod = tcase_create("mod");
    suite_add_tcase(s, s21_mod);
    tcase_add_test(s21_mod, test_mod);

    TCase *s21_add = tcase_create("add");
    suite_add_tcase(s, s21_add);
    tcase_add_test(s21_add, test_add);

    TCase *s21_sub = tcase_create("sub");
    suite_add_tcase(s, s21_sub);
    tcase_add_test(s21_sub, test_sub);

    TCase *s21_mul = tcase_create("mul");
    suite_add_tcase(s, s21_mul);
    tcase_add_test(s21_mul, test_mul);

    TCase *s21_div = tcase_create("div");
    suite_add_tcase(s, s21_div);
    tcase_add_test(s21_div, test_div);

    TCase *s21_from_int_to_decimal = tcase_create("from_int_to_decimal");
    suite_add_tcase(s, s21_from_int_to_decimal);
    tcase_add_test(s21_from_int_to_decimal, test_s21_from_int_to_decimal);

    TCase *s21_from_float_to_decimal = tcase_create("from_float_to_decimal");
    suite_add_tcase(s, s21_from_float_to_decimal);
    tcase_add_test(s21_from_float_to_decimal, test_s21_from_float_to_decimal);

    TCase *s21_from_decimal_to_int = tcase_create("from_decimal_to_int");
    suite_add_tcase(s, s21_from_decimal_to_int);
    tcase_add_test(s21_from_decimal_to_int, test_s21_from_decimal_to_int);

    TCase *s21_from_decimal_to_float = tcase_create("from_decimal_to_float");
    suite_add_tcase(s, s21_from_decimal_to_float);
    tcase_add_test(s21_from_decimal_to_float, test_s21_from_decimal_to_float);

    TCase *s21_is_less = tcase_create("is_less");
    suite_add_tcase(s, s21_is_less);
    tcase_add_test(s21_is_less, test_is_less);

    TCase *s21_is_less_or_equal = tcase_create("is_less_or_equal");
    suite_add_tcase(s, s21_is_less_or_equal);
    tcase_add_test(s21_is_less_or_equal, test_is_less_or_equal);

    TCase *s21_is_greater = tcase_create("is_greater");
    suite_add_tcase(s, s21_is_greater);
    tcase_add_test(s21_is_greater, test_is_greater);

    TCase *s21_is_greater_or_equal = tcase_create("is_greater_or_equal");
    suite_add_tcase(s, s21_is_greater_or_equal);
    tcase_add_test(s21_is_greater_or_equal, test_is_greater_or_equal);

    TCase *s21_is_equal = tcase_create("is_equal");
    suite_add_tcase(s, s21_is_equal);
    tcase_add_test(s21_is_equal, test_is_equal);

    TCase *s21_is_not_equal = tcase_create("is_not_equal");
    suite_add_tcase(s, s21_is_not_equal);
    tcase_add_test(s21_is_not_equal, test_is_not_equal);

    TCase *s21_floor = tcase_create("floor");
    suite_add_tcase(s, s21_floor);
    tcase_add_test(s21_floor, test_floor);

    TCase *s21_round = tcase_create("round");
    suite_add_tcase(s, s21_round);
    tcase_add_test(s21_round, test_round);

    TCase *s21_truncate = tcase_create("truncate");
    suite_add_tcase(s, s21_truncate);
    tcase_add_test(s21_truncate, test_truncate);

    TCase *s21_negate = tcase_create("negate");
    suite_add_tcase(s, s21_negate);
    tcase_add_test(s21_negate, test_negate);

    return s;
}

int main()
{
    int no_failed = 0;

    Suite *s = s21_decimal_test_suite();

    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
