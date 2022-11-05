// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <syscalls.h>
#include <mm_utils.h>

uint64_t sys_mm_status(uint64_t * buffer){
	printMemStatus(buffer);
	return 1;
}
