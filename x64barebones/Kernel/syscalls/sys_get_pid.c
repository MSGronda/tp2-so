#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_get_pid()
{
	return get_current_pid();
}
