#include "../includes/malloc.h"

void show_alloc_mem()
{
    t_block *curr;

    curr = headNode;
    while (curr)
    {
        printf("HEADNODE @ => %p\n", curr);
        curr = curr->next;
    }
}
