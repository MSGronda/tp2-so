// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_process_alive(unsigned int pid)
{
	return findTask(pid) != NO_TASK_FOUND;
}
