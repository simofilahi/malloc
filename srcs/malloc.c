#include "../includes/malloc.h"

// FILL THE FIRST ALLOCATION BLOCK IN A ZONE
void *fillFirstBlock(t_memZone *zone, size_t totalSize)
{
    zone->headBlock = zone->startZone;
    zone->headBlock->blockSize = totalSize;
    zone->headBlock->used = true;
    zone->headBlock->mergedCount = 0;
    zone->headBlock->next = NULL;
    zone->tailBlock = zone->headBlock;
    zone->zoneSize -= totalSize;
    if (zone->zoneSize > totalSize)
        zone->startZone += totalSize;
    return zone->headBlock;
}

// FILL AN ALLOCATION BLOCK
void *fillBlock(t_memZone *zone, size_t totalSize)
{
    t_block *block;

    block = zone->startZone;
    block->blockSize = totalSize;
    block->used = true;
    block->mergedCount = 0;
    block->next = NULL;
    zone->tailBlock->next = block;
    zone->tailBlock = zone->tailBlock->next;
    zone->zoneSize -= totalSize;
    if (zone->zoneSize > totalSize)
        zone->startZone += totalSize;
    return block;
}

// FIND FREE BLOCK IN A ZONE
void *findFreeBlockInZone(t_memZone *zone, size_t totalSize)
{
    t_block *currBlock;

    currBlock = zone->headBlock;
    while (currBlock)
    {
        if (!currBlock->used && currBlock->blockSize >= totalSize && (currBlock->used = 1))
            return splitMergedBlocks(currBlock, totalSize);
        currBlock = currBlock->next;
    }
    return createNewBlockInZone(zone, totalSize);
}

// RESERVE AN ALLOCATION BLOCK
void *requestBlock(size_t totalSize)
{
    t_memZone *tinyZone;
    t_memZone *smallZone;

    tinyZone = headZone;
    smallZone = headZone->next;
    if (totalSize <= MAX_TINY_ZONE_SIZE)
        return findFreeBlockInZone(tinyZone, totalSize);
    else if (totalSize <= MAX_SMALL_ZONE_SIZE)
        return findFreeBlockInZone(smallZone, totalSize);
    else
        return createLargeZone(totalSize);
    return NULL;
}

// ALLOCATE A BLOCK OF MEMORY
void *malloc(size_t size)
{
    t_block *block;
    size_t nodeSize;
    size_t totalSize;

    pthread_mutex_lock(&lock);
    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    if (!headZone)
    {
        createNewZone(TINY_ZONE_PAGES, TINY_ZONE);
        createNewZone(SAMLL_ZONE_PAGES, SMALL_ZONE);
    }
    if (!size)
        return NULL;
    if (!(block = requestBlock(totalSize)))
        return NULL;
    pthread_mutex_unlock(&lock);
    return (void *)((t_block *)block + 1);
}