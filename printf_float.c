#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int get_num_len(double num, fmt_info_t *fmt_info, char *str);
int get_max_width(int num_len, fmt_info_t *fmt_info);
void print_padding(fmt_info_t *fmt_info, double num, int num_len, int max_w, int zeros_count);
void print_number(fmt_info_t *fmt_info, double num, int num_len, char *str);
void print_non_convertible(fmt_info_t *fmt_info, char *str);
void cleanup(char *str, float_info_t *flt_info);
int get_precision(fmt_info_t *fmt_info);
char *convert_and_round_float(double num, fmt_info_t *fmt_info, float_info_t *flt_info, int precision);

/**
 * calculate_and_print_float - Calculate and print the decimal number
 * @num: The double number to print
 * @fmt_info: The format info
 */
void calculate_and_print_float(double num, fmt_info_t *fmt_info)
{
    char *str;
    int num_len, zeros_count, max_w, i;
    int has_sign = (fmt_info->plus_sign && num >= 0) || num < 0;
    ushort_t exp_size = fmt_info->is_long_double ? 15 : 11;
    ushort_t mant_size = fmt_info->is_long_double ? 64 : 52;

    float_info_t *flt_info = new_float_info(exp_size, mant_size);

    if (flt_info == NULL)
        return;

    set_float_parts(num, exp_size, mant_size, flt_info);
    str = check_validity(flt_info);

    if (str == NULL)
    {
        str = convert_float_to_str(num, fmt_info, flt_info);
        num_len = get_num_len(num, fmt_info, str);
        max_w = get_max_width(num_len, fmt_info);

        zeros_count = calculate_zeros_count(fmt_info, max_w, num_len);
        print_padding(fmt_info, num, num_len, max_w, zeros_count);
        print_number(fmt_info, num, num_len, str);
    }
    else
    {
        print_non_convertible(fmt_info, str);
    }

    cleanup(str, flt_info);
}

/**
 * convert_float_to_str - Convert a float number to a formatted string
 * @num: The double number to print
 * @fmt_info: The format info
 * @flt_info: The float info
 * Return: The converted string
 */
char *convert_float_to_str(double num, fmt_info_t *fmt_info, float_info_t *flt_info)
{
    int precision = get_precision(fmt_info);
    char *str = convert_and_round_float(num, fmt_info, flt_info, precision);
    return str;
}

/**
 * printf_float - Prints the decimal representation of a double
 * @args_list: The arguments list
 * @fmt_info: The format info
 */
void printf_float(va_list *args_list, fmt_info_t *fmt_info)
{
    double num = va_arg(*args_list, double);
    calculate_and_print_float(num, fmt_info);
} 
