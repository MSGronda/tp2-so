#include <video.h>
#include <syscalls.h>
#include <multitasking.h>


/* Decides which screen to clear */
unsigned int sys_clear_screen() {
	return clearScreenDispatcher();
}