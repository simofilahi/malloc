#include "../includes/malloc.h"

// void clean_exit_on_sig(int sig_num)
// {
//     printf("\n Signal %d received", sig_num);
// }

// FILL THE FIRST ALLOCATION BLOCK IN A ZONE
void *fillFirstBlock(t_memZone *zone, size_t totalSize)
{
    zone->headBlock = zone->startZone;
    zone->zoneSize -= (totalSize);
    // ft_putstr("zone->zoneSize ");
    // ft_putnbr(zone->zoneSize % 8);
    // ft_putchar('\n');
    zone->startZone += (totalSize + 8);
    zone->headBlock->blockSize = totalSize;
    zone->headBlock->used = 1;
    zone->headBlock->mergedCount = 0;
    zone->headBlock->next = NULL;
    zone->tailBlock = zone->headBlock;
    return zone->headBlock;
}

// FILL AN ALLOCATION BLOCK
void *fillBlock(t_memZone *zone, size_t totalSize)
{
    t_block *block;

    block = zone->startZone;
    zone->zoneSize -= (totalSize);
    // ft_putstr("zone->zoneSize ");
    // ft_putnbr(zone->zoneSize % 8);
    // ft_putchar('\n');
    zone->startZone += (totalSize + 8);
    block->blockSize = totalSize;
    block->used = 1;
    block->mergedCount = 0;
    block->next = NULL;
    zone->tailBlock->next = block;
    zone->tailBlock = zone->tailBlock->next;
    return block;
}

// [    |  ]

// FIND FREE BLOCK IN A ZONE
void *findFreeBlockInZone(t_memZone *zone, size_t totalSize)
{
    t_block *currBlock;

    currBlock = zone->headBlock;
    while (currBlock)
    {
        if (!currBlock->used && currBlock->blockSize >= totalSize && (currBlock->used = 1))
        {
            // return splitMergedBlocks(currBlock, totalSize);
            return currBlock;
        }

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

    // ft_putstr("malloc\n");
    // ft_putstr("size ==> ");
    // ft_putnbr((long)size);
    // ft_putchar('\n');
    // pthread_mutex_lock(&lock);
    // ft_putstr("malloc started \n");
    nodeSize = sizeof(t_block);
    totalSize = size + nodeSize;
    // ft_putstr("totalSize 1");
    // ft_putnbr(totalSize);
    // ft_putchar('\n');
    // totalSize = align(totalSize);
    ft_putstr("totalSize % ");
    ft_putnbr(totalSize % 8);
    ft_putchar('\n');
    if (!headZone)
    {
        createNewZone(TINY_ZONE_PAGES, TINY_ZONE);
        createNewZone(SAMLL_ZONE_PAGES, SMALL_ZONE);
    }
    if (size == 0)
        return NULL;
    if (!(block = createLargeZone(totalSize)))
        return NULL;
    // show_alloc_mem_ex();
    // pthread_mutex_unlock(&lock);
    // ft_putnbr((((t_block *)block) + 1) - (void *)block);
    block = ((t_block *)block) + 8;
    // printf("block @ %p\n", block);'
    min_printf("malloc returned address ", block, 1);
    return (void *)(block);
}