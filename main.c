#include "includes/malloc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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

// void *func()
// {
//     char *ptr = NULL;
//     ptr = (char *)malloc(sizeof(char) * 10);
//     return NULL;
// }

int main()
{
	// char *ptr = NULL;
	// char *nbr = NULL;
	// char *str = NULL;
	// char *s = NULL;
  // char *t = NULL;

	// ptr = malloc(100);
	// nbr = malloc(200);
  // t = malloc(150);
	// str = malloc(5000);
	// s = malloc(50000);
	// show_alloc_mem();
  // ft_putstr("******************************\n");
	// free(ptr);
  // show_alloc_mem();
  //  ft_putstr("******************************\n");
	// free(nbr);
 	// show_alloc_mem();
  //   ft_putstr("******************************\n");
  // free(t);
  // show_alloc_mem();
  //  ft_putstr("******************************\n");
  // ptr = malloc(100);
	// show_alloc_mem();
  //  ft_putstr("******************************\n");
  // 	ptr = malloc(10);
	// show_alloc_mem();
  //  ft_putstr("******************************\n");

  // 	// nbr = malloc(50);
	// show_alloc_mem();
	// free(s);
	// show_alloc_mem();
    // char *ptr = NULL;
    // char *str = NULL;
    // char *nbr = NULL;
    // char *d = NULL;

    // printf("****************************\n");

    // // logger(ptr, 10);
    // printf("****************************\n");

    // // printf("ret str @ => %p\n", str);
    // str = fill(str, 97);
    // logger(str, 10);
    // printf("****************************\n");
    // int i = 0;
    // nbr = (char *)malloc(sizeof(char) * 500);
    // nbr = (char *)malloc(sizeof(char) * 500);
    // nbr = (char *)malloc(sizeof(char) * 80);
    // nbr = (char *)malloc(sizeof(char) * 80);
    // nbr = (char *)malloc(sizeof(char) * 100);
    // nbr = (char *)malloc(sizeof(char) * 80);
    // nbr = (char *)malloc(sizeof(char) * 20);
    // nbr = (char *)malloc(sizeof(char) * 10);
    // nbr = (char *)malloc(sizeof(char) * 200);
    // nbr = (char *)malloc(sizeof(char) * 150);
    // nbr = (char *)malloc(sizeof(char) * 300);
    // nbr = (char *)malloc(sizeof(char) * 10000);
    // ptr = (char *)malloc(sizeof(char) * 20000);
    // str = (char *)malloc(sizeof(char) * 30000);
    // ptr = (char *)malloc(sizeof(char) * 10);
    // nbr = (char *)malloc(sizeof(char) * 10);
    // str = (char *)malloc(sizeof(char) * 10);
    // // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    // // show_alloc_mem();
    // // debugger();
    // // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");
    // // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    // free(ptr);
    // free(nbr);
    // show_alloc_mem();
    // debugger();
    // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");
    // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

    // char *ptr;

    // ptr = NULL;
    // ptr = malloc(1024);
    // show_alloc_mem_ex();
    // free(ptr);
    // show_alloc_mem_ex();
   // pthread_t thread_id[3];

    // // i = 0;
    // // while (i < 100)
    // // {
    // malloc(500);

  //  pthread_create(&thread_id[0], NULL, func, NULL);
    //pthread_create(&thread_id[1], NULL, func, NULL);
    //pthread_create(&thread_id[2], NULL, func, NULL);
    //pthread_join(thread_id[0], NULL);
    // ft_putstr("hey 1\n");
    //pthread_join(thread_id[1], NULL);
    // ft_putstr("hey 2\n");
   // pthread_join(thread_id[2], NULL);
    // ft_putstr("hey 3\n");
    //show_alloc_mem();
    //pthread_mutex_destroy(&g_lock);

    //     i++;
    // }

    // debugger();
    // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");
    // int i = 0;

    // while (i < 1000000)
    // {
    //     nbr = (char *)malloc(sizeof(char) * 80);
    //     i++;
    // }

    // nbr = fill(nbr, 48);
    // logger(nbr, 10);
    // // printf("ret ptr @ => %p\n", ptr);
    // // ptr = fill(ptr, 65);
    // // logger(ptr, 10);
    // printf("****************************\n");
    // nbr = realloc(nbr, sizeof(char) * 11);
    // ft_strcat(nbr, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello");
    // logger(nbr, 15);
    // printf("ret nbr @ => %p\n", nbr);
    // nbr = fill(nbr, 48);
    // // logger(ptr, 100);
    // printf("****************************\n");
    // d = (char *)malloc(sizeof(char) * 11);
    // printf("ret d @ => %p\n", d);
    // free(d);
    return (0);
}
