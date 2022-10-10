#ifndef _MM_IMP_H_
#define _MM_IMP_H_

/*
*   Based on: https://www.youtube.com/watch?v=74s0m4YoHgM
*   The idea of this memory allocator algorithm is to use
*   an implicit list of blocks, which supports merging 
*   forward. The end of the list is marked by EOL.
*   Blocks are used in order to allign memory.
*/

#include <memoryManager.h>

#define EOL_SIZE HEADER_SIZE

// last bit == 1 => allocated  or
// *ptr % 2 != 0 => allocated
#define IS_ALLOCATED(ptr) ((header_t)*(ptr) & 1)
#define SET_ALLOCATED(size) ((size) | 1)

// *ptr % 2 == 0 => not allocated / free
#define MASK_LAST_BIT(num) (((num) >> 1) << 1)

// As last bit can be 1 or 0, we do not have to take it into account
// -2 = 111...1110
#define GET_SIZE(ptr) (*(ptr) & -2)

// size == 0 && allocated == 1 => EOL
// so we can check if *ptr == 1 bc 1 = 000...001
#define IS_EOL(ptr) ((header_t)*(ptr) == 1)

/*
 * << freeBlock >>
 * ----------------------------------------------------------------------
 * Description: frees block pointed by [ptr]
 * ----------------------------------------------------------------------
 * Receives: 
 *      [ptr] = pointer to block to be freed
 * Returns: --
 */
void freeBlock(header_t * ptr);

/*
 * << addBlock >>
 * ----------------------------------------------------------------------
 * Description: adds a block to the implicit list in [ptr] 
 * with [len] bytes of length. May split block to reduce fragmentation
 * ----------------------------------------------------------------------
 * Receives: 
 *      [ptr] = pointer to block to be freed
 *      [len] = size (in bytes) of memory block to be allocated
 * Returns: --
 */
void addBlock(header_t * ptr, uint64_t len);

/*
 * << findFree >>
 * ----------------------------------------------------------------------
 * Description: finds a free block of size [len] (in bytes)
 * ----------------------------------------------------------------------
 * Receives: 
 *       [len] = size (in bytes) of block requested
 * Returns: --
 *      (header_t *) pointer to the start of block. It does not allocate
 *      the header, thus this is the real start of the block
 */
header_t * findFree(uint64_t len);

/*
 * << addEOL >>
 * ----------------------------------------------------------------------
 * Description: adds EOL (End of List) block to the list in the direction
 * pointed by [ptr]. Assumes there is enough space in HEAP.
 * ----------------------------------------------------------------------
 * Receives: 
 *      [ptr] = pointer where EOL is to be added
 * Returns: --
 */
void addEOL(header_t * ptr);

#endif