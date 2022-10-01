#include <interrupts.h>
#include <syscalls.h>


unsigned int sys_renounce_cpu(uint64_t rsp, uint64_t ss){
	forceNextTask(rsp,  ss);
	return 1;
}