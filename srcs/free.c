#include "../includes/malloc.h"

//  FREE BY SIMPLE ZONES
void freeByZone(t_memZone *zone, t_block *ptr)
{
    t_block *currBlock;
    t_block *prev;

    currBlock = zone->headBlock;
    while (currBlock)
    {
        if (currBlock == ptr && !(currBlock->used = 0))
            return;
        prev = currBlock;
        currBlock = currBlock->next;
    }
}

// FREE BY LARGES ZONES
void freeByLargeZone(t_block *ptr)
{
    t_memZone *currZone;
    t_memZone *prevZone;
    t_memZone *tmp;

    currZone = headZone->next;
    currZone = currZone->next;
    prevZone = currZone;
    while (currZone)
    {
        if (ptr == currZone->headBlock)
        {
            tmp = currZone->next;
            if (!(munmap(currZone, currZone->zoneSize)))
            {
                prevZone->next = tmp;
                return;
            }
        }
        prevZone = currZone;
        currZone = currZone->next;
    }
}

void free(void *ptr)
{
    t_memZone *tinyZone;
    t_memZone *smallZone;
    t_block *curr;

    if (!ptr)
        return;
    tinyZone = headZone;
    smallZone = headZone->next;
    curr = (t_block *)ptr - 1;
    if (curr->blockSize <= MAX_TINY_ZONE_SIZE)
        freeByZone(tinyZone, curr);
    else if (curr->blockSize <= MAX_SMALL_ZONE_SIZE)
        freeByZone(smallZone, curr);
    else
        freeByLargeZone(curr);
}