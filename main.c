#include "includes/malloc.h"

#include <stdint.h>

char hex_digit(int v)
{
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10; // <-- Here
}

void print_address_hex(void *p0)
{
    int i;
    uintptr_t p = (uintptr_t)p0;

    ft_putchar('0');
    ft_putchar('x');
    for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4)
    {
        ft_putchar(hex_digit((p >> i) & 0xf));
    }
}

void logger(char *ptr, int limitNum)
{
    int i = -1;
    while (++i < limitNum)
        printf("ptr[%d] = %c\n", i, ptr[i]);
}

char *fill(char *ptr, int asciiNum)
{

    int i = -1;
    while (++i < 9)
    {

        ptr[i] = i + asciiNum;
        // print_address_hex(&ptr[i]);
        ft_putchar(ptr[i]);
        ft_putchar('\n');
    }
    ptr[i] = '\0';
    return ptr;
}

int main()
{
    char *ptr = NULL;
    char *str = NULL;

    ptr = (char *)malloc(sizeof(char) * 100);
    ptr = fill(ptr, 65);
    str = (char *)malloc(sizeof(char) * 100);
    str = fill(str, 97);
    logger(ptr, 10);
    return (0);
}