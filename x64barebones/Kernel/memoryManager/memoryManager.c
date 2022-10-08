#include <memoryManager.h>
// SIEMPRE QUEREMOS BYTES !!!!!!!!!!!!!!!!!!!!!!!!

void printNum(uint64_t num);

// TODO: CHEQUEO DE ERRORES
// TODO: HACER EL FREE PARA ATRAS TAMBIEN
void freeBlock(header_t * ptr) {
    *ptr = GET_SIZE(ptr);

    //ojo el tipo de dato aca
    header_t * next = ptr + *ptr / BITS_IN_BYTE;

    if(IS_ALLOCATED(next) == FALSE)
        *ptr = *ptr + *next;
}


// Allocate in a free block, split if needed
void addBlock(header_t * ptr, uint64_t len) {

    uint64_t oldSize = GET_SIZE(ptr);

    if(IS_EOL(ptr)) {
        addEOL(ptr + len / BITS_IN_BYTE);
        *ptr = SET_ALLOCATED(len);
    }
    else if(len + HEADER_SIZE >= oldSize) 
    	*ptr = SET_ALLOCATED(oldSize);
    else {
        *ptr = SET_ALLOCATED(len);
        *(ptr + len / BITS_IN_BYTE) = oldSize - len; 
    }

}


header_t * findFree(uint64_t len) {
    header_t * ptr = HEAP_START;

    // TODO: Creo que hay un error , es necesario ptr<HEAP_END??
    while( !IS_EOL(ptr) && (IS_ALLOCATED(ptr) || (*ptr < len)) )
        ptr = ptr + GET_SIZE(ptr) / BITS_IN_BYTE;

    if(IS_EOL(ptr)) {
    	// Check if it fits
    	if((ptr + (len + EOL_SIZE) / BITS_IN_BYTE) > HEAP_END)
    		return NULL;
    }

    return ptr;
}


// Add End Of List block
void addEOL(header_t * ptr) {
    *ptr = 1;  // size = 0 y allocated = 1
}


//TODO Ver si queremos hacer el heap dinamico (setear inicio y size)
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
    return (void *) (out + HEADER_SIZE / BITS_IN_BYTE);
}


void mm_free(void * ptr) {
	header_t * castedPtr = (header_t *) ptr;
    if(castedPtr == NULL || castedPtr < HEAP_START || castedPtr >= HEAP_END)
        return;
    
    //Free the header just before the user pointer
    freeBlock(castedPtr - HEADER_SIZE / BITS_IN_BYTE);
    // Set IS_ALLOCATED to 0 (aka. FALSE)
    *(castedPtr - HEADER_SIZE / BITS_IN_BYTE) = MASK_LAST_BIT(*(castedPtr - HEADER_SIZE / BITS_IN_BYTE));
}

void printNum(uint64_t num){
    char buffer[30];
    hex_to_string(num, buffer, 30);
    sys_write(1, buffer, 30);
}