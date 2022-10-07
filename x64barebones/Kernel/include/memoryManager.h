#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>

typedef size_t header_t;

#define HEADER_SIZE sizeof(header_t)
#define TRUE 1
#define FALSE (!TRUE)

#define HEAP_SIZE 4096
#define HEAP_START (header_t *) 4096
#define HEAP_END (header_t *) (HEAP_START + HEAP_SIZE)

#define EOL_SIZE HEADER_SIZE
//Seteo el size en par = free
#define MASK_LAST_BIT(num) (((num) >> 1) << 1)

//Como los size (real) son par, transforma el valor en par mas cercano para abajo
//No tiene en cuenta el bit de IsAllocated
// -2 = 1111 .... 1110
#define GET_SIZE(ptr) (*ptr & -2)

//Es impar = allocated?
#define IS_ALLOCATED(ptr) ((header_t)*(ptr) & 1)

//Hacer el size impar = allocated
#define SET_ALLOCATED(size) ((size) | 1)

//Check if size is 1 = real size (0) and is allocated(1)
#define IS_EOL(ptr) ((header_t)*(ptr) == 1)

void freeBlock(header_t * ptr);
void addBlock(header_t * ptr, uint32_t len);
header_t * findFree(uint32_t len);
void addEOL(header_t * ptr);
void mm_init();
void * mm_malloc(uint32_t len);
void mm_free(void * ptr);



#endif
