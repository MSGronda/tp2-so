#ifndef MM_UTILS_H
#define MM_UTILS_H

#include <stdint.h>

typedef struct memStatus{
    uint64_t allocatedBytes;
    uint64_t freeBytes;
    uint64_t allocatedBlocks;
} memStatus;

void printMemStatus(uint64_t * buffer);

#endif