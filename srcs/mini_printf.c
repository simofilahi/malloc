
#include "../includes/malloc.h"
#include <stdint.h>

char hex_digit(int v)
{
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10;
}

void print_address_hex(void *p0, int nflag)
{
    int i;
    uintptr_t p = (uintptr_t)p0;

    ft_putchar('0');
    ft_putchar('x');
    for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4)
    {
        ft_putchar(hex_digit((p >> i) & 0xf));
    }
    if (nflag)
        ft_putchar('\n');
}

void min_printf(void *str, void *ptr, int nflag)
{
    if (str)
        ft_putstr(str);
    if (ptr)
        print_address_hex(ptr, nflag);
}