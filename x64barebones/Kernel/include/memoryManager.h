#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>

#define SUM_PTR(ptr, num) ((uint64_t) (ptr) + (num))

#define TRUE 1
#define FALSE (!TRUE)

#define HEAP_SIZE 0x100000  // 1Mb (in bytes!!!!)    
#define HEAP_START ((void *) 0xA00000)  // 10 Mb  (TODO: habria que calcular el fin del userland y meterlo ahi)
#define HEAP_END ((void *) (SUM_PTR(HEAP_START, HEAP_SIZE)))


/*
 * << mm_init >>
 * ----------------------------------------------------------------------
 * Description: sets up the desired memory manager
 * ----------------------------------------------------------------------
 * Receives: --
 * Devuelve: --
 */
void mm_init();

/*
 * << mm_malloc >>
 * ----------------------------------------------------------------------
 * Description: allocates [size] bytes and returns pointer to allocated
 * memory
 * ----------------------------------------------------------------------
 * Receives: 
 *      [size] = size (in bytes) of memory block to be allocated
 * Devuelve: 
 *      (void *) pointer to allocated memory
 */
void * mm_malloc(uint64_t size);

/*
 * << mm_free >>
 * ----------------------------------------------------------------------
 * Description: frees memory space pointed by [ptr]
 * ----------------------------------------------------------------------
 * Receives: 
 *      [ptr] = pointer to memory space to be freed
 * Devuelve: --
 */
void mm_free(void * ptr);

#endif
