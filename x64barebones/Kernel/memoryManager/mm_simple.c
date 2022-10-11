#include <memoryManager.h>

static uint64_t * current = HEAP_START;

void mm_init() {
    //nada
}


void * mm_malloc(uint64_t len) {
    void * resp = current;

    current = current + (len / BITS_IN_BYTE) + 1;

    return resp;
}

void mm_free(void * ptr) {
    // nada
}
