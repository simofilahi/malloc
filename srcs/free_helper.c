#include "../includes/malloc.h"

// MERGE TWO FREE BLOCK
void mergeBlock(t_block *prevBlock, t_block *currBlock)
{
    if ((prevBlock != currBlock) &&
        (!prevBlock->used && !currBlock->used))
    {
        prevBlock->blockSize += currBlock->blockSize;
        prevBlock->next = currBlock->next;
        prevBlock->mergedCount++;
    }
}
