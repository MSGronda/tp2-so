#include <semaphore.h>
#include <syscalls.h>


unsigned int sys_signal_sem(unsigned int sem_id){
	return signal_sem(sem_id);
}