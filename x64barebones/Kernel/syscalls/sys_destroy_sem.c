#include <semaphore.h>
#include <syscalls.h>

uint64_t sys_destroy_sem(unsigned int sem_id)
{
	destroy_sem(sem_id);
	return 1;
}
