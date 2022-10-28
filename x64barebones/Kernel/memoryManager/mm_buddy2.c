#include <memoryManager.h>

#define MIN_SIZE_CLASS 5
#define BUDDY_START 0xA00000
#define BUDDY_END (BUDDY_START + HEAP_SIZE)

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

static inline unsigned int getFirstIdxOfClass(unsigned int sizeClass) {
    return (1 << (maxSizeClass - sizeClass)) - 1;
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
    
    return out < MIN_SIZE_CLASS? MIN_SIZE_CLASS : out;
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
    if(btree[idx].isAllocated)
        return NULL;

    if(sizeClass == currSizeClass) {
        btree[idx].isAllocated = TRUE;
        return &btree[idx];
    }

    if(sizeClass < currSizeClass) {
        TNode * out = getSmallestAvailableRec(sizeClass, currSizeClass - 1, getLeftChildIdx(idx));
        if(out == NULL)
            out = getSmallestAvailableRec(sizeClass, currSizeClass - 1, getRightChildIdx(idx));

        btree[idx].isSplit = out? TRUE : FALSE;
        return out;
    }

    return NULL; // sizeClass > currSizeClass => shouldnt happen, already checked
}


// TODO !!!!!!
// should return idx NOT node
static inline void * nodeToPtr(unsigned int idx, unsigned int sizeClass) {
    return (uint64_t) userStart + (idx - getFirstIdxOfClass(sizeClass)) * (1 << sizeClass);
}


void * mm_malloc(uint64_t size) {
    if(size <= 0 || size > HEAP_SIZE)
        return NULL;    

    unsigned int sizeClass = getSizeClass(size);
    if(sizeClass > maxSizeClass)
        return NULL;

    TNode * node = getSmallestAvailable(sizeClass);

    return (void *) nodeToPtr(node, sizeClass);
}

void freeRec(unsigned int idx) {
    btree[idx].isAllocated = FALSE;

    int buddyIdx = getBuddy(idx);
    if(!btree[buddyIdx].isAllocated) {
        int parentIdx = getParentIdx(idx);
        btree[parentIdx].isSplit = FALSE;
        freeRec(parentIdx);
    }
}

void mm_free(void * ptr) {
    if(ptr == NULL || ptr < userStart || ptr > BUDDY_END)
        return;

    unsigned int idx = ptrToIdx(ptr);
    freeRec(idx);
}
