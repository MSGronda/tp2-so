#include <semaphore.h>
#include <syscalls.h>

uint64_t sys_register_sem_available(unsigned int value)
{
	return create_sem_available(value);
}