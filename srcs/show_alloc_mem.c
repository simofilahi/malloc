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
        printf("currMemZone size %lu\n", currMemZone->size);
        printf("currMemZone start address @ => %p\n", currMemZone->startZone);
        t_block *curr;

        curr = currMemZone->headBlock;

        while (curr)
        {
            printf("++++++++++++++++++++++++++++\n");
            printf("curr->size %lu\n", curr->size);
            printf("curr->used %d\n", curr->used);
            printf("++++++++++++++++++++++++++++\n");
            curr = curr->next;
        }

        // printf("_________________________________\n");
        currMemZone = currMemZone->next;
    }
    ft_putendl("*******************\n");
}
