#include <interrupts.h>
#include <syscalls.h>


unsigned int sys_renounce_cpu(){
	forceTimerTick();
	return 1;
}