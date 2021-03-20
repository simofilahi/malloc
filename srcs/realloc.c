#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *chunk;
    void *pptr;

    pthread_mutex_lock(&lock);
    pptr = ptr;
    free(ptr);
    chunk = malloc(size);
    ft_memcpy(chunk, pptr, ft_strlen(ptr));
    pthread_mutex_unlock(&lock);
    return chunk;
}