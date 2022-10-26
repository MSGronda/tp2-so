#include <interrupts.h>
#include <syscalls.h>


uint64_t sys_renounce_cpu(){
	forceTimerTick();
	return 1;
}