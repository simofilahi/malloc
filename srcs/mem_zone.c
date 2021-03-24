#include "../includes/malloc.h"

//  ADD NEW MEMORY ZONE TO LIST
void addNewZoneToList(t_memZone *newZone)
{
    t_memZone *curr;

    if (!headZone)
        headZone = newZone;
    else
    {
        curr = headZone;
        while (curr->next)
            curr = curr->next;
        curr->next = newZone;
    }
}

// REQUEST FROM OS NEW MEMORY ZONE
t_memZone *createNewZone(size_t pages, size_t type)
{
    size_t size;
    size_t zoneSize;
    t_memZone *newZone;

    zoneSize = sizeof(t_memZone);
    size = (size_t)getpagesize() * pages;
    newZone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // newZone->startZone = (void *)newZone + (zoneSize + 8);
    // ft_putstr("malloc\n");
    // min_printf("Zone @ before", newZone, 1);
    // newZone->startZone = (void *)newZone + (zoneSize + 8);
    // min_printf("newZone->startZone @ after", newZone->startZone, 1);
    newZone->zoneSize = size - zoneSize;
    newZone->type = type;
    newZone->next = NULL;
    addNewZoneToList(newZone);
    return newZone;
}

// CREATE LARGE ZONE
void *createLargeZone(size_t totalSize)
{
    t_memZone *zone;
    size_t pages;
    size_t zoneDataSize;

    zoneDataSize = sizeof(t_memZone);
    pages = (totalSize / (size_t)getpagesize()) + 1;
    zone = createNewZone(pages, LARGE_ZONE);
    return (createNewBlockInZone(zone, totalSize));
}