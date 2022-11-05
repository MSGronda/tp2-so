// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_kill_process(unsigned int pid) {
	return removeTask(pid);
}