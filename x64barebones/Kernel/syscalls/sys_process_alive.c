#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_process_alive(unsigned int pid)
{
	return findTask(pid) != NO_TASK_FOUND;
}
