#include "../include/comandos.h"
#include "../include/stdio.h"
#include "../include/test_util.h"
#include "../include/stdlib.h"
#include "../include/syscalls.h"

#define MAX_BLOCKS 500
#define MAX_MEMORY 3000
typedef struct MM_rq{
  void *address;
  uint32_t size;
}mm_rq;

void* setmem(void* destiation, int32_t c, uint64_t length) {
    uint8_t chr = (uint8_t)c;
    char* dst = (char*)destiation;
    while (length--) {
        dst[length] = chr;
    }
    return destiation;
}

void test_mm(){
    mm_rq mm_rqs[MAX_BLOCKS];
    uint8_t rq;
    uint32_t total;
    uint64_t max_memory;

    max_memory = MAX_MEMORY;

    while (1) {
        rq = 0;
        total = 0;

        puts("TESTING MEMORY MANAGER - PRESS ESC TO FINISH TEST");

        // Request as many blocks as we can
        while (rq < MAX_BLOCKS && total < max_memory) {
            mm_rqs[rq].size = 1;
            mm_rqs[rq].address = malloc(mm_rqs[rq].size);
            puts("allocated");
            char buffer[20];
            num_to_string(rq, buffer);
            puts(buffer);
            for(int j = 0 ; j<5000000 ; j++);
            if(mm_rqs[rq].address == NULL){
                puts("NO MORE MEM AVAILABLE");
                return;
            }

            if (mm_rqs[rq].address) {
                total += mm_rqs[rq].size;
                rq++;
            }
        }

        // Set
        uint32_t i;
        for (i = 0; i < rq; i++)
            if (mm_rqs[i].address)
                setmem(mm_rqs[i].address, i, mm_rqs[i].size);

        // Check
        for (i = 0; i < rq; i++)
            if (mm_rqs[i].address)
                if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size)) {
                    puts("test_mm ERROR");
                    return;
                }

        // Free
        for (i = 0; i < rq; i++)
            if (mm_rqs[i].address)
                free(mm_rqs[i].address);
        puts("Test passed!");   
    }
}