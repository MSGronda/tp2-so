#include <memoryManager.h>
#include "./btreeADT.h"

#define MIN_SIZE_CLASS 5
#define BUDDY_START ((uint64_t *) 0xA00000)
#define BUDDY_SUM_PTR(ptr, num) (((uint64_t) (ptr) + (num)) )

void mm_init() {
    int maxSizeClass = getSizeClass(HEAP_SIZE);

    uint64_t * sizeClasses = BUDDY_START;

    int nodes = ((maxSizeClass - MIN_SIZE_CLASS + 1) << 1) - 1;

    uint64_t * userStart = (uint64_t *) BUDDY_SUM_PTR(BUDDY_START, nodes*sizeof(TNode *));
    
    //INITTREE?
    
}

int getSizeClass(uint64_t size) {
    int out = 0;
    while((size >>= 1) != 0) 
        out++;

    return out;
}
