#include "../includes/malloc.h"

// FREE A BLOCK
int freeBlock(t_memZone *zone, t_block *ptr)
{
    t_block *currBlock;
    t_block *prevBlock;

    currBlock = zone->headBlock;
    prevBlock = zone->headBlock;
    while (currBlock)
    {
        if (currBlock == ptr && !(currBlock->used = 0))
        {
            // mergeBlock(prevBlock, currBlock);
            // ft_putstr("free done successfully\n");
            // ft_putstr("here is ptr  before ft_bzero ");
            // ft_putstr((void *)ptr + 1);
            // ft_putchar('\n');
            // ft_bzero((void *)ptr + 1, currBlock->blockSize);
            // ft_putstr("here is ptr  ");
            // ft_putstr((void *)ptr + 1);
            // ft_putchar('\n');
            return (SUCCESS);
        }
        prevBlock = currBlock;
        currBlock = currBlock->next;
    }
    return (FAILED);
}

// FREE BY EXTRA ZONES
void freeByExtraZone(t_memZone *zone, t_block *ptr)
{

    while (zone)
    {
        if (zone->type == EXTRA_ZONE)
            freeBlock(zone, ptr);
        zone = zone->next;
    }
}

//  FREE BY PREALLOCATED ZONES
void freeByZone(t_memZone *zone, t_block *ptr)
{
    // ft_putstr("ptr size \n");
    // ft_putnbr(ptr->blockSize);
    if (!freeBlock(zone, ptr))
        return;
    freeByExtraZone(zone, ptr);
}

// CALL MUNMAP TO DEALLOCATE AN ZONE
int deallocateZone(t_block *ptr, t_memZone *currZone, t_memZone *prevZone)
{
    t_memZone *nextZone;
    if (currZone && ptr == currZone->headBlock && currZone->type == LARGE_ZONE)
    {
        // ft_putstr("large zone \n");
        nextZone = currZone->next;
        if (!(munmap(currZone, currZone->zoneSize + sizeof(t_memZone) + ptr->blockSize)))
        {
            // ft_putstr("mnumap succes\n");
            prevZone->next = nextZone;
            return (SUCCESS);
        }
    }
    return (FAILED);
}

// FREE BY LARGES ZONES
void freeByLargeZone(t_block *ptr)
{
    t_memZone *currZone;
    t_memZone *prevZone;

    currZone = headZone;
    while (currZone && (currZone->type != LARGE_ZONE))
    {
        prevZone = currZone;
        currZone = currZone->next;
    }
    while (currZone)
    {
        if (!deallocateZone(ptr, currZone, prevZone))
            return;
        prevZone = currZone;
        currZone = currZone->next;
    }
    deallocateZone(ptr, currZone, prevZone);
}

void findBlock_debugger(t_block *ptr)
{
    t_memZone *currZone;
    t_block *currBlock;
    t_memZone *prevZone;

    currZone = headZone;
    currZone = headZone;
    while (currZone)
    {
        currBlock = currZone->headBlock;
        while (currBlock)
        {
            if (ptr == currBlock)
            {
                if (currZone->type == LARGE_ZONE)
                    deallocateZone(ptr, currZone, prevZone);
                else
                    freeByZone(currZone, ptr);
            }
            currBlock = currBlock->next;
        }
        prevZone = currZone;
        currZone = currZone->next;
    }
}

//  FREE AN ALLOCATED MEMORY BLOCK
void free(void *ptr)
{
    t_memZone *tinyZone;
    t_memZone *smallZone;
    // t_block *curr;

    // ft_putstr("free\n");
    // min_printf("free incoming address ", ptr, 1);
    // ft_putstr("here is ptr in the begin ");
    // ft_putstr(ptr);
    // ft_putchar('\n');
    // pthread_mutex_lock(&lock);
    if (!ptr)
        return;
    tinyZone = headZone;
    smallZone = headZone->next;
    ptr = (t_block *)ptr;
    // min_printf("ptr @ ", ptr, 1);
    ptr -= 1;
    // min_printf("curr @ ", curr, 1);
    // printf("blockSize %lu\n", curr->blockSize);
    // ft_putchar('\n');
    // // ft_putnbr((long)curr->mergedCount);
    // // ft_putchar('\n');
    // if (curr && curr->blockSize > 0 && curr->blockSize <= MAX_TINY_ZONE_SIZE)
    //     freeByZone(tinyZone, curr);
    // else if (curr && curr->blockSize > 0 && curr->blockSize <= MAX_SMALL_ZONE_SIZE)
    //     freeByZone(smallZone, curr);
    // else if (curr && curr->blockSize > 0)
    //     freeByLargeZone(curr);
    findBlock_debugger(ptr);
    // / pthread_mutex_unlock(&lock);
}