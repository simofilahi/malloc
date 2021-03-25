#include "../includes/malloc.h"

// LOOK FOR A BLOCK IF EXIST IN A ZONE
static t_block *findBlock(t_block *ptr)
{
    t_memZone *currZone;
    t_block *currBlock;

    currZone = headZone;
    while (currZone)
    {
        currBlock = currZone->headBlock;
        while (currBlock)
        {
            if (ptr == currBlock)
                return currBlock;
            currBlock = currBlock->next;
        }
        currZone = currZone->next;
    }
    return NULL;
}

// REALLOC HELPER
void *realloc_helper(void *ptr, size_t size)
{
    void *block;
    t_block *targetedBlock;
    size_t len;

    block = NULL;
    if (!ptr)
        return malloc(size);
    if ((targetedBlock = findBlock((t_block *)ptr - 1)))
    {
        if (targetedBlock->blockSize > size)
            len = size;
        else
            len = targetedBlock->blockSize;
        if (!(block = (malloc(size))))
            return block;
        ft_memcpy(block, ptr, len);
        free(ptr);
    }
    return block;
}

// REALLOC AN ALLOCATION
void *realloc(void *ptr, size_t size)
{
    void *block;

    pthread_mutex_lock(&lock);
    block = realloc_helper(ptr, size);
    pthread_mutex_unlock(&lock);
    return (block);
}