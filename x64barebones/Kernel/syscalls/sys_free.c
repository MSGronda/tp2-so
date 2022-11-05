// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <memoryManager.h>

uint64_t sys_free(void * ptr) {
	mm_free(ptr);
	return 1;	
}