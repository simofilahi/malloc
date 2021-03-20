#include "../includes/malloc.h"

//  ADD NEW MEMORY ZONE TO LIST
void addNewZoneToList(t_memZone *newZone)
{
    t_memZone *curr;

    if (!headZone)
        headZone = newZone;
    else
    {
        curr = headZone;
        while (curr->next)
            curr = curr->next;
        curr->next = newZone;
    }
}

// REQUEST FROM OS NEW MEMORY ZONE
void *createNewZone(size_t pages, size_t type)
{
    size_t size;
    t_memZone *newZone;

    size = getpagesize() * pages;
    newZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    newZone->startZone = newZone + 1;
    newZone->zoneSize = size - sizeof(t_memZone);
    newZone->type = type;
    newZone->next = NULL;
    addNewZoneToList(newZone);
    return newZone;
}

// FILL THE FIRST ALLOCATION BLOCK IN A ZONE
void *fillFirstBlock(t_memZone *zone, size_t totalSize)
{
    zone->headBlock = zone->startZone;
    zone->headBlock->blockSize = totalSize;
    zone->headBlock->used = true;
    zone->headBlock->next = NULL;
    zone->tailBlock = zone->headBlock;
    zone->startZone += totalSize;
    if (!(zone->type == LARGE_ZONE))
        zone->zoneSize -= totalSize;
    return zone->headBlock;
}

// FILL AN ALLOCATION BLOCK
void *fillBlock(t_memZone *zone, size_t totalSize)
{
    t_block *block;

    if (zone->zoneSize >= totalSize)
    {
        block = zone->startZone;
        block->blockSize = totalSize;
        block->used = true;
        block->next = NULL;
        zone->tailBlock->next = block;
        zone->tailBlock = zone->tailBlock->next;
        zone->startZone += totalSize;
        zone->zoneSize -= totalSize;
        return block;
    }
    else
        return findFreeBlockInExtraZone(totalSize);
    return NULL;
}

// CREATE NEW BLOCK IN A ZONE
void *createNewBlockInZone(t_memZone *zone, size_t totalSize)
{
    if (!zone->headBlock)
        return fillFirstBlock(zone, totalSize);
    else
        return fillBlock(zone, totalSize);
    return NULL;
}

// // SPLIT MERGED BLOCKS
void *splitMergedBlocks(t_block *block, size_t totalSize)
{
    t_block *newBlock;
    t_block *tmp;

    if (block->blockSize > totalSize)
    {
        newBlock = block + totalSize;
        newBlock->blockSize = block->blockSize - totalSize;
        newBlock->used = 0;
        block->blockSize = block->blockSize - totalSize;
        tmp = block->next;
        block->next = newBlock;
        newBlock->next = tmp;
    }
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

// CREATE LARGE ZONE
void *createLargeZone(size_t totalSize)
{
    t_memZone *zone;
    size_t pages;
    size_t zoneDataSize;

    zoneDataSize = sizeof(t_memZone);
    totalSize += zoneDataSize;
    pages = (totalSize / (size_t)getpagesize()) + 1;
    zone = createNewZone(pages, LARGE_ZONE);
    return (createNewBlockInZone(zone, totalSize));
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

// REQUEST TWO PREALLOCATED ZONES IN THE BEGINNING OF PROGRAM
void preallocateZones()
{
    createNewZone(TINY_ZONE_PAGES, TINY_ZONE);
    createNewZone(SAMLL_ZONE_PAGES, SMALL_ZONE);
}

void *malloc(size_t size)
{
    t_block *block;
    size_t nodeSize;
    size_t totalSize;

    pthread_mutex_lock(&lock);
    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    if (!headZone)
        preallocateZones();
    if (size == 0)
        return NULL;
    block = requestBlock(totalSize);
    pthread_mutex_unlock(&lock);
    return (void *)(block + 1);
}