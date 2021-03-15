#include "../includes/malloc.h"

void show_alloc_mem()
{
    t_memZone *currMemZone;

    currMemZone = headZone;
    printf("currMemZone @ => %p\n", headZone);
    while (currMemZone)
    {
        ft_putendl("holla");
        printf("_________________________________\n");
        printf("currMemZone @ => %p\n", currMemZone);
        printf("currMemZone size %lu\n", currMemZone->size);
        printf("currMemZone start address @ => %p\n", currMemZone->startZone);
        printf("headBlock @ %p\n", currMemZone->headBlock);
        printf("tailBlock @ %p\n", currMemZone->tailBlock);
        printf("_________________________________\n");
        currMemZone = currMemZone->next;
    }
}
