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
    uint32_t newSize = MASK_LAST_BIT(len + 1); // we also round the number (2-Byte align)
    uint32_t oldSize = GET_SIZE(ptr);

    if(newSize + HEADER_SIZE >= oldSize)
    	*ptr = SET_ALLOCATED(oldSize);
    else{
        *ptr = SET_ALLOCATED(newSize);
        *(ptr + newSize) = oldSize - newSize; 
    }
}

header_t * findFree(uint32_t len) {
    header_t * ptr = HEAP_START;

    while( !IS_EOL(ptr) && (IS_ALLOCATED(ptr) || (*ptr < len)) )
        ptr = ptr + GET_SIZE(ptr);


    if(IS_EOL(ptr)){
    	//Si es el EOL chequeo si entra
    	if(ptr + HEADER_SIZE + len > HEAP_END)
    		return NULL;
    	addEOL(ptr + EOL_SIZE + len);
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
    addBlock(out, len + HEADER_SIZE);

    //User has a pointer after the header
    return (void *)(out + HEADER_SIZE);
}


void mm_free(void * ptr) {
	header_t * cPtr = (header_t *) ptr;
    if(cPtr == NULL || cPtr < HEAP_START || cPtr >= HEAP_END)
        return;
    
    //Free the header just before the user pointer
    freeBlock(cPtr - HEADER_SIZE);
    //1011 -> 1010 
    *cPtr = MASK_LAST_BIT(*cPtr);
}





