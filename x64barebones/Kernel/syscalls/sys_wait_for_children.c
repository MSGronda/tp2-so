#include <multitasking.h>
#include <syscalls.h>


uint64_t sys_wait_for_children(){
	wait_for_children();
	return 1;
}