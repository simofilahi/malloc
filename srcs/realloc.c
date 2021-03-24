#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *block;
    min_printf("realloc incoming address ", ptr, 1);
    block = malloc(size);
    if (!block)
        return ptr;
    else
    {
        if (ptr)
        {
            t_block *p;
            size_t len;

            p = (t_block *)ptr - 1;
            if (p->blockSize > size)
                len = size;
            else 
                len = p->blockSize;
            ft_putstr("len  ");
            ft_putnbr(p->blockSize);
            ft_memcpy(block, ptr, len);
            ft_putstr("block : ");
            ft_putstr(block);
            ft_putchar('\n');
            free(ptr);
            // free(block);
        }
    }
    // pthread_mutex_unlock(&lock);
    min_printf("realloc returned address ", block, 1);
    return block;
}