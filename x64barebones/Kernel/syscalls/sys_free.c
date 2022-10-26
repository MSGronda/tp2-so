#include <memoryManager.h>

uint64_t sys_free(void * ptr) {
	mm_free(ptr);

	return 1;	
}