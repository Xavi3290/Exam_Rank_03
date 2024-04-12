#include <unistd.h>
#include <stdarg.h>

void put_str(char *str, int *len)
{
    int i = 0;
    
    if (!str)
        str = "(null)";
    while (str[i])
    {
        write(1, &str[i], 1);
        (*len)++;
        i++;
    }
}

void put_nbr_base(int num, int base, int *len)
{
    char    *hex = "0123456789abcdef";

    if (num < 0)
    {
        num *= -1;
        (*len)++;
        write(1, "-", 1);
    }
    if (num >= base)
        put_nbr_base((num/base), base, len);
    (*len)++;
    write(1, &hex[num % base], 1);
}

int ft_printf(const char *format, ...)
{
    int len = 0;
    int i = 0;
    va_list args;
    
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 's')
                put_str(va_arg(args, char *), &len);
            else if (format[i] == 'd')
                put_nbr_base(va_arg(args, int), 10, &len);
            else if(format[i] == 'x')
                put_nbr_base((int)va_arg(args, unsigned int), 16, &len);
        }
        else
        {
            len++;
            write(1, &format[i], 1);
        }
        i++;
    }
    va_end(args);
    return (len);
}

int main(void)
{
    ft_printf("%d\n",ft_printf("%s\n", "toto"));
    ft_printf("%d\n",ft_printf("Magic %s is %d \n", "number", 42));
    ft_printf("%d\n",ft_printf("Hexadecimal for %d is %x\n", 42, 42));
    
    return (0);
}