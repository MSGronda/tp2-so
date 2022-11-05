// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <interrupts.h>
#include <syscalls.h>


uint64_t sys_renounce_cpu(){
	forceChangeTask();
	return 1;
}