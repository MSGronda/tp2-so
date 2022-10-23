#include <memoryManager.h>
#include <mm_imp.h>

 // WE ALWAYS WANT BYTES!!!!
 void mm_init() {
     addEOL(HEAP_START);
 }

 void * mm_malloc(uint64_t len) {
     if(len == 0) 
         return NULL;
     uint64_t newSize = MASK_LAST_BIT(len + 1 + HEADER_SIZE); // Alligns the number, rounding it
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
     // Set IS_ALLOCATED to 0 (aka. FALSE)
     *(head) = MASK_LAST_BIT(*head);
 }

 // TODO: CHEQUEO DE ERRORES
 // TODO: HACER EL FREE PARA ATRAS TAMBIEN
 void freeBlock(header_t * ptr) {
     *ptr = GET_SIZE(ptr);
     sys_write(1, "free", 4);
     header_t * next = SUM_PTR(ptr, *ptr);
     if(IS_ALLOCATED(next) == FALSE)
         *ptr = *ptr + *next;
 }

 // Allocate in a free block, split if needed
 void addBlock(header_t * ptr, uint64_t len) {
     uint64_t oldSize = GET_SIZE(ptr);
     if(IS_EOL(ptr)) { // last block
         addEOL( (header_t*) SUM_PTR(ptr, len));
         *ptr = SET_ALLOCATED(len);
     }
     else if(len + HEADER_SIZE >= oldSize) // normal case
     	*ptr = SET_ALLOCATED(oldSize);
     else { // split
         *ptr = SET_ALLOCATED(len);
         *((header_t*) SUM_PTR(ptr, len)) = oldSize - len; 
     }
 }

 header_t * findFree(uint64_t len) {
     header_t * ptr = HEAP_START;
     while( !IS_EOL(ptr) && (IS_ALLOCATED(ptr) || (GET_SIZE(ptr) < len)) ){
         ptr = SUM_PTR(ptr, GET_SIZE(ptr));
     }
     if(IS_EOL(ptr)) {
         // Check if it fits
         if((SUM_PTR(ptr, len + EOL_SIZE)) > HEAP_END)
             return NULL;
     }
     return ptr;
 }

 // Add End Of List block
 void addEOL(header_t * ptr) {
     *ptr = 1;  // size = 0 and allocated = 1
 }