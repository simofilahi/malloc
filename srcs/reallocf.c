#include "../includes/malloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *block;
    min_printf("reallocf incoming address", ptr, 1);
    // pthread_mutex_lock(&lock);

    block = malloc(size);
    ft_memcpy(block, ptr, ft_strlen(ptr));
    free(ptr);
    // pthread_mutex_unlock(&lock);
    min_printf("reallocf returned address", block, 1);
    return block;
}