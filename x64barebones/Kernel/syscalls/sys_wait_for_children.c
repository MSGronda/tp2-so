#include <multitasking.h>
#include <syscalls.h>


uint64_t sys_wait_for_children(uint64_t rsp, uint64_t ss){
	wait_for_children(rsp,  ss);
	return 1;
}