#include "../includes/malloc.h"

void debugger()
{
    t_memZone *currMemZone;

    currMemZone = headZone;
    printf("head %p\n", headZone);
    ft_putendl("*******************\n");
    while (currMemZone)
    {
        printf("_________________________________\n");
        printf("currMemZone @ => %p\n", currMemZone);
        printf("currMemZone size %lu\n", currMemZone->zoneSize);
        printf("currMemZone start address @ => %p\n", currMemZone->startZone);
        printf("currMemZone headblock address @ => %p\n", currMemZone->headBlock);
        if (currMemZone->type == TINY_ZONE)
            printf("THIS IS A TINY ZONE\n");
        else if (currMemZone->type == SMALL_ZONE)
            printf("THIS IS A SMALL ZONE\n");
        else if (currMemZone->type == EXTRA_ZONE)
            printf("THIS IS AN EXTRA ZONE\n");
        else
            printf("THIS IS A LARGE ZONE\n");
        printf("_________________________________\n");
        t_block *curr;
        curr = currMemZone->headBlock;
        while (curr)
        {
            printf("++++++++++++++++++++++++++++\n");
            printf("curr->size %lu\n", curr->blockSize);
            printf("curr->used %d\n", curr->used);
            printf("++++++++++++++++++++++++++++\n");
            curr = curr->next;
        }

        currMemZone = currMemZone->next;
    }
    ft_putendl("*******************\n");
}

void show_alloc_mem()
{
    t_memZone *currMemZone;
    t_block *curr;
    size_t totalSize;

    currMemZone = headZone;
    totalSize = 0;
    while (currMemZone)
    {
        if (currMemZone->type == TINY_ZONE)
            min_printf("TINY : ", currMemZone, 1);
        else if (currMemZone->type == SMALL_ZONE)
            min_printf("SMALL: ", currMemZone, 1);
        else if (currMemZone->type == EXTRA_ZONE)
            min_printf("EXTRA: ", currMemZone, 1);
        else
            min_printf("LARGE: ", currMemZone, 1);
        curr = currMemZone->headBlock;
        while (curr)
        {
            if (curr->used)
            {
                min_printf("", curr, 0);
                min_printf(" - ", NULL, 0);
                min_printf("", (curr - curr->blockSize), 0);
                ft_putstr(" : ");
                ft_putnbr((int)curr->blockSize);
                min_printf(" bytes", NULL, 1);
                ft_putchar('\n');
                totalSize += curr->blockSize;
            }
            curr = curr->next;
        }
        currMemZone = currMemZone->next;
    }
    printf("Total: %lu bytes\n", totalSize);
}
