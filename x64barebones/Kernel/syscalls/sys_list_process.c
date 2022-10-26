#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_list_process() {
	list_process();
	return 1;
}
