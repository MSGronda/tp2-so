#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_register_child_process(uint64_t entryPoint, int screen, uint64_t arg0)
{
	return add_child_task(entryPoint, screen, arg0);
}
