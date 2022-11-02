#include <multitasking.h>
#include <data_types.h>
#include <syscalls.h>

uint64_t sys_process_info(process_info * info)
{
	return get_process_info(info);
}
