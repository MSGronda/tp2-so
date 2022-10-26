#include <multitasking.h>
#include <syscalls.h>


unsigned int sys_wait_for_children(){
	wait_for_children();
	return 1;
}