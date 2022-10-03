#include <memoryManager.h>

// TODO: CHEQUEO DE ERRORES
// TODO: HACER EL FREE PARA ATRAS TAMBIEN
void freeBlock(header_t * ptr) {
    *ptr = GET_SIZE(ptr);
    header_t * next = ptr + *ptr;

    if(IS_ALLOCATED(next) == FALSE)
        *ptr = *ptr + *next;
}


// Allocate in a free block, split if needed
void addBlock(header_t * ptr, uint32_t len) {
    uint32_t newSize = MASK_LAST_BIT(len + 1); // Alligns the number, rounding it
    uint32_t oldSize = GET_SIZE(ptr);

    if(newSize + HEADER_SIZE >= oldSize && oldSize != 0) 
    	*ptr = SET_ALLOCATED(oldSize);
    else {
        *ptr = SET_ALLOCATED(newSize);
        *(ptr + newSize) = oldSize - newSize; 
    }
}


header_t * findFree(uint32_t len) {
    header_t * ptr = HEAP_START;

    // TODO: Creo que hay un error aca
    while( !IS_EOL(ptr) && (IS_ALLOCATED(ptr) || (*ptr < len)) && ptr < HEAP_END)
        ptr = ptr + GET_SIZE(ptr);

    // Probably no more space
    if(ptr > HEAP_END)
    	return NULL;

    if(IS_EOL(ptr)) {
    	// Check if it fits
    	if(ptr + len + HEADER_SIZE > HEAP_END)
    		return NULL;

    	addEOL(ptr + len + HEADER_SIZE);
    }

    addBlock(ptr,len);
    return ptr;
}


// Add End Of List block
void addEOL(header_t * ptr) {
    *ptr = (header_t) 1;  // size = 0 y allocated = 1
}


//TODO Ver si queremos hacer el heap dinamico (setear inicio y size)
void mm_init() {
    addEOL(HEAP_START);
}


void * mm_malloc(uint32_t len) {
    if(len == 0) 
        return NULL;

    header_t * out = findFree(len + HEADER_SIZE);
    if(out == NULL)
    	return NULL;

    addBlock(out, len + HEADER_SIZE);

    // User has a pointer after the header
    return (void *) (out + HEADER_SIZE);
}


void mm_free(void * ptr) {
	header_t * castedPtr = (header_t *) ptr;
    if(castedPtr == NULL || castedPtr < HEAP_START || castedPtr >= HEAP_END)
        return;
    
    //Free the header just before the user pointer
    freeBlock(castedPtr - HEADER_SIZE);
    // Set IS_ALLOCATED to 0 (aka. FALSE)
    *castedPtr = MASK_LAST_BIT(*castedPtr);
}
