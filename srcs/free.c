#include "../includes/malloc.h"

void free(void *ptr)
{
    ptr = NULL;
    // t_block *curr;

    // if (!ptr)
    //     return;
    // else
    // {
    //     ptr = (t_block *)ptr;
    //     ptr -= sizeof(t_block);
    //     curr = headNode;
    //     while (curr != ptr)
    //         curr = curr->next;
    //     curr->used = false;
    //     show_alloc_mem();
    // }
}

// [[]->[] -> [] -> -> -> [] -> []]