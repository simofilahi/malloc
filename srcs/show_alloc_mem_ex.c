#include "../includes/malloc.h"

// PRINT ZONES NAME
static void print_zones_name(t_memZone *currMemZone)
{
    if (currMemZone->type == TINY_ZONE)
        min_printf("TINY : ", currMemZone, 0);
    else if (currMemZone->type == SMALL_ZONE)
        min_printf("SMALL : ", currMemZone, 0);
    else if (currMemZone->type == EXTRA_ZONE)
        min_printf("EXTRA : ", currMemZone, 0);
    else
        min_printf("LARGE : ", currMemZone, 0);
    ft_putstr(", ");
    ft_putnbr((long)currMemZone->zoneSize);
    ft_putendl(" bytes ");
}

// PRINT BLOCK INFORMATION
static void print_blocks_infos(t_block *curr, size_t *totalSize)
{
    size_t blockSize;

    if (!curr->mergedCount)
        blockSize = curr->blockSize - sizeof(t_block);
    else
        blockSize = curr->blockSize - (sizeof(t_block) * (curr->mergedCount + 1));
    min_printf("   -> BLOCK          : ", curr + 1, 0);
    min_printf(" - ", (((void *)(curr + 1)) + blockSize), 1);
    ft_putstr("     - USED          : ");
    if (curr->used)
        ft_putendl("YES");
    else
        ft_putendl("NO");
    ft_putstr("     - SIZE          : ");
    ft_putnbr((long)blockSize);
    ft_putendl(" bytes");
    *totalSize += blockSize;
}

// DISPLAY MORE DETAILS ABOUT ALLOCATION
void show_alloc_mem_ex()
{
    t_memZone *currMemZone;
    t_block *curr;
    size_t totalSize;

    pthread_mutex_lock(&lock);
    currMemZone = headZone;
    totalSize = 0;
    ft_putstr("\n*************************************\n");
    while (currMemZone)
    {
        print_zones_name(currMemZone);
        curr = currMemZone->headBlock;
        while (curr)
        {
            print_blocks_infos(curr, &totalSize);
            curr = curr->next;
        }
        currMemZone = currMemZone->next;
    }
    ft_putstr("Total: ");
    ft_putnbr((long)totalSize);
    ft_putendl(" bytes");
    ft_putstr("*************************************\n");
    pthread_mutex_unlock(&lock);
}