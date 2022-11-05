// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <memoryManager.h>
#include <lib.h>

void printMemStatus(uint64_t buffer[3]){
    memStatus * status = getMemStatus();

    buffer[0] = status->allocatedBytes;
    buffer[1] = status->freeBytes;
    buffer[2] = status->allocatedBlocks;
}