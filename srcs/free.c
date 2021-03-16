#include "../includes/malloc.h"

void free(void *ptr)
{
    t_block *curr;
    t_memZone *memZoneCurr;

    memZoneCurr = headZone;
    ptr = (t_block *)ptr;
    ptr -= sizeof(t_block);
    while (memZoneCurr)
    {
        curr = memZoneCurr->headBlock;
        while (curr)
        {
            if (curr == ptr)
            {
                curr->used = 0;
                show_alloc_mem();
                return;
            }
            curr = curr->next;
        }
        memZoneCurr = memZoneCurr->next;
    }
}