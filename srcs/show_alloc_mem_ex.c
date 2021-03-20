#include "../includes/malloc.h"

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
}

static void print_blocks_infos(t_block *curr)
{
    min_printf("   -> BLOCK          : ", curr, 0);
    printf(" block @ %p\n", curr);
    ft_putstr("     - USED          : ");
    if (curr->used)
        ft_putendl("YES");
    else
        ft_putendl("NO");
    ft_putstr("     - SIZE          : ");
    ft_putnbr(curr->blockSize);
    ft_putendl(" bytes");
}

void show_alloc_mem_ex()
{
    t_memZone *currMemZone;
    t_block *curr;

    pthread_mutex_lock(&lock);
    currMemZone = headZone;
    ft_putstr("\n*************************************\n");
    while (currMemZone)
    {
        print_zones_name(currMemZone);
        ft_putstr(", ");
        ft_putnbr(currMemZone->zoneSize);
        ft_putendl(" bytes ");
        curr = currMemZone->headBlock;
        while (curr)
        {
            print_blocks_infos(curr);
            curr = curr->next;
        }
        currMemZone = currMemZone->next;
    }
    ft_putstr("*************************************\n");
    pthread_mutex_unlock(&lock);
}