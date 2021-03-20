
#include "../includes/malloc.h"

void print_address_hex(unsigned long n)
{
    unsigned long base;
    base = 16;

    if (n > 0)
        print_address_hex(n /= base);
    if ((n % base) >= 10)
        ft_putchar((n % base) + 'a' - 10);
    else
        ft_putchar((n % base) + '0');
}

void min_printf(void *str, void *ptr, int nflag)
{
    if (str)
        ft_putstr(str);
    if (ptr)
        print_address_hex((unsigned long)ptr);
    if (nflag)
        ft_putchar('\n');
}