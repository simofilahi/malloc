#include "includes/malloc.h"

#include <stdint.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include "./libft/libft.h"

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
    while (++i < 10)
    {

        ptr[i] = i + asciiNum;
        // print_address_hex(&ptr[i]);
        // ft_putchar(ptr[i]);
        // ft_putchar('\n');
    }
    ptr[i] = '\0';
    return ptr;
}

int main()
{
    char *ptr = NULL;
    // char *str = NULL;
    char *nbr = NULL;
    // char *d = NULL;

    // printf("****************************\n");

    // // logger(ptr, 10);
    // printf("****************************\n");
    // str = (char *)malloc(sizeof(char) * 11);
    // // printf("ret str @ => %p\n", str);
    // str = fill(str, 97);
    // logger(str, 10);
    printf("****************************\n");
    nbr = (char *)malloc(sizeof(char) * 11);
    nbr = fill(nbr, 48);
    logger(nbr, 10);
    printf("****************************\n");
    ptr = (char *)malloc(sizeof(char) * 11);
    // printf("ret ptr @ => %p\n", ptr);
    ptr = fill(ptr, 65);
    logger(ptr, 10);
    printf("****************************\n");
    nbr = realloc(nbr, sizeof(char) * 11);
    ft_strcat(nbr, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello");
    logger(nbr, 15);

    // printf("ret nbr @ => %p\n", nbr);
    // nbr = fill(nbr, 48);
    // // logger(ptr, 100);
    // printf("****************************\n");
    // d = (char *)malloc(sizeof(char) * 11);
    // printf("ret d @ => %p\n", d);
    // free(d);
    return (0);
}