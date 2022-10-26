#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_get_pid()
{
	return get_current_pid();
}
