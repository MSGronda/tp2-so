// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <video.h>
#include <syscalls.h>
#include <multitasking.h>


/* Decides which screen to clear */
uint64_t sys_clear_screen() {
	return clearScreenDispatcher();
}