#include <semaphore.h>
#include <syscalls.h>

unsigned int sys_destroy_sem(unsigned int sem_id)
{
	destroy_sem(sem_id);
	return 1;
}
