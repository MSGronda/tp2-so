#include <memoryManager.h>
#include <lib.h>

void printMemStatus(uint64_t buffer[3]){
    memStatus * status = getMemStatus();

    buffer[0] = status->allocatedBytes;
    buffer[1] = status->freeBytes;
    buffer[2] = status->allocatedBlocks;
}