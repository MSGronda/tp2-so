#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_pause_process(unsigned int pid) {
	return pauseOrUnpauseProcess(pid);
}
