#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/**
 * _printf - Our own printf function
 * @format: The format string
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0, i, j;
    char *str;

    va_start(args, format);
    for (i = 0; format && format[i]; i++)
    {
        if (format[i] == '%' && (format[i + 1] == 'c' || format[i + 1] == 's' || format[i + 1] == '%'))
        {
            i++; /* Increment to skip the specifier */
            switch (format[i])
            {
                case 'c':
                    count += _putchar(va_arg(args, int));
                    break;
                case 's':
                    str = va_arg(args, char*);
                    for (j = 0; str && str[j]; j++)
                        count += _putchar(str[j]);
                    break;
                case '%':
                    count += _putchar('%');
                    break;
            }
        }
        else
        {
            count += _putchar(format[i]);
        }
    }
    va_end(args);
    return (count);
}

/**
 * main - Main function
 *
 * Return: 0 if success
 */
int main(void)
{
    char character = 'A';
    char *string = "Hello, world!";

    _printf("Character: %c\nString: %s\nPercentage symbol: %%\n", character, string);
    return (0);
}
