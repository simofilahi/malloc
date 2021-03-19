#include "../includes/malloc.h"

// MERGE TWO FREE BLOCK
void mergeBlock(t_block *prevBlock, t_block *currBlock)
{
    if ((prevBlock != currBlock) &&
        (!prevBlock->used && !currBlock->used))
    {
        printf("prevBlock->blockSize %lu\n", prevBlock->blockSize);
        printf("currBlock->blockSize %lu\n", currBlock->blockSize);
        prevBlock->blockSize += currBlock->blockSize;
        prevBlock->next = currBlock->next;
    }
}

// FREE A BLOCK
int freeBlock(t_memZone *zone, t_block *ptr)
{
    t_block *currBlock;
    t_block *prevBlock;

    currBlock = zone->headBlock;
    prevBlock = zone->headBlock;
    while (currBlock)
    {
        if (currBlock == ptr && !(currBlock->used = 0))
        {
            mergeBlock(prevBlock, currBlock);
            return (SUCCESS);
        }
        prevBlock = currBlock;
        currBlock = currBlock->next;
    }
    return (FAILED);
}

// FREE BY EXTRA ZONES
void freeByExtraZone(t_memZone *zone, t_block *ptr)
{

    while (zone)
    {
        if (zone->type == EXTRA_ZONE)
            freeBlock(zone, ptr);
        zone = zone->next;
    }
}

//  FREE BY PREALLOCATED ZONES
void freeByZone(t_memZone *zone, t_block *ptr)
{
    if (!freeBlock(zone, ptr))
        return;
    freeByExtraZone(zone, ptr);
}

// CALL MUNMAP TO DEALLOCATE AN ZONE
int deallocateZone(t_block *ptr, t_memZone *currZone, t_memZone *prevZone)
{
    t_memZone *nextZone;

    if (ptr == currZone->headBlock && currZone->type == LARGE_ZONE)
    {
        nextZone = currZone->next;
        if (!(munmap(currZone, currZone->zoneSize + sizeof(t_memZone))))
        {
            prevZone->next = nextZone;
            return (SUCCESS);
        }
    }
    return (FAILED);
}

// FREE BY LARGES ZONES
void freeByLargeZone(t_block *ptr)
{
    t_memZone *currZone;
    t_memZone *prevZone;

    currZone = headZone;
    while (currZone && (currZone->type != LARGE_ZONE))
    {
        prevZone = currZone;
        currZone = currZone->next;
    }
    while (currZone)
    {
        if (!deallocateZone(ptr, currZone, prevZone))
            return;
        prevZone = currZone;
        currZone = currZone->next;
    }
    deallocateZone(ptr, currZone, prevZone);
}

//  FREE AN ALLOCATED MEMORY BLOCK
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