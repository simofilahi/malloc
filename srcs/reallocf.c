#include "../includes/malloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *block;

    pthread_mutex_lock(&lock);
    block = malloc(size);
    if (ptr)
        ft_memcpy(block, ptr, ft_strlen(ptr));
    if (!block)
        free(ptr);
    pthread_mutex_unlock(&lock);
    return block;
}