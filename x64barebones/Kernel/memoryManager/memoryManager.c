#include "memoryManager.h"
#include <stdlib.h>

typedef uint64_t header_t;

#define HEADER_SIZE sizeof(header_t)
#define TRUE 1
#define FALSE (!TRUE)

#define HEAP_SIZE 4096
#define EOL_SIZE HEADER_SIZE
//Seteo el size en par = free
#define MASK_LAST_BIT(num) (((num) >> 1) << 1)

//Como los size (real) son par, transforma el valor en par mas cercano
//No tiene en cuenta el bit de IsAllocated
// -2 = 1111 .... 1110
#define GET_SIZE(ptr) ((uint64_t)*(ptr) & -2)

//Es impar = allocated?
#define IS_ALLOCATED(ptr) ((uint64_t)*(ptr) & 1)

//Hacer el size impar = allocated
#define SET_ALLOCATED(size) ((size) | 1)

//Check if size is 1 = real size (0) and is allocated(1)
#define IS_EOL(ptr) ((uint64_t)*(ptr) == 1)



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
    uint64_t newSize = MASK_LAST_BIT(len + 1); // we also round the number (2-Byte align)
    uint64_t oldSize = GET_SIZE(ptr);

    if(newSize + HEADER_SIZE >= oldSize)
    	*ptr = SET_ALLOCATED(oldSize);
    else{
        *ptr = SET_ALLOCATED(newSize);
        *(ptr + newSize) = oldSize - newSize; 
    }
}

void * findFree(uint64_t len) {
    void * ptr = heapStart;

    while( !IS_EOL(ptr) && (IS_ALLOCATED(ptr) || (*ptr < len) )
        ptr = ptr + GET_SIZE(ptr);


    if(IS_EOL(ptr)){
    	//Si es el EOL chequeo si entra
    	if(ptr + HEADER_SIZE + len > heapEnd)
    		return NULL;
    	addEOL(ptr + EOL_SIZE + len);
    }
    addBlock(ptr,len);
    return ptr;
}

// Add End Of List block
void addEOL(void * ptr) {
    *ptr = (uint64_t) 1;  // size = 0 y allocated = 1
}


//TODO Ver si queremos hacer el heap dinamico (setear inicio y size)
void mm_init() {
    addEOL(heapStart);
}


void * mm_malloc(uint64_t len) {
    if(len == 0) 
        return NULL;

    void * out = findFree(len + HEADER_SIZE);
    addBlock(out, len + HEADER_SIZE);

    //User has a pointer after the header
    return out + HEADER_SIZE;
}


void mm_free(void * ptr) {
    if(ptr == NULL || ptr < heapStart || ptr >= heapEnd)
        return;
    
    //Free the header just before the user pointer
    freeBlock(ptr - HEADER_SIZE);
    //1011 -> 1010 
    *ptr = MASK_LAST_BIT(*ptr);
}





