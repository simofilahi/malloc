#include "../includes/malloc.h"

void *calloc(size_t count, size_t size)
{
    void *ptr;

    min_printf("calloc begin ", NULL, 1);
    // pthread_mutex_lock(&lock);
    ptr = malloc(count * size);
    ptr = ft_bzero(ptr, count * size);
    // pthread_mutex_unlock(&lock);
    min_printf("calloc returned address ", ptr, 1);
    // show_alloc_mem_ex();
    return (ptr);
}