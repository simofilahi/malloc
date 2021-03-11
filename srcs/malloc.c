#include "../includes/malloc.h"

memZone ZONES[2];
t_block *headNode;

t_block head;

void debugger(t_block **node)
{
    printf("size of allocation %zu\n", (*node)->alloSize);
    printf("address of started alloaction %p\n", *node);
}

void printfHelper(char *str)
{
    printf("%s\n", str);
}

// size_t CalculateAvailabelSize()
// {
// }

void reserveSpace(t_block **headNode, size_t size)
{
    t_block *currentNode;
    size_t nodeSize;
    size_t availableSize;
    size_t totalSize;

    currentNode = NULL;
    nodeSize = sizeof(t_block);
    totalSize = nodeSize + size;
    availableSize = (ZONES[0].size - totalSize);
    if (availableSize > size)
    {
        // printf("remain size %lu\n", ZONES[0].size);
        if (!(*headNode))
        {
            // printfHelper("INSIDE THE IF CONDITION");
            (*headNode) = ZONES[0].startZone + availableSize;
            (*headNode)->alloSize = totalSize;
            (*headNode)->next = NULL;
            debugger(&(*headNode));
        }
        else
        {
            // printf("INSIDE THE ELSE CONDITION");
            while ((*headNode)->next)
                (*headNode) = (*headNode)->next;
            currentNode = ZONES[0].startZone + availableSize;
            currentNode->alloSize = size;
            currentNode->next = NULL;
            (*headNode)->next = currentNode;
        }
        ZONES[0].size = availableSize;
    }
}

// availableSize = 1000bytes;
// NodeSize = 8bytes;
// allocationSize = 11bytes;
// startZoneAddress = x0;

// totalSize = 19bytes

// newAddress = x981

//     startZoneAddress-> 0x[                     next<-newAddress-> x981[ 8bytes->{} | [   ] ]]

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

void show_alloc_mem(t_block **headNode)
{
    t_block *current;

    current = *headNode;
    while (current)
    {
        // printf("size of allocation %zu\n", current->alloSize);
        // printf("address of started alloaction %p\n", current);
        current = current->next;
    }
}

void *casting(t_block **headNode)
{
    t_block *current;

    current = *headNode;
    while ((*headNode)->next)
        (*headNode) = (*headNode)->next;
    printf("address before add 1 %p\n", (*headNode));
    printf("address after add 1 %p\n", (*headNode + 1));
    return (*headNode + 1);
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
    reserveSpace(&headNode, size);
    // show_alloc_mem(&headNode);
    return casting(&headNode);
}
