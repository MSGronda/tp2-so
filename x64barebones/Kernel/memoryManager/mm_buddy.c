#include <memoryManager.h>

#define MIN_SIZE_CLASS 5
#define BUDDY_START 0xA00000
#define BUDDY_END (BUDDY_START + HEAP_SIZE)

#define HEADER_SIZE (sizeof(uint64_t)) // in order to stay alligned

#define BUDDY_SUM_PTR(ptr, num) (((uint64_t) (ptr) + (num)) )
#define BUDDY_GET_CLASS(ptr) ( *((unsigned int *) ptr))



typedef struct TNode{
    char isAllocated : 1;
    char isSplit : 1;
} TNode;

static TNode * btree = BUDDY_START;
static void * userStart;
static unsigned int maxSizeClass;
static uint64_t buddySize;

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

static inline unsigned int pow2(unsigned int exp) {
    return (2 << exp);
}

//Returns the max size class that fits a block of size
//Performs a log2(size) rounded to nearest whole num using bitwise operations
unsigned int getSizeClass(uint64_t size) {
    unsigned int out = 1; 

    while((size >>= 1) != 0)
        out++;
    
    return out < MIN_SIZE_CLASS? MIN_SIZE_CLASS : out;
}

void mm_init() {
    maxSizeClass = getSizeClass(HEAP_SIZE);

    int nodes = pow2((maxSizeClass - MIN_SIZE_CLASS) + 1) - 1; // 2^h+1 - 1

    userStart = (void *) BUDDY_SUM_PTR(btree, nodes * sizeof(TNode));
    buddySize =  BUDDY_END - ((int64_t) userStart);
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

    return NULL; // sizeClass > currSizeClass => shouldnt happen
}

TNode * getSmallestAvailable(unsigned int sizeClass) {
    return getSmallestAvailableRec(sizeClass, maxSizeClass, 0);
}

static inline void * nodeToPtr(unsigned int idx, unsigned int sizeClass) {
    return BUDDY_SUM_PTR(userStart, (idx - getFirstIdxOfClass(sizeClass)) * (1 << sizeClass));
}

static inline unsigned int ptrToIdx(void * ptr, unsigned int sizeClass) {
    return (ptr - userStart) >> sizeClass; 
}


void * mm_malloc(uint64_t size) {
    if(size <= 0 || size + HEADER_SIZE > buddySize)
        return NULL;    

    unsigned int sizeClass = getSizeClass(size + HEADER_SIZE);
    if(sizeClass > maxSizeClass)
        return NULL;

    TNode * node = getSmallestAvailable(sizeClass);

    void * out = nodeToPtr(node, sizeClass);
    *((uint64_t *) out) = sizeClass; // TODO: posible error aca, chequear con gdb que hace lo esperado

    return (void *) BUDDY_SUM_PTR(out, HEADER_SIZE);
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

    void * realPtr = BUDDY_SUM_PTR(ptr, -HEADER_SIZE);
    unsigned int idx = ptrToIdx(realPtr, BUDDY_GET_CLASS(realPtr));
    freeRec(idx);
}
