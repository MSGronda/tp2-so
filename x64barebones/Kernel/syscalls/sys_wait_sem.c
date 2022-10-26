#include <semaphore.h>
#include <syscalls.h>


unsigned int sys_wait_sem(unsigned int sem_id){
	return wait_sem(sem_id);
}