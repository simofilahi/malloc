#include "../includes/malloc.h"

// CREATE AN EXTRA ZONE
void *createExtraZone(size_t totalSize)
{
    t_memZone *zone;

    zone = createNewZone(EXTRA_ZONE_PAGES, EXTRA_ZONE);
    return createNewBlockInZone(zone, totalSize);
}

// SEARCH FOR EXTRA ZONE THAT WILL HOLD AN ALLOCATION
void *getEmptyExtraZone(size_t totalSize)
{
    t_memZone *currZone;

    currZone = headZone;
    while (currZone)
    {
        if (currZone->zoneSize >= totalSize && currZone->type == EXTRA_ZONE)
            return createNewBlockInZone(currZone, totalSize);
        currZone = currZone->next;
    }
    return createExtraZone(totalSize);
}

// LOOK IN EXTRA ZONE IF THERE IS A FREE BLOCK
void *findFreeBlockInExtraZone(size_t totalSize)
{
    t_block *currBlock;
    t_memZone *currZone;

    currZone = headZone;

    while (currZone)
    {
        if (currZone->type == EXTRA_ZONE)
        {
            currBlock = currZone->headBlock;
            while (currBlock)
            {
                if (!currBlock->used && currBlock->blockSize >= totalSize && (currBlock->used = 1))
                    return currBlock;
                currBlock = currBlock->next;
            }
        }
        currZone = currZone->next;
    }
    return (getEmptyExtraZone(totalSize));
}