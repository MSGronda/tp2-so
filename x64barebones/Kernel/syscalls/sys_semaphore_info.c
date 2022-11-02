#include <semaphore.h>
#include <data_types.h>
#include <syscalls.h>

uint64_t sys_semaphore_info(semaphore_info * info)
{
	return get_semaphore_info(info);
}
