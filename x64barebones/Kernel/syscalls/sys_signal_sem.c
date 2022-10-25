#include <semaphore.h>
#include <syscalls.h>


uint64_t sys_signal_sem(unsigned int sem_id){
	return signal_sem(sem_id);
}