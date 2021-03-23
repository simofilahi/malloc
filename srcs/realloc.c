#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *block;
    // min_printf("realloc incoming address", ptr, 1);
    // pthread_mutex_lock(&lock);
    if (ptr)
    {
        ptr = ft_bzero(ptr, ft_strlen(ptr));
    }
    if (!ptr)
    {
        ft_putstr("before block : ");
        // ptr = NULL;
    }
    // ft_putendl(ptr);
    // ft_putstr("after");
    block = malloc(size);
    if (block)
    {
        if (ptr)
        {
            ft_memcpy(block, ptr, ft_strlen(ptr));
            // ft_putstr("block : ");
            // ft_putstr(block);
        }
        // free(ptr);
    }
    // pthread_mutex_unlock(&lock);
    min_printf("realloc returned address ", block, 1);
    return block;
}