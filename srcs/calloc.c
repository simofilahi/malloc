#include "../includes/malloc.h"

void *calloc(size_t count, size_t size)
{
    void *ptr;

    pthread_mutex_lock(&lock);
    ptr = malloc(count * size);
    ft_bzero(ptr, count * size);
    pthread_mutex_unlock(&lock);
    return (ptr);
}