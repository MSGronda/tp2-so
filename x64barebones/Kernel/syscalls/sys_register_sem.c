#include <semaphore.h>
#include <syscalls.h>

uint64_t sys_register_sem(unsigned int sem_id)
{
	return create_sem(sem_id);
}
