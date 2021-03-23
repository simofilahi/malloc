#include "../includes/malloc.h"

size_t align(size_t size)
{
    while (size % 8)
        size++;
    return size;
}