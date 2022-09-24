#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdlib.h>

#define HEAP_SIZE (0xFFFFFFFFFFFFFFFF - 0x0000000000100000)

typedef struct MemoryManagerCDT *MemoryManagerADT;

MemoryManagerADT createMemoryManager(void *const restrict memoryForMemoryManager, void *const restrict managedMemory);

void *allocMemory(MemoryManagerADT const restrict memoryManager, const size_t memoryToAllocate);

void freeMemory(MemoryManagerADT const restrict memoryManager, void *memoryToFree);

// TODO: Hay que agregar un status (lo pide la consigna)
// -> Memoria total ocupada, libre y cualq otra variable necesaria

#endif
