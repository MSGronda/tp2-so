// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0)
{
	return add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL, arg0);
}
