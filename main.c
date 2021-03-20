#include "includes/malloc.h"

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <stdlib.h>
// #include <stdio.h>
// #include "./libft/libft.h"

// char hex_digit(int v)
// {
//     if (v >= 0 && v < 10)
//         return '0' + v;
//     else
//         return 'a' + v - 10;
// }

// void print_address_hex(void *p0)
// {
//     int i;
//     uintptr_t p = (uintptr_t)p0;

//     ft_putchar('0');
//     ft_putchar('x');
//     for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4)
//     {
//         ft_putchar(hex_digit((p >> i) & 0xf));
//     }
// }

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

void *func()
{
    char *ptr = NULL;

    // puts("I'M HERE\n");
    ptr = (char *)malloc(sizeof(char) * 10);
    show_alloc_mem();
    return NULL;
}

int main()
{
    char *ptr = NULL;
    char *str = NULL;
    char *nbr = NULL;
    // char *d = NULL;

    ptr = (char *)malloc(sizeof(char) * 10);
    str = (char *)malloc(sizeof(char) * 10);
    nbr = (char *)malloc(sizeof(char) * 10);
    show_alloc_mem_ex();
    free(ptr);
    free(str);
    show_alloc_mem_ex();
    ptr = (char *)malloc(sizeof(char) * 10);
    show_alloc_mem_ex();
    ptr = (char *)malloc(sizeof(char) * 11111);
    show_alloc_mem_ex();
    free(NULL);
    show_alloc_mem_ex();
    // pthread_mutex_init(&lock, NULL);
    // pthread_t thread_id;
    // int error = pthread_create(&thread_id, NULL, func, NULL);
    // if (error != 0)
    //     printf("\nThread can't be created : [%s]", strerror(error));

    // // puts("I'M HERE 2\n");
    // ptr = (char *)malloc(sizeof(char) * 10);
    // show_alloc_mem();
    // pthread_join(thread_id, NULL);
    // pthread_mutex_destroy(&lock);

    return (0);
}