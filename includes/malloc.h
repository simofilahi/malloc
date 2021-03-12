#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../libft/libft.h"

// REMOVE THIS LATER
#include <stdio.h>

typedef struct s_block
{
    size_t size;
    bool used;
    void *next;
} t_block;

t_block *headNode;

typedef struct
{
    void *startZone;
    size_t size;
} memZone;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();