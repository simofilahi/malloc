#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *chunk;
    void *pptr;

    pptr = ptr;
    free(ptr);
    chunk = malloc(size);
    ft_memcpy(chunk, pptr, ft_strlen(ptr));
    return chunk;
}