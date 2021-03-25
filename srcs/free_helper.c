#include "../includes/malloc.h"

// MERGE TWO FREE BLOCK
void mergeBlock(t_block *currBlock, t_block *prevBlock)
{
    if ((prevBlock != currBlock) &&
        (!prevBlock->used && !currBlock->used))
    {
        prevBlock->blockSize += currBlock->blockSize;
        prevBlock->next = currBlock->next;
        prevBlock->mergedCount++;
    }
}
