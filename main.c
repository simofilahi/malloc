#include "includes/malloc.h"

int main()
{
    char *ptr = NULL;
    char *str = NULL;

    ptr = (char *)malloc(sizeof(char *) * 10);
    str = (char *)malloc(sizeof(char *) * 10);
    return (0);
}