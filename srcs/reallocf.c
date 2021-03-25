#include "../includes/malloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *block;

    pthread_mutex_lock(&lock);
    block = malloc(size);
    ft_memcpy(block, ptr, ft_strlen(ptr));
    free(ptr);
    pthread_mutex_unlock(&lock);
    return block;
}