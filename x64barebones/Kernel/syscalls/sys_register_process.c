#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_register_process(uint64_t entrypoint, int screen, uint64_t arg0)
{
	return add_task(entrypoint, screen, DEFAULT_PRIORITY, MORTAL, arg0);
}
