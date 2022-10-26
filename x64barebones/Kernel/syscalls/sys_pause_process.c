#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_pause_process(unsigned int pid) {
	return pauseOrUnpauseProcess(pid);
}
