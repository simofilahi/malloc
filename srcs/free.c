#include "../includes/malloc.h"

void free(void *ptr)
{
    t_block *curr;

    if (!ptr)
        return;
    else
    {
        ptr = (t_block *)ptr;
        ptr -= sizeof(t_block);
        printf("ptr @ => %p\n", ptr);
        printf("headNode @ => %p\n", headNode);
        printf("headNode->next @ => %p\n", headNode->next);
        curr = headNode;
        if (curr == ptr)
        {
            headNode = headNode->next;
            show_alloc_mem();
            return;
        }
        while (curr != ptr)
            curr = curr->next;
        curr->used = false;
        show_alloc_mem();
    }
}

// [[]->[] -> [] -> -> -> [] -> []]