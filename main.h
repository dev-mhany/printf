#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#ifndef TRUE
#define TRUE 1
#endif
#ifndef T
#define T 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif
#define MAX_WIDTH "2147483647"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) > (0) ? (a) : (0 - (a)))
#define NEG(a) ((a) < (0) ? (0) : ((a)))
#define CMP(a, b) ((a) < (b) ? (b) : ((a)))
#define TOUPPER(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 6 - 26 : (c))
#define TOLOWER(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + 6 + 26 : (c))

/**
 * struct format_info - Contains information about the options
 * \ and flags appearing in an instance of the conversion specifier
 * @precision: The specified precision
 * @width: The length of the formatted data
 * @specifier: The specified conversion specifier character
 * @is_long_double: Specifies the presence of the 'L' length modifier
 * @is_long_long: Specifies the presence of the 'll' length modifier
 * @is_long: Specifies the presence of the 'l' length modifier
 * @is_short: Specifies the presence of the 'h' length modifier
 * @is_char: Specifies the presence of the 'hh' length modifier
 * @is_precision_set: Specifies the presence of a precision value
 * @is_width_set: Specifies the presence of a width value
 * @hash: Specifies the presence of the '#' flag
 * @space: Specifies the presence of the ' ' (invisible plus sign) flag
 * @left_align: Specifies the presence of the '-' (left_align-align) flag
 * @plus_sign: Specifies the presence of the '+' flag
 * @group: The current locale's digit separator for integers
 * @padding: This is the character to use for padding the output
 */
struct format_info
{
	int precision;
	int width;
	char specifier;
	char is_long_double;
	char is_long;
	char is_long_long;
	char is_short;
	char is_char;
	char is_precision_set;
	char is_width_set;
	char hash;
	char space;
	char left_align;
	char plus_sign;
	char group;
	char padding;
};
typedef struct format_info fmt_info_t;
/**
 * struct spec_printer - Represents a function that prints an argument
 * \ based on a determined format
 * @specifier: The conversion specifier
 * @print_arg: The pointer to the printing function
 */
struct spec_printer
{
	char specifier;
	void (*print_arg)(va_list *args, fmt_info_t *fmt_info);
};
typedef struct spec_printer spec_printer_t;
typedef unsigned char uchar_t;
typedef unsigned short ushort_t;

/**
 * struct float_info - Represents the IEE754 specification of a float
 * @sign: The sign of the float
 * @exponent: The exponent of the float
 * @mantissa: The mantissa of the float
 */
struct float_info
{
	char sign;
	char *exponent;
	char *mantissa;
};
typedef struct float_info float_info_t;


int _putchar(char c);
int _putstring(char *str);
int write_to_buffer(char c, char action);
int _printf(const char *format, ...);
void placeHolder(va_list *args_list, fmt_info_t *fmt_info);

void print_n_times(char c, int n);
void _putnchrs(int n, ...);
char is_letter(char c);
void set_format_error(const char *, int *, int len, int, int *);
void _putnum(int zeros_count, long num, char *str);

void init_format_info(fmt_info_t *specifier);
int read_format_info(const char *, va_list, fmt_info_t *, int *);
fmt_info_t *new_format_info();
float_info_t *new_float_info(ushort_t exponent_size, ushort_t mantissa_size);
void free_float_info(float_info_t *flt_info);

void calculate_and_print_float(double num, fmt_info_t *fmt_info);
char *convert_float_to_str(double num, fmt_info_t *fmt_info,
float_info_t *flt_info);
void printf_float(va_list *args_list, fmt_info_t *fmt_info);
float_info_t *setup_float_info(fmt_info_t *fmt_info);
int should_have_sign(double num, fmt_info_t *fmt_info);
char *calculate_float_str(double num, float_info_t *flt_info,
fmt_info_t *fmt_info);
int calculate_zeros_count(fmt_info_t *fmt_info, int max_w, int num_len);
void print_float_padding(fmt_info_t *fmt_info, double num,
int num_len, int max_w, int zeros_count);
void print_float_number(fmt_info_t *fmt_info, double num,
int num_len, char *str);

int set_number(const char *str, int *number);
void set_length(char cur, int *pos, fmt_info_t *fmt_info);
int set_flags(const char *str, fmt_info_t *fmt_info);
void set_precision(const char *str, va_list args,
	fmt_info_t *fmt_info, int *i, int *error_status);

void printf_percent(va_list *args_list, fmt_info_t *fmt_info);
void printf_pointer(va_list *args_list, fmt_info_t *fmt_info);
void printf_char(va_list *args_list, fmt_info_t *fmt_info);
void printf_string(va_list *args_list, fmt_info_t *fmt_info);

void printf_integer(va_list *args_list, fmt_info_t *fmt_info);
void printf_hex(va_list *args_list, fmt_info_t *fmt_info);
void printf_octal(va_list *args_list, fmt_info_t *fmt_info);
void printf_unsigned(va_list *args_list, fmt_info_t *fmt_info);

void printf_binary(va_list *args_list, fmt_info_t *fmt_info);
void printf_rot13(va_list *args_list, fmt_info_t *fmt_info);
void printf_rev_str(va_list *args_list, fmt_info_t *fmt_info);
void printf_S(va_list *args_list, fmt_info_t *fmt_info);
void printf_float(va_list *args_list, fmt_info_t *fmt_info);

int _strlen(char *str);
void mem_set(char *str, int n, char c);
void left_shift(char *str, int n);
int index_of(char *str, char c);
void rev_string(char *s);

char *append_char(char *str, char c, int n, char can_free);
char *delete_char(char *str, char c, char can_free);
char *insert_char(char *str, int pos, char c, char can_free);
int count_char(char *str, char c);
char *str_cat(char *left_align, char *right, char can_free);

char *sub_str(char *str, int i, char can_free);
char *trim_start(char *str, char c, char can_free);
char *trim_end(char *str, char c, char can_free);
char *str_copy(char *str);

char hex_digit(char c);
char compare_numbers(char *left_align, char *right);
int str_to_int(char *num);
int bin_to_int(char *bin_str);
char *long_to_octal(unsigned long num);

char *add_int(char *left_align, char *right, int can_free);
char *add_float(char *left_align, char *right, char can_free);

char *multiply(char *num, char *multiple);
char *mul_int(char *num1, char *num2, char can_free);
char *mul_float(char *left_align, char *right, char can_free);

char *div_by_pow_10(char *num, unsigned short n, char can_free);
char *two_pow_x(short n);
char *five_pow_n(unsigned short n);
unsigned int two_pow_n(unsigned int n);
char *unsigned_long_to_hex(unsigned long num, char upper);

char *round_float(char *num, unsigned int precision, char can_free);
char *round_float_to_int(char *num, int len, int dec_pos, int frac_len);

char *unsigned_long_to_str(unsigned long num);
char *long_to_str(long num);
char *ptr_to_str(void *ptr);
char *check_validity(float_info_t *flt_info);

void set_float_parts(double num,	uchar_t exponent_size,
	uchar_t mantissa_size, float_info_t *float_info);
char *_to_dec_fraction(char *mantissa, unsigned short frac_len);
char *float_to_str(float_info_t *flt_info, char can_free);

char is_digit(char c);
char non_custom_specifier(char c);
char is_specifier(char c);
char flag_characters(char c);
char length_modifier(char c);
#endif
