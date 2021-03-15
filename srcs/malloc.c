#include "../includes/malloc.h"

void debugger(t_memZone **node)
{
    printf("address of started alloaction %p\n", *node);
}

void addNewZoneToList(t_memZone *newZone)
{
    t_memZone *curr;

    if (!headZone)
    {

        headZone = newZone;
    }

    else
    {
        curr = headZone;
        debugger(&curr);
        while (curr->next)
            curr = curr->next;
        curr->next = newZone;
    }
}

void createNewZone(size_t pages)
{
    size_t size;
    t_memZone *newZone;

    size = getpagesize() * pages;
    newZone = (t_memZone *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    newZone->startZone = newZone + sizeof(t_memZone);
    newZone->size = size;
    newZone->next = NULL;
    addNewZoneToList(newZone);
}

t_block *createNewBlock(size_t totalSize)
{
    size_t availabeSize;
    t_block *tmp;
    t_block *currBlock;
    t_memZone *currMemZone;

    currMemZone = headZone;
    while (currMemZone)
    {
        currBlock = currMemZone->headBlock;
        availabeSize = currMemZone->size - totalSize;
        if (!currBlock)
        {
            currBlock = currMemZone->startZone;
            currBlock->size = totalSize;
            currBlock->used = true;
            currBlock->next = NULL;
            currMemZone->tailBlock = currMemZone->headBlock;
            currMemZone->startZone += totalSize;
            currMemZone->size -= totalSize;
            return currBlock;
        }
        else
        {
            if (availabeSize > totalSize)
            {
                tmp = currMemZone->startZone;
                tmp->used = true;
                tmp->size = totalSize;
                tmp->next = NULL;
                currMemZone->tailBlock->next = tmp;
                currMemZone->tailBlock = currMemZone->tailBlock->next;
                currMemZone->startZone += totalSize;
                currMemZone->size -= totalSize;
                return tmp;
            }
        }
        currMemZone = currMemZone->next;
    }
    return NULL;
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
    createNewZone(4);
    createNewZone(8);
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
    printf("t_block * =>%lu\n", sizeof(t_block *));
}

void *malloc(size_t size)
{
    t_block *block;
    t_memZone *headZone;

    headZone = NULL;
    if (!headZone)
        requestMemorySpace();
    block = reserveSpace(size);
    show_alloc_mem();
    return (void *)(block + 1);
}