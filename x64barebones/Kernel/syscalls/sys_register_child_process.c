#include <child_process.h>
#include <syscalls.h>

uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0)
{
	return add_child_task(entryPoint, input, output, arg0);
}
