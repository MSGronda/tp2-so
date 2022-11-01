#ifdef USE_BUDDY
#ifndef _MM_BUDDY_H_
#define _MM_BUDDY_H_

#define MIN_SIZE_CLASS 6

#define HEADER_SIZE (sizeof(uint64_t)) // in order to stay alligned

#define POW_2(exp) (1 << (exp))

typedef struct TNode{
    char isAllocated;
    char isSplit;
} TNode;

/*
 * << getSmallestAvailable >>
 * ----------------------------------------------------------------------
 * Description: finds the lowest index block of [sizeClass], this
 * means we first fill the left side of the btree
 * ----------------------------------------------------------------------
 * Receives: 
 *       [sizeClass] = size of the block we are trying to find, block
 *      has size 2^sizeClass
 * Returns: 
 *      (int) idx of said block
 */
int getSmallestAvailable(unsigned int sizeClass);

#endif // _MM_BUDDY_H_
#endif // USE_BUDDY