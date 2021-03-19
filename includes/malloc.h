#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../libft/libft.h"

// REMOVE THIS LATER
#include <stdio.h>

#define MAX_TINY_ZONE_SIZE 255
#define MAX_SMALL_ZONE_SIZE 4092

#define TINY_ZONE_PAGES 10
#define SAMLL_ZONE_PAGES 120
#define EXTRA_ZONE_PAGES 200

#define TINY_ZONE 1
#define SMALL_ZONE 2
#define LARGE_ZONE 3
#define EXTRA_ZONE 4

#define SUCCESS 0
#define FAILED 1

typedef struct s_block
{
    size_t blockSize;
    void *next;
    bool used;
} t_block;

typedef struct s_memZone
{
    void *startZone;
    void *next;
    size_t zoneSize;
    size_t type;
    t_block *headBlock;
    t_block *tailBlock;
} t_memZone;

t_memZone *headZone;

// FREE FUNCTIONS;
void free(void *ptr);

// REALLOC FUNCTIONS
void *realloc(void *ptr, size_t size);

// MALLOC FUNCTIONS
void *malloc(size_t size);
void *createExtraZone(size_t totalSize);
void *findFreeBlockInExtraZone(size_t totalSize);
void *createNewZone(size_t pages, size_t type);
void *fillFirstBlock(t_memZone *zone, size_t totalSize);
void *fillBlock(t_memZone *zone, size_t totalSize);
void *createNewBlockInZone(t_memZone *zone, size_t totalSize);

// ALLOCATION STATE VISUALISATION
void show_alloc_mem();
void show_alloc_mem_ex();

// PRINT FUNCTIONS
void min_printf(void *str, void *ptr, int nflag);

// DEBUGG
void debugger();
