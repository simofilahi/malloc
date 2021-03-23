#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

// REMOVE IT LATER
#include <string.h>
// REMOVE IT LATER
// #include <signal.h>
// void (*signal(int signum, void (*sighandler)(int)))(int);

// REMOVE IT LATER
#include <stdio.h>
// MAX SIZE OF AN ALLOCATION IN A ZONE
#define MAX_TINY_ZONE_SIZE 3000
#define MAX_SMALL_ZONE_SIZE 4096

// MMAP PAGES
#define TINY_ZONE_PAGES 400
#define SAMLL_ZONE_PAGES 800
#define EXTRA_ZONE_PAGES 300

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
    struct s_block *next;
    size_t blockSize;
    size_t used;
    size_t mergedCount;

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

// FIRST ZONE GLOBAL VARIABLE
t_memZone *headZone;

// MEMORY ZONES
t_memZone *createNewZone(size_t pages, size_t type);
void addNewZoneToList(t_memZone *newZone);
void *createLargeZone(size_t totalSize);

// FREE FUNCTIONS;
void free(void *ptr);
void mergeBlock(t_block *prevBlock, t_block *currBlock);

// REALLOC FUNCTIONS
void *realloc(void *ptr, size_t size);

// REALLOCF FUNCTIONS
void *reallocf(void *ptr, size_t size);

// CALLOC FUNCTIONS
void *calloc(size_t count, size_t size);

// VALLOC
void *valloc(size_t size);

// ALIGNMENT
size_t align(size_t size);

// MALLOC FUNCTIONS
void *malloc(size_t size);
void *createExtraZone(size_t totalSize);
t_block *findFreeBlockInExtraZone(size_t totalSize);
t_block *fillFirstBlock(t_memZone *zone, size_t totalSize);
t_block *fillBlock(t_memZone *zone, size_t totalSize);
t_block *createNewBlockInZone(t_memZone *zone, size_t totalSize);
t_block *splitMergedBlocks(t_block *block, size_t totalSize);

// ALLOCATION STATE VISUALISATION
void show_alloc_mem();
void show_alloc_mem_ex();

// PRINT FUNCTIONS
void min_printf(void *str, void *ptr, int nflag);

// LIBFT FUNCTIONS
void *ft_memcpy(void *dst, const void *src, size_t n);
void ft_putchar(char c);
void ft_putstr(char const *s);
void ft_putendl(char const *s);
void ft_putnbr(long n);
size_t ft_strlen(const char *s);
void *ft_bzero(void *s, size_t n);
