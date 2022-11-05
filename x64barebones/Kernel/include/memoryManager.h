#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>
#include <mm_utils.h>

#define SUM_PTR(ptr, num) ((uint64_t) (ptr) + (num))

#define TRUE 1
#define FALSE (!TRUE)

#define HEAP_SIZE 0x100000  // 1Mb (in bytes!!!!)    
#define HEAP_START ((void *) 0xA00000)  // 10 Mb
#define HEAP_END ((void *) (SUM_PTR(HEAP_START, HEAP_SIZE)))


/**
 * @brief   Sets up the memory manager
*/
void mm_init();

/**
 * @brief   Allocates size bytes
 * 
 * @param   size Size of memory block to allocate
 * 
 * @return  Pointer to the allocated block of memory
 *          If NULL, then error
*/
void * mm_malloc(uint64_t size);

/**
 * @brief   Frees a block of memory
 * 
 * @param   ptr Pointer to the memory block to be freed
*/
void mm_free(void * ptr);

memStatus * getMemStatus();

#endif
