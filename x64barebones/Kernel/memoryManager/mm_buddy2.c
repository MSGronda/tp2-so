#include <memoryManager.h>

#define MIN_SIZE_CLASS 5
#define BUDDY_START 0xA00000

#define BUDDY_SUM_PTR(ptr, num) (((uint64_t) (ptr) + (num)) )

typedef struct TNode{
    char isAllocated : 1;
    char isSplit : 1;
} TNode;

static TNode * btree = BUDDY_START;
static void * userStart;
static unsigned int maxSizeClass;

static inline unsigned int getParentIdx(unsigned int idx) {
    return (idx - 1) >> 1;
}

static inline unsigned int getLeftChildIdx(unsigned int idx) {
    return (idx << 1) + 1;
}

static inline unsigned int getRightChildIdx(unsigned int idx) {
    return (idx << 1) + 2;
}

static inline unsigned int getBuddy(unsigned int idx) {
    return (idx % 2) == 0? idx - 1 : idx + 1; 
}

static inline pow2(unsigned int exp) {
    return (2 << exp);
}

//Returns the max size class that fits a block of size
//Performs a log2(size) rounded to nearest whole num using bitwise operations
unsigned int getSizeClass(uint64_t size) {
    unsigned int out = 1; // TODO: creo q esto arrancaba con 0

    while((size >>= 1) != 0) 
        out++;
    return out;
}

void mm_init() {
    maxSizeClass = getSizeClass(HEAP_SIZE);

    int nodes = pow2((maxSizeClass - MIN_SIZE_CLASS) + 1) - 1; // 2^h+1 - 1
    //Como nos aseguramos que el TREE + la memoria de 2^maxSizeClass entre en el heapsize??
    userStart = BUDDY_SUM_PTR(btree, nodes * sizeof(TNode));
}

TNode * getSmallestAvailable(unsigned int sizeClass) {
    return getSmallestAvailableRec(sizeClass, maxSizeClass, 0);
}

TNode * getSmallestAvailableRec(unsigned int sizeClass, unsigned int currSizeClass, unsigned int idx) {
    // cb
    if(sizeClass > maxSizeClass)
        return NULL;

    if(sizeClass == MIN_SIZE_CLASS) {
        unsigned int buddyIdx = getBuddy(idx);
        if(!(btree[idx].isAllocated && btree[buddyIdx].isAllocated)) {
            btree[getParentIdx(idx)].isSplit = TRUE;
            return btree[idx].isAllocated? &btree[buddyIdx] : &btree[idx];
        }

        return NULL;
    }

    TNode * out = getSmallestAvailableRec(sizeClass, currSizeClass - 1, getLeftChildIdx(idx));
    if(out == NULL)
        out = getSmallestAvailableRec(sizeClass, currSizeClass - 1, getRightChildIdx(idx));

    return out;
}



void * mm_malloc(uint64_t size) {
    unsigned int sizeClass = getSizeClass(size);
    TNode * node = getSmallestAvailable(sizeClass);
    // TODO: falta hacer el calculo



}

