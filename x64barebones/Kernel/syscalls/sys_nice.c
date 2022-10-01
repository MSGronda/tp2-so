#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_nice(uint8_t pid, int delta)
{
	return change_priority(pid, delta);
}
