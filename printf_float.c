#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * print_float_parts - Helper function to print float parts.
 * @str: string representation of the float
 * @num: original number to print
 * @fmt_info: The format info
 */
void print_float_parts(char *str, double num, fmt_info_t *fmt_info)
{
	int i, len, num_len, zeros_count, max_w;
	char has_sign = (fmt_info->plus_sign && num >= 0) || num < 0;

	num_len = _strlen(str) + ((fmt_info->plus_sign && num >= 0) ? 1 : 0);
	max_w = MAX(fmt_info->width, num_len);
	zeros_count = (max_w - num_len) * !fmt_info->left_align;
	zeros_count *= (fmt_info->padding == '0');
	len = max_w - (zeros_count + num_len);
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

/**
 * calculate_and_print_float - Calculate and print the decimal number.
 * @num: The double number to print
 * @fmt_info: The format info
 */
void calculate_and_print_float(double num, fmt_info_t *fmt_info)
{
	char *str;
	ushort_t exp_size = fmt_info->is_long_double ? 15 : 11;
	ushort_t mant_size = fmt_info->is_long_double ? 64 : 52;
	float_info_t *flt_info;

	flt_info = new_float_info(exp_size, mant_size);
	if (!flt_info)
		return;

	set_float_parts(num, exp_size, mant_size, flt_info);
	str = check_validity(flt_info);
	if (!str) 
	{
		str = float_to_str(flt_info, FALSE);
		str = round_float(str, fmt_info->is_precision_set ?
		fmt_info->precision : 6, T);
		print_float_parts(str, num, fmt_info);
		}
		else 
	{
		for (int i = 0; i < _strlen(str); i++)
			_putchar(fmt_info->specifier == 'f' ? TOLOWER(str[i]) : TOUPPER(str[i]));
	}
	free(str);
	free_float_info(flt_info);
}

/**
 * printf_float - Prints the decimal representation of a double.
 * @args_list: The arguments list
 * @fmt_info: The format info
 */
void printf_float(va_list *args_list, fmt_info_t *fmt_info)
{
	double num;

	num = va_arg(*args_list, double);
	calculate_and_print_float(num, fmt_info);
}
