#include <syscalls.h>
#include <mm_utils.h>

uint64_t sys_mm_status(uint64_t * buffer){
	printMemStatus(buffer);
}
