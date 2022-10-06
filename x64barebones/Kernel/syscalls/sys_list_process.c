#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_list_process() {
	list_process();
	return 1;
}
