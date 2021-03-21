#include "../includes/malloc.h"

// PRINT MEMORY ZONE NAME
void print_mem_names(t_memZone *currMemZone)
{
    if (currMemZone->type == TINY_ZONE)
        min_printf("TINY : ", currMemZone, 1);
    else if (currMemZone->type == SMALL_ZONE)
        min_printf("SMALL: ", currMemZone, 1);
    else if (currMemZone->type == EXTRA_ZONE)
        min_printf("EXTRA: ", currMemZone, 1);
    else
        min_printf("LARGE: ", currMemZone, 1);
}

// PRINT MEMORY BLOCK INFORMATION
void print_blocks_infos(t_block *curr, size_t *totalSize)
{
    size_t blockSize;

    blockSize = 0;
    while (curr)
    {
        if (curr->used)
        {
            if (!curr->mergedCount)
                blockSize = curr->blockSize - sizeof(t_block);
            else
                blockSize = curr->blockSize - (sizeof(t_block) * (curr->mergedCount + 1));
            min_printf("", curr + 1, 0);
            min_printf(" - ", (((void *)(curr + 1)) + blockSize), 0);
            ft_putstr(" : ");
            ft_putnbr((long)blockSize);
            min_printf(" bytes", NULL, 1);
            *totalSize += blockSize;
        }
        curr = curr->next;
    }
}

// DISPLAY MEMORY ALLOCATION DETAILS
void show_alloc_mem()
{
    t_memZone *currMemZone;
    size_t totalSize;

    pthread_mutex_lock(&lock);
    currMemZone = headZone;
    totalSize = 0;
    while (currMemZone)
    {
        print_mem_names(currMemZone);
        print_blocks_infos(currMemZone->headBlock, &totalSize);
        currMemZone = currMemZone->next;
    }
    ft_putstr("Total: ");
    ft_putnbr((long)totalSize);
    ft_putendl(" bytes");
    pthread_mutex_unlock(&lock);
}
