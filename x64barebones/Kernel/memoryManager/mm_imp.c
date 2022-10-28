#include <memoryManager.h>
#include <mm_imp.h>
#include <stddef.h>

 // WE ALWAYS WANT BYTES!!!!
 void mm_init() {
     addEOL(HEAP_START);
 }

 void * mm_malloc(uint64_t len) {
    if(len <= 0) 
        return NULL;

    uint64_t newSize = MASK_LAST_BIT(len + 1 + HEADER_SIZE); // Rounds number
    header_t * out = findFree(newSize);

    if(out == NULL)
        return NULL;

    addBlock(out, newSize);

    // User has a pointer after the header
    return (void *)  (SUM_PTR(out, HEADER_SIZE));
 }

 void mm_free(void * ptr) {
 	header_t * castedPtr = (header_t *) ptr;
    if(castedPtr == NULL || castedPtr < HEAP_START || castedPtr >= HEAP_END)
        return;
  
    header_t * head = SUM_PTR(castedPtr, -HEADER_SIZE);
    //Free the header just before the user pointer
    freeBlock(head);
 }

 // TODO: HACER EL FREE PARA ATRAS TAMBIEN
void freeBlock(header_t * ptr) {
    ptr->allocated = FALSE;

    header_t * next = SUM_PTR(ptr, ptr->size);
    if(!next->allocated)
        ptr->size += next->size;
}

 // Allocate in a free block, split if needed
 void addBlock(header_t * ptr, uint64_t newSize) {
    uint64_t oldSize = MASK_LAST_BIT(ptr->size);

    if(IS_EOL(ptr->size)) { 
        // last block
        addEOL(SUM_PTR(ptr, newSize));

        ptr->size = newSize;
        ptr->allocated = TRUE;
    }
    else if(newSize + MIN_REQUEST < oldSize) { // split
        ptr->size = newSize;
        ptr->allocated = TRUE;

        ptr = SUM_PTR(ptr, newSize); // next block

        ptr->size = oldSize - newSize;
        ptr->allocated = FALSE; // for coherence
    }
    else { 
        // normal case
        ptr->size = oldSize;
        ptr->allocated = TRUE;
    }
 }

 header_t * findFree(uint64_t len) {
     header_t * ptr = HEAP_START;

     while( !IS_EOL(ptr->size) && (ptr->allocated || MASK_LAST_BIT(ptr->size) < len) )
         ptr = SUM_PTR(ptr, MASK_LAST_BIT(ptr->size));

     if(IS_EOL(ptr->size)) {
         // Check if it fits
         if(SUM_PTR(ptr, len + EOL_SIZE) > HEAP_END)
             return NULL;
     }
     return ptr;
 }

 // Add End Of List block
 void addEOL(header_t * ptr) {
    ptr->size = 0;
    ptr->allocated = TRUE;
 }