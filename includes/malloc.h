#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

// REMOVE THIS LATER
#include <stdio.h>

// MAX SIZE OF AN ALLOCATION IN A ZONE
#define MAX_TINY_ZONE_SIZE 255
#define MAX_SMALL_ZONE_SIZE 2000

// MMAP PAGES
#define TINY_ZONE_PAGES 10
#define SAMLL_ZONE_PAGES 100
#define EXTRA_ZONE_PAGES 100

// DEFINITION OF ZONES
#define TINY_ZONE 1
#define SMALL_ZONE 2
#define LARGE_ZONE 3
#define EXTRA_ZONE 4

#define SUCCESS 0
#define FAILED 1

// THREAD SAFE GLOBAL VARIABLE
pthread_mutex_t lock;

// BLOCK STRUCTURE
typedef struct s_block
{
    size_t blockSize;
    struct s_block *next;
    int used;
    int mergedCount;
} t_block;

// ZONE STRUCTURE
typedef struct s_memZone
{
    void *startZone;
    struct s_memZone *next;
    size_t zoneSize;
    size_t type;
    t_block *headBlock;
    t_block *tailBlock;
} t_memZone;

// FIRST ZONE
t_memZone *headZone;

// MEMORY ZONES
void *createNewZone(size_t pages, size_t type);
void addNewZoneToList(t_memZone *newZone);
void *createLargeZone(size_t totalSize);
void *createExtraZone(size_t totalSize);

// FREE FUNCTIONS;
void free(void *ptr);
void mergeBlock(t_block *prevBlock, t_block *currBlock);

// REALLOC FUNCTIONS
void *realloc(void *ptr, size_t size);

// REALLOCF FUNCTIONS
void *reallocf(void *ptr, size_t size);

// CALLOC FUNCTIONS
void *calloc(size_t count, size_t size);

// MALLOC FUNCTIONS
void *malloc(size_t size);
void *findFreeBlockInExtraZone(size_t totalSize);
void *fillFirstBlock(t_memZone *zone, size_t totalSize);
void *fillBlock(t_memZone *zone, size_t totalSize);
void *createNewBlockInZone(t_memZone *zone, size_t totalSize);
void *splitMergedBlocks(t_block *block, size_t totalSize);
void *createNewBlockInZone(t_memZone *zone, size_t totalSize);

// ALLOCATION VISUALISATION
void show_alloc_mem();
void show_alloc_mem_ex();

// PRINT FUNCTIONS
void min_printf(void *str, void *ptr, int nflag);

// UTILIS
void calculateBlockSize(t_block *curr, size_t *blockSize);

// LIBFT FUNCTIONS
void *ft_memcpy(void *dst, const void *src, size_t n);
void ft_putchar(char c);
void ft_putstr(char const *s);
void ft_putendl(char const *s);
void ft_putnbr(long n);
size_t ft_strlen(const char *s);
void ft_bzero(void *s, size_t n);
