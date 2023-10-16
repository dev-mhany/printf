#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * _putstring - Writes the given string to the buffer.
 * @str: The string to write.
 * Return: On success, returns 1. On error, returns -1.
 */
int _putstring(char *str)
{
    int i, out;
    for (i = 0; str && str[i] != '\0'; i++) {
        out = _putchar(str[i]);
    }
    return out;
}

/**
 * _putchar - Writes the character c to the buffer.
 * @c: The character to print.
 * Return: On success, returns 1. On error, returns -1.
 */
int _putchar(char c)
{
    return write_to_buffer(c, 0);
}

/**
 * write_to_buffer - Writes a char to the buffer based on an action code.
 * @c: The character to write.
 * @action: The action to perform. See function body for details.
 * Return: On success, returns 1. On error, returns -1.
 */
int write_to_buffer(char c, char action)
{
    static int i;
    static int chars_count;
    static char buffer[1024];
    static char out;

    if (i < 1024 && action == 0) {
        out = chars_count < 1 ? 1 : out;
        buffer[i++] = c;
        chars_count++;
    }

    if (i >= 1024 || action == 1) {
        out = write(1, buffer, i);
        fflush(stdout);
        i = 0;
        mem_set(buffer, 1024, 0);
    }

    if (action == -1) {
        i = 0;
        chars_count = 0;
        mem_set(buffer, 1024, 0);
    }

    if (action == -2) {
        return chars_count;
    }

    return out;
}

/**
 * _putnum - Prints a number to the buffer.
 * @zeros_count: The number of zeros to print.
 * @num: The number.
 * @str: The string representation of the number.
 */
void _putnum(int zeros_count, long num, char *str)
{
    int i;

    for (i = 0; i < zeros_count; i++) {
        _putchar('0');
    }

    for (i = num < 0 ? 1 : 0; str[i] != '\0'; i++) {
        _putchar(str[i]);
    }
}

/**
 * _putnchrs - Prints multiple characters.
 * @n: The number of characters to print.
 */
void _putnchrs(int n, ...)
{
    int i;
    va_list args;

    if (n <= 0) return;

    va_start(args, n);
    for (i = 0; i < n; i++) {
        _putchar(va_arg(args, int));
    }
    va_end(args);
}
*******
/**
 * _printf - Our version of the printf function.
 * @format: Format string.
 * @...: Variable arguments.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    for (int i = 0; format && format[i] != '\0'; i++) {
        if (format[i] == '%' && (format[i + 1] == 'c' || format[i + 1] == 's' || format[i + 1] == '%')) {
            switch (format[i + 1]) {
                case 'c':
                    count += write(1, &(char){va_arg(args, int)}, 1);
                    i++;  // skip the specifier
                    break;
                case 's':
                {
                    char *str = va_arg(args, char*);
                    for (int j = 0; str && str[j] != '\0'; j++) {
                        write(1, &str[j], 1);
                        count++;
                    }
                    i++;  // skip the specifier
                    break;
                }
                case '%':
                    count += write(1, &"%", 1);
                    i++;  // skip the specifier
                    break;
            }
        } else {
            count += write(1, &format[i], 1);
        }
    }

    va_end(args);

    return count;
}

int main() {
    char character = 'A';
    char *string = "Hello, world!";
    _printf("Character: %c\nString: %s\nPercentage symbol: %%\n", character, string);
    return 0;
}