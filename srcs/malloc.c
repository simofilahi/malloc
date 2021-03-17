#include "../includes/malloc.h"

void debugger(t_memZone **node)
{
    printf("address of started alloaction %p\n", *node);
}

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
    newZone->zoneSize = size;
    newZone->type = type;
    newZone->next = NULL;
    addNewZoneToList(newZone);
    return newZone;
}

// FILL THE FIRST ALLOCATION BLOCK FROM A ZONE
void *fillFirstBlock(t_memZone *zone, size_t totalSize)
{
    // ft_putendl("I'M HERE");
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

void *createExtraZone(size_t totalSize)
{
    t_memZone *zone;

    zone = createNewZone(EXTRA_ZONE_PAGES, EXTRA_ZONE);
    if (zone->headBlock)
        return fillFirstBlock(zone, totalSize);
    else if (zone->zoneSize >= totalSize)
        return fillBlock(zone, totalSize);
}

// CREATE NEW BLOCK IN A ZONE
void *createNewBlockInZone(t_memZone *zone, size_t totalSize)
{
    if (!zone->headBlock)
        return fillFirstBlock(zone, totalSize);
    else if (zone->zoneSize >= totalSize)
        return fillBlock(zone, totalSize);
    return createExtraZone(totalSize);
}

// FIND FREE BLOCK IN A ZONE
void *findFreeBlockInZone(t_memZone *zone, size_t totalSize)
{
    t_block *headBlock;

    headBlock = zone->headBlock;
    while (headBlock)
    {
        if (!headBlock->used && headBlock->blockSize >= totalSize && (headBlock->used = 1))
            return headBlock;
        headBlock = headBlock->next;
    }
    return createNewBlockInZone(zone, totalSize);
}

// LOOK IN EXTRA ZONE IF THERE IS A FREE BLOCK
void *findFreeBlockInExtraZone(size_t totalSize)
{
    t_memZone *currZone;
    t_block *currBlock;

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
    }
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
    t_block *block = createNewBlockInZone(zone, totalSize);
    return block;
}

// LOOKING FOR A FREE ALLOCATION BLOCK WITHIN PREALLOCATED ZONES
void *findFreeBlock(size_t totalSize)
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
}

// RESERVE AN ALLOCATION BLOCK
void *reserveBlock(size_t totalSize)
{
    t_block *block;

    block = findFreeBlock(totalSize);
    return block;
}

// REQUEST TWO PREALLOCATED ZONES IN THE BEGINNING OF PROGRAM
void preallocateZones()
{
    createNewZone(TINY_ZONE_PAGES, TINY_ZONE);
    createNewZone(SAMLL_ZONE_PAGES, SMALL_ZONE);
}

// void dispaly_size_of_infos()
// {
//     printf("size_t    =>%lu\n", sizeof(size_t));
//     printf("char      =>%lu\n", sizeof(char));
//     printf("char *    =>%lu\n", sizeof(char *));
//     printf("void      =>%lu\n", sizeof(void));
//     printf("void *    =>%lu\n", sizeof(void *));
//     printf("bool      =>%lu\n", sizeof(bool));
//     printf("t_block   =>%lu\n", sizeof(t_block));
//     printf("t_memZonw  =>%lu\n", sizeof(t_memZone));
// }

void *malloc(size_t size)
{
    t_block *block;
    size_t nodeSize;
    size_t totalSize;

    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    if (!headZone)
        preallocateZones();
    if (size == 0)
        return NULL;
    block = reserveBlock(totalSize);
    // show_alloc_mem();
    return (void *)(block + 1);
}