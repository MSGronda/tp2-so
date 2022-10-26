#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_kill_process(unsigned int pid) {
	return removeTask(pid);
}