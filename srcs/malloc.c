#include "../includes/malloc.h"

memZone ZONES[2];

void debugger(t_block **node)
{
    // printf("size of allocation %zu\n", (*node)->alloSize);
    printf("address of started alloaction %p\n", *node);
}

// void printfHelper(char *str)
// {
//     printf("%s\n", str);
// }

// size_t CalculateAvailabelSize()
// {
// }

t_block *createNewChunk(t_block *curr, size_t totalSize)
{
    size_t availabeSize;
    t_block *tmp;

    availabeSize = ZONES[0].size - totalSize;
    printf("ZONE @ adress %p\n", ZONES[0].startZone);
    if (availabeSize > totalSize)
    {
        tmp = ZONES[0].startZone;
        tmp->next = NULL;
        curr->next = tmp;
        return tmp;
    }
    return NULL;
}

t_block *findChunk(size_t alloSize)
{
    t_block *curr;
    curr = headNode;

    while (curr->next)
    {
        if (!curr->used && curr->size >= alloSize)
            return curr;
        curr = curr->next;
    }
    return createNewChunk(curr, alloSize);
}

void fillFirstChunk(size_t alloSize)
{
    if (!headNode)
    {
        headNode = ZONES[0].startZone;
        headNode->size = alloSize;
        headNode->used = true;
        headNode->next = NULL;
    }
}

void reserveSpace(size_t size)
{
    size_t nodeSize;
    size_t totalSize;

    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    fillFirstChunk(totalSize);
    findChunk(totalSize);
    ZONES[0].startZone += totalSize;
    ZONES[0].size -= totalSize;
}

void requestMemorySpace()
{
    int size;

    size = getpagesize() * 4;
    ZONES[0].startZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ZONES[0].size = size;
    // printf("sizeof StartZone %lu\n", sizeof(ZONES[0].startZone[0]));
    // printf("StartedMemoryAddress %p\n", ZONES[0].startZone);
    // printf("size of allocated memory %lu\n", ZONES[0].size);
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
    printf("t_block   =>%lu\n", sizeof(t_block));
    printf("t_block * =>%lu\n", sizeof(t_block *));
}

void *malloc(size_t size)
{
    // dispaly_size_of_infos();
    if (!ZONES[0].size)
        requestMemorySpace();
    reserveSpace(size);
    // show_alloc_mem(&headNode);
    show_alloc_mem();
    return casting();
}
