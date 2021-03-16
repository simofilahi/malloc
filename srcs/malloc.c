#include "../includes/malloc.h"

void debugger(t_memZone **node)
{
    printf("address of started alloaction %p\n", *node);
}

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

void createNewZone(size_t pages)
{
    size_t size;
    size_t zoneDataSize;
    t_memZone *newZone;

    size = getpagesize() * pages;
    zoneDataSize = sizeof(t_memZone);
    newZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    newZone->startZone = newZone + 1;
    newZone->size = size + zoneDataSize;
    newZone->next = NULL;
    addNewZoneToList(newZone);
}

t_block *fillFirstBlock(t_memZone *currMemZone, size_t totalSize)
{
    currMemZone->headBlock = currMemZone->startZone;
    currMemZone->headBlock->size = totalSize;
    currMemZone->headBlock->used = true;
    currMemZone->headBlock->next = NULL;
    currMemZone->tailBlock = currMemZone->headBlock;
    currMemZone->startZone += totalSize;
    currMemZone->size -= totalSize;
    return currMemZone->headBlock;
}

t_block *fillBlock(t_memZone *currMemZone, size_t totalSize)
{
    t_block *block;

    block = currMemZone->startZone;
    block->used = true;
    block->size = totalSize;
    block->next = NULL;
    currMemZone->tailBlock->next = block;
    currMemZone->tailBlock = currMemZone->tailBlock->next;
    currMemZone->startZone += totalSize;
    currMemZone->size -= totalSize;
    return block;
}

t_block *createNewBlock(size_t totalSize)
{
    t_memZone *currMemZone;

    currMemZone = headZone;
    while (currMemZone)
    {
        if (!currMemZone->headBlock)
            return fillFirstBlock(currMemZone, totalSize);
        else if (currMemZone->size >= totalSize)
            return fillBlock(currMemZone, totalSize);
        currMemZone = currMemZone->next;
    }
    createNewZone(8);
    return createNewBlock(totalSize);
}

t_block *findBlock(size_t totalSize)
{
    t_block *curr;
    t_memZone *memZoneCurr;

    memZoneCurr = headZone;
    while (memZoneCurr)
    {
        curr = memZoneCurr->headBlock;
        while (curr)
        {
            if (!curr->used && curr->size >= totalSize && (curr->used = 1))
                return curr;
            curr = curr->next;
        }

        memZoneCurr = memZoneCurr->next;
    }
    return createNewBlock(totalSize);
}

t_block *reserveSpace(size_t size)
{
    size_t nodeSize;
    size_t totalSize;
    t_block *block;

    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    block = findBlock(totalSize);
    return block;
}

void requestMemorySpace()
{
    createNewZone(10);
    createNewZone(20);
}

void dispaly_size_of_infos()
{
    printf("size_t    =>%lu\n", sizeof(size_t));
    printf("char      =>%lu\n", sizeof(char));
    printf("char *    =>%lu\n", sizeof(char *));
    printf("void      =>%lu\n", sizeof(void));
    printf("void *    =>%lu\n", sizeof(void *));
    printf("bool      =>%lu\n", sizeof(bool));
    printf("t_block   =>%lu\n", sizeof(t_block));
    printf("t_memZonw  =>%lu\n", sizeof(t_memZone));
}

void *malloc(size_t size)
{
    t_block *block;

    // dispaly_size_of_infos();
    if (!headZone)
        requestMemorySpace();
    block = reserveSpace(size);
    show_alloc_mem();
    return (void *)(block + 1);
}