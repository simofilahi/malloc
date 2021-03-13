#include "../includes/malloc.h"

memZone ZONES[2];

void debugger(t_block **node)
{
    printf("address of started alloaction %p\n", *node);
}

t_block *createNewChunk(t_block *curr, size_t totalSize)
{
    size_t availabeSize;
    t_block *tmp;

    availabeSize = ZONES[0].size - totalSize;
    if (availabeSize > totalSize)
    {
        tmp = ZONES[0].startZone;
        tmp->used = true;
        tmp->size = totalSize;
        tmp->next = NULL;
        curr->next = tmp;
        ZONES[0].startZone += totalSize;
        ZONES[0].size -= totalSize;
        return tmp;
    }
    return NULL;
}

t_block *findChunk(size_t totalSize)
{
    t_block *curr;
    t_block *prev;

    curr = headNode;
    prev = curr;
    while (curr)
    {
        if (!curr->used && curr->size >= totalSize && (curr->used = 1))
            return curr;
        prev = curr;
        curr = curr->next;
    }
    return createNewChunk(prev, totalSize);
}

t_block *fillFirstChunk(size_t totalSize)
{
    if (!headNode)
    {
        headNode = ZONES[0].startZone;
        headNode->size = totalSize;
        headNode->used = true;
        headNode->next = NULL;
        ZONES[0].startZone += totalSize;
        ZONES[0].size -= totalSize;
        return headNode;
    }
    else
    {
        return findChunk(totalSize);
    }
}

t_block *reserveSpace(size_t size)
{
    size_t nodeSize;
    size_t totalSize;
    t_block *AlloChunk;

    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    AlloChunk = fillFirstChunk(totalSize);
    return AlloChunk;
}

void requestMemorySpace()
{
    int size;

    size = getpagesize() * 4;
    ZONES[0].startZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ZONES[0].size = size;
    printf("sizeof StartZone %lu\n", sizeof(ZONES[0].startZone[0]));
    printf("StartedMemoryAddress %p\n", ZONES[0].startZone);
    printf("size of allocated memory %lu\n", ZONES[0].size);
}

void *casting()
{
    t_block *current;

    current = headNode;
    while (current->next)
        current = current->next;
    return (void *)(current + 1);
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
    t_block *alloChunk;

    // dispaly_size_of_infos();
    printf("im here\n");
    if (!ZONES[0].size)
        requestMemorySpace();
    alloChunk = reserveSpace(size);
    show_alloc_mem();
    return (void *)(alloChunk + 1);
}
