#include <video.h>
#include <syscalls.h>
#include <multitasking.h>


/* Decides which screen to clear */
uint64_t sys_clear_screen() {
	return clearScreenDispatcher();
}