#include <multitasking.h>
#include <syscalls.h>


unsigned int sys_wait_sem(unsigned int sem_id, uint64_t rsp, uint64_t ss){
	return wait_sem( sem_id,  rsp,  ss);
}