#include <semaphore.h>
#include <syscalls.h>

unsigned int sys_register_sem(unsigned int sem_id)
{
	return create_sem(sem_id);
}
