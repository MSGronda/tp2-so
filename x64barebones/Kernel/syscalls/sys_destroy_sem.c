// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <semaphore.h>
#include <syscalls.h>

uint64_t sys_destroy_sem(unsigned int sem_id)
{
	destroy_sem(sem_id);
	return 1;
}
