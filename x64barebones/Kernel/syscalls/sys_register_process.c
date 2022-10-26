#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0)
{
	return add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL, arg0);
}
