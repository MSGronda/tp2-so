#include <multitasking.h>
#include <syscalls.h>


unsigned int sys_wait_for_children(uint64_t rsp, uint64_t ss){
	wait_for_children(rsp,  ss);
	return 1;
}