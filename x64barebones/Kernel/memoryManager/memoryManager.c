#include "memoryManager.h"
#include <stdlib.h>

#define TRUE 1
#define FALSE (!TRUE)

#define HEAP_SIZE 4096
#define EOL_SIZE (sizeof(uint64_t))

#define MASK_LAST_BIT(num) (((num) >> 1) << 1)
#define GET_SIZE(ptr) (*(ptr) & -2)
#define IS_ALLOCATED(ptr) (*(ptr) & 1)
#define SET_ALLOCATED(size) ((size) | 1)

static void * heapStart = 5000;
static void * heapEnd = heapStart + HEAP_SIZE;


// TODO: CHEQUEO DE ERRORES

// TODO: HACER EL FREE PARA ATRAS TAMBIEN
void freeBlock(void * ptr) {
    *ptr = GET_SIZE(ptr);
    void * next = ptr + *ptr;

    if(IS_ALLOCATED(next) == FALSE)
        *ptr = *ptr + *next;
}


// Allocate in a free block, split if needed
void addBlock(void * ptr, uint64_t len) {
    uint64_t newSize = MASK_LAST_BIT(len + 1); // we also round the number
    uint64_t oldSize = GET_SIZE(ptr);

    *ptr = SET_HEADER(len);
    if(newSize < oldSize)
        *(ptr + newSize) = oldSize - newSize; 
}

void * findFree(uint64_t len) {
    void * ptr = heapStart;

    while( (ptr + len + EOL_SIZE < ) && (IS_ALLOCATED(ptr) || (*ptr < len) )
        ptr = ptr + GET_SIZE(ptr);

    if(ptr + len >= heapEnd)
        return NULL;
    return ptr;
}

// Add End Of List block
void addEOL(void * ptr) {
    *ptr = (uint64_t) 1;  // size = 0 y allocated = 1
}


void mm_init() {
    addEOL(heapStart);
}


void * mm_malloc(uint64_t len) {
    if(len == 0) 
        return NULL;

    void * out = findFree(len + sizeof(uint64_t));
    addBlock(out, len + sizeof(uint64_t));

    return out + sizeof(uint64_t);
}


void mm_free(void * ptr) {
    if(ptr == NULL || ptr < heapStart || ptr >= heapEnd)
        return;
    
    freeBlock(ptr - sizeof(uint64_t));
    *ptr = MASK_LAST_BIT(*ptr);
}





