#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_kill_process(unsigned int pid) {
	return removeTask(pid);
}