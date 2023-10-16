#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * print_formatted_float - Prints the formatted float with given format info
 * @str: The formatted float string
 * @fmt_info: The format info
 * @num: The float number
 * @has_sign: Whether the float number has a sign
 *
 * This function takes a formatted float string and format info and prints
 * the float with proper padding and alignment as specified in fmt_info.
 */
void print_formatted_float(const char *str, fmt_info_t *fmt_info, int num, int has_sign) {
    int num_len = _strlen(str) + ((fmt_info->plus_sign && num >= 0) ? 1 : 0);
    int max_w = MAX(fmt_info->width, num_len);
    int zeros_count = (max_w - num_len) * !fmt_info->left_align * (fmt_info->padding == '0');
    int len = max_w - (zeros_count + num_len);
    int i;

    for (i = 0; !fmt_info->left_align && i < len; i++)
        _putchar(' ');

    if (has_sign)
        _putchar(num < 0 ? '-' : '+');

    for (i = 0; !fmt_info->left_align && i < zeros_count; i++)
        _putchar('0');

    for (i = has_sign ? 1 : 0; *(str + i) != '\0'; i++)
        _putchar(*(str + i));

    for (i = 0; fmt_info->left_align && i < len; i++)
        _putchar(' ');
}

