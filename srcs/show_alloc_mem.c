#include "../includes/malloc.h"

void show_alloc_mem()
{
    t_memZone *currMemZone;

    currMemZone = headZone;
    ft_putendl("*******************\n");
    while (currMemZone)
    {
        printf("_________________________________\n");
        printf("currMemZone @ => %p\n", currMemZone);
        printf("currMemZone size %lu\n", currMemZone->zoneSize);
        // printf("currMemZone start address @ => %p\n", currMemZone->startZone);
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
