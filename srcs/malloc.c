#include "../includes/malloc.h"

memZone ZONES[2];

void reserveSpace(t_block **headNode, size_t size)
{
    t_block *currentNode;
    size_t nodeSize;
    size_t availableSize;

    currentNode = NULL;
    nodeSize = sizeof(struct t_block *);
    availableSize = (ZONES[0].size + nodeSize);
    if (availableSize > size)
    {
        if (!(*headNode))
        {

            // *headNode = (*headNode) + (availableSize - size);
            ft_putendl("Hello I'M HERE");
            (*headNode)->alloSize = size;
            (*headNode)->next = NULL;
        }
        else
        {
            while (*headNode)
                *headNode = (*headNode)->next;
            currentNode = currentNode + (availableSize - size);
            currentNode->alloSize = size;
            currentNode->next = NULL;
            *headNode = currentNode;
        }
    }
}

void requestMemorySpace()
{
    int size;

    size = getpagesize() * 4;
    ZONES[0].startZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ZONES[0].size = size;
    printf("memorySpace %p\n", ZONES[0].startZone);
}

void show_alloc_mem(t_block **headNode)
{
    while (*headNode)
    {
        printf("size of allocation %zu\n", (*headNode)->alloSize);
        printf("address of started alloaction %p\n", *headNode);
        *headNode = (*headNode)->next;
    }
}

void *malloc(size_t size)
{
    static t_block *headNode;

    headNode = NULL;
    printf("size %zu\n", size);
    if (!ZONES[0].size)
        requestMemorySpace();
    reserveSpace(&headNode, size);
    show_alloc_mem(&headNode);
    return NULL;
}

// Heap : 10000 bytes
//     startZone = []

//     requested memory = 100bytes

// 1000