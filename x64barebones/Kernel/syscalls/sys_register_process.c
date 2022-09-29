#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_register_process(uint64_t entryPoint, int screen, uint64_t arg0)
{
	return addTask(entryPoint, screen, arg0);
}
