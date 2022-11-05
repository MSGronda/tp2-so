#ifdef USE_BUDDY
#ifndef _MM_BUDDY_H_
#define _MM_BUDDY_H_

/*
 * This implementation of the buddy algorithm
 * uses a linearized binary tree to keep track
 * of which blocks are allocated and split
*/

#define MIN_SIZE_CLASS 6

#define HEADER_SIZE (sizeof(uint64_t)) // in order to stay alligned

#define POW_2(exp) ((uint64_t) 1 << (exp))

typedef struct TNode{
    char isAllocated;
    char isSplit;
} TNode;

/**
 * @brief   Finds the lowest index block of sizeClass
 * 
 * @note    sizeClass is the power in 2^n
 * @note    This means we first fill the left side of btree
 * 
 * @return  Index of lowest block of sizeClass
*/
int getSmallestAvailable(unsigned int sizeClass);

#endif // _MM_BUDDY_H_
#endif // USE_BUDDY