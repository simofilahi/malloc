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

// // SPLIT MERGED BLOCKS
void *splitMergedBlocks(t_block *block, size_t totalSize)
{
    t_block *newBlock;

    newBlock = NULL;
    if (block->blockSize > totalSize)
    {
        newBlock = block + (block->blockSize - totalSize);
        newBlock->blockSize = block->blockSize - totalSize;
        newBlock->used = 0;
        if (block->mergedCount > 0)
            newBlock->mergedCount = block->mergedCount - 1;
        newBlock->next = block->next;
        block->mergedCount = 0;
        block->blockSize = totalSize;
        block->used = 1;
        block->next = newBlock;
    }
    return block;
}

// CREATE NEW BLOCK IN A ZONE
void *createNewBlockInZone(t_memZone *zone, size_t totalSize)
{
    if (zone->zoneSize > (totalSize + 1))
    {
        if (!zone->headBlock)
            return fillFirstBlock(zone, totalSize);
        else
            return fillBlock(zone, totalSize);
    }
    else
        return findFreeBlockInExtraZone(totalSize);
    return NULL;
}